Atmosfear
=========

Atmosfear was a project for [MidiHack 2015][midihack], written by [Daniel
Swärd][daniel], [Rickard Lindroth][rickard], and [Nik Reiman][nik]. It is a VSTi
plugin which generates random atmospheric soundscapes with samples scraped from
FreeSound. We had originally imagined that the plugin colud generate soundscapes
resembling parks, public places, nature, etc. However, the resulting sounds that it
makes are generally quite surreal and creepy, hence the name. :)

The plugin right now is a bit proof-of-concept, since the whole thing was written in
less than 24 hours and doesn't have a GUI. But if you really want to try it out,
here's how:

- Build the plugin for your respective operating system (sorry, no Windows support
  yet).
- Run the "scraper" tool to fetch samples for a given keyword:

```
$ cd Scraper
$ go run scraper.go -v=true -q="car crash"
```

- Copy the resulting files from `tmp/<timestamp>` to `/tmp/foo/voiceN`, where `N` is a
  number 0-7.

When you run the plugin, it will choose samples from the `voiceN` directories at
random intervals and mix them together.


Future goals
------------

A GUI would be nice to specify keywords and actually run the scraper for you.


[midihack]: http://midihack.com/
[daniel]: https://github.com/Excds
[rickard]: https://github.com/lindroth
[nik]: https://github.com/nikreiman
