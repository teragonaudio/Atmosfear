package freesound
import (
	"net/http"
	"fmt"
	"io/ioutil"
	"encoding/json"
)

const (
	SORT_SCORE = "score" //Sort by a relevance score returned by our search engine (default).
	SORT_DURATION_DESC = "duration_desc" //Sort by the duration of the sounds, longest sounds first.
	SORT_DURATION_ASC = "duration_asc" //Same as above, but shortest sounds first.
	SORT_CREATED_DESC = "created_desc" //Sort by the date of when the sound was added. newest sounds first.
	SORT_CREATED_ASC = "created_asc" //Same as above, but oldest sounds first.
	SORT_DOWNLOADS_DESC = "downloads_desc" //Sort by the number of downloads, most downloaded sounds first.
	SORT_DOWNLOADS_ASC = "downloads_asc" //Same as above, but least downloaded sounds first.
	SORT_RATING_DESC = "rating_desc" //Sort by the average rating given to the sounds, highest rated first.
	SORT_RATING_ASC = "rating_asc" //Same as above, but lowest rated sounds first.

	API_KEY = "your API key goes here"
	ACCESS_TOKEN="your access token goes here"
	CLIENT_ID="your client ID goes here"
)

type SearchResponse struct {
	Detail string `detail`
	Count int `count` //<total number of results>,
	Next string `next` //<link to the next page of results (null if none)>,
	Results []Sound`results`
	Previous string `previous` //<link to the previous page of results (null if none)>
}

type Sound struct {
	Id int `id` //The sound’s unique identifier.
	url string `url` //The URI for this sound on the Freesound website.
	Name string `name` //The name user gave to the sound.
	Tags []string `tags`//An array of tags the user gave to the sound.
	Description string `description` //The description the user gave to the sound.
	GeoTag string `geotag` //Latitude and longitude of the geotag separated by spaces (e.g. “41.0082325664 28.9731252193”, only for sounds that have been geotagged).
	Created string `created` //The date when the sound was uploaded (e.g. “2014-04-16T20:07:11.145”).
	License string `license` //The license under which the sound is available to you.
	Type string `type` //The type of sound (wav, aif, aiff, mp3, or flac).
	Channels string `channels` //The number of channels.
	Filesize int `filesize` //The size of the file in bytes.
	Bitrate int `bitrate` //The bit rate of the sound in kbps.
	Bitdepth int `bitdepth` //The bit depth of the sound.
	Duration int `duration` //The duration of the sound in seconds.
	Samplerate int `samplerate` //The samplerate of the sound.
	Username string `username` //The username of the uploader of the sound.
	Pack string `pack` //If the sound is part of a pack, this URI points to that pack’s API resource.
	Download string `download` //The URI for retrieving the original sound.
	Bookmark string `bookmark` //The URI for bookmarking the sound.
	//Previews string `previews` //Dictionary containing the URIs for mp3 and ogg versions of the sound. The dictionary includes the fields preview-hq-mp3 and preview-lq-mp3 (for ~128kbps quality and ~64kbps quality mp3 respectively), and preview-hq-ogg and preview-lq-ogg (for ~192kbps quality and ~80kbps quality ogg respectively). API authentication is required for retrieving sound previews (Token or OAuth2).
	//Images	string `images` //Dictionary including the URIs for spectrogram and waveform visualizations of the sound. The dinctionary includes the fields waveform_l and waveform_m (for large and medium waveform images respectively), and spectral_l and spectral_m (for large and medium spectrogram images respectively).
	NumDownloads int `num_downloads` //The number of times the sound was downloaded.
	AvgRating int `avg_rating` //The average rating of the sound.
	NumRatings int `num_ratings` //The number of times the sound was rated.
	Rate string `rate` //The URI for rating the sound.
	Comments string `comments` //The URI of a paginated list of the comments of the sound.
	NumComments int `num_comments` //The number of comments.
	Comment string `comment` //The URI to comment the sound.
	SimilarSounds string `similar_sounds` //URI pointing to the similarity resource (to get a list of similar sounds).
	//Analysis analysis	object	Object containing requested descriptors information according to the descriptors request parameter (see below). This field will be null if no descriptors were specified (or invalid descriptor names specified) or if the analysis data for the sound is not available.
	//analysis_stats	URI	URI pointing to the complete analysis results of the sound (see Analysis Descriptor Documentation).
	//analysis_frames	URI	The URI for retrieving a JSON file with analysis information for each frame of the sound (see Analysis Descriptor Documentation).
}

func AuthorizedRequest(path string) (request *http.Request, err error){
	request, err = http.NewRequest("GET", path, nil)
	if err != nil {
		return
	}

	request.Header.Add("Authorization", fmt.Sprintf("Token %s", API_KEY))
	return
}

func OA2AuthorizedRequest(path string) (request *http.Request, err error){
	request, err = http.NewRequest("GET", path, nil)
	if err != nil {
		return
	}

	request.Header.Add("Authorization", fmt.Sprintf("Bearer %s", ACCESS_TOKEN))
	return
}

func Search(query string, filter string, sort string, groupByPack bool) (searchResponse *SearchResponse, err error) {
	path := "http://www.freesound.org/apiv2/search/text?query=car"

	request, err := AuthorizedRequest(path)
	if err != nil {
		return
	}

	url := request.URL
	q := url.Query()
	if query != "" {
		q.Set("query", query)

	}
	if filter != "" {
		q.Set("filter", filter)

	}
	if sort != "" {
		q.Set("sort", sort)
	}

	q.Set("fields", "download,name,type")
	q.Set("filter", "type:wav duration:[1 TO 10]")
	q.Set("group_by_pack", fmt.Sprintf("%v", groupByPack))
	q.Set("group_by_pack", fmt.Sprintf("%v", groupByPack))
	url.RawQuery = q.Encode()

	response, err := Do(request)
	defer response.Body.Close()
	if err != nil {
		return
	}

	body, err := ioutil.ReadAll(response.Body)
	if err != nil {
		fmt.Errorf("Error parsing response", err)
		return
	}

	err = json.Unmarshal(body, &searchResponse)

	if err != nil {
		fmt.Printf("%T\n%s\n%#v\n", err, err, err)
		switch v := err.(type){
			case *json.SyntaxError:
			fmt.Println(string(body[v.Offset-40:v.Offset]))
		}
	}

	if searchResponse.Detail != "" {
		err = fmt.Errorf("problem with request: %v", searchResponse.Detail)
		return
	}

	return searchResponse, nil
}

func Do(request *http.Request) (response *http.Response, err error) {
	client := &http.Client{}
	client.CheckRedirect = func(req *http.Request, via []*http.Request) error {
		if len(via) >= 10 {
			return fmt.Errorf("too many redirects")
		}
		if len(via) == 0 {
			return nil
		}
		for attr, val := range via[0].Header {
			if _, ok := req.Header[attr]; !ok {
				req.Header[attr] = val
			}
		}
		return nil
	}

	response, err = client.Do(request)
	if err != nil {
		err = fmt.Errorf("Failed to do search request: %v", err)
		return
	}
	return
}

func GetNewCode() string {
	path := "//www.freesound.org/apiv2/oauth2/authorize/"

	request, err := http.NewRequest("GET", path, nil)
	if err != nil {
		panic(err)
	}

	url := request.URL
	q := url.Query()

	q.Set("client_id", CLIENT_ID)
	q.Set("response_type", "code")
	return fmt.Sprintf("//www.freesound.org/apiv2/oauth2/authorize/%v",q.Encode())
}
