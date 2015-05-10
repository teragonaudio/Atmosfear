Directory structure
===================

Atmosfear needs to see the Juce and VST SDK sources. It assumes that they
are checked out in a directory called `sdk` above the project subdirectory
which contains its own sources. In other words:

    /wherever/path/to/Code
    ├── sdk
    │   ├── juce
    │   └── vstsdk2.4
    ├── teragon
    │   ├── Atmosfear

In the `juce` subdirectory should be a clone of [Juce][juce], and in the
`vstsdk2.4` directory the uncompressed [VST SDK 2.4 sources][vst]. Don't
forget to run `git submodule sync && git submodule --init --recursive`
after cloning.


Build dependencies
------------------

* CMake 2.8 or newer
* Xcode, and optionally [CLion][clion] for building on Mac OSX
* [CLion][clion] for building on Linux
* [MrsWatson][mrswatson] for running tests
* Introjucer, which can be built from within the `extras/Introducer`
  subdirectory of the Juce source tree.
* Extra dependencies with Ubuntu:
  `sudo apt-get install libx11-dev libxinerama-dev libfreetype6-dev libxcursor-dev`



Building with an IDE
--------------------

An Xcode project file is provided by Introducer and can be found in the
`Builds/MacOSX` subdirectory. Point CLion to the project's top-level
`CMakeLists.txt` when opening the project.

Note that the CMakeJuce configuration creates two targets,
`build_Atmosfear` and `virtual_Atmosfear`. Use the `build_Atmosfear`
target, as it uses the external builder from the Introjucer project. The
`virtual_Atmosfear` target is only needed so that the IDE correctly sees
and indexes the project sources, but it will probably not build correctly.


Building with CMake
-------------------

For a vanilla CMake build, the steps look something like this:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make build_Atmosfear

Note that passing `-j` to make is not necessary, the CMakeJuce toolchain
determines this for you.


[juce]: https://github.com/julianstorer/JUCE
[vst]: http://www.steinberg.net/nc/en/company/developer/sdk_download_portal.html
[clion]: https://www.jetbrains.com/clion
[mrswatson]: http://teragonaudio.com/MrsWatson.html
