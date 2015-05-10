package main

import (
	"./freesound"
	"fmt"
	"os"
	"io"
	"flag"
	"time"
)

var oaFlag = flag.Bool("oa", false, "Use this to get the url for oauth")
var queryFlag = flag.String("q", "", "Query strings \"car crash\" separated by space")
var verboseFlag = flag.Bool("v", false, "Verbose mode")

const (
	TMP_DIRECTORY = "tmp"
)
func main() {
	flag.Parse()

	if oaFlag != nil && *oaFlag {
		fmt.Printf("Dowload url: %v \v", freesound.GetNewCode())
		return
	}

	if queryFlag == nil || *queryFlag == ""{
		fmt.Printf("You must suply the -q flag!")
		return
	}

	searchResponse, err := freesound.Search(*queryFlag, "", "", true)
	if err != nil {
		panic(err)
	}

	if err := os.MkdirAll(TMP_DIRECTORY, 0777); err != nil {
		panic(err)
	}

	newDir := fmt.Sprintf("%v/%v",TMP_DIRECTORY, time.Now().Unix())
	os.Mkdir(newDir, 0777)

	for _, hit := range searchResponse.Results {
		log(fmt.Sprintf("%v, %v \n", hit.Name, hit.Type))
		download(hit, newDir)
		//return
	}
}

func download(sound freesound.Sound, path string) {
	log(fmt.Sprintf("Downloading url:%v ", sound.Download))

	out, err := os.Create(fmt.Sprintf("%v/%v", path, sound.Name))
	if err != nil {
		panic(err)
	}

	defer out.Close()

	request, err := freesound.OA2AuthorizedRequest(sound.Download)
	if err != nil {
		panic(err)
	}

	resp, err := freesound.Do(request)
	if err != nil {
		panic(err)
	}

	if resp.StatusCode != 200 {
		fmt.Printf("Somethings is wrong %+v", resp)
	}

	defer resp.Body.Close()

	bytesRead, err := io.Copy(out, resp.Body)
	if err != nil {
		panic(err)
	}
	log(fmt.Sprintf("Wrote %v bytes", bytesRead))
}

func log(msg string) {
	if verboseFlag != nil && *verboseFlag {
		fmt.Println(msg)
	}
}
