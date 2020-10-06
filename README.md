# Building happiness in your life...with StackBlox
I couldn't find a simple C++ CMake/Conan build setup with continuous integration that uses the latest compilers and builds a shippable application on mobile and desktop platforms so I made one! And in the process, I also made StackBlox.

## Whoa, I didn't sign up for this code stuff, I just want to play the game!
[Get StackBlox now](http://dnqpy.com/stackblox/)
(it's free and ad-free)

## Building StackBlox
If you want to build from source, download the **latest versions** of the following tools:
*  [CMake](https://cmake.org/download/)
*  [Conan](https://conan.io/downloads.html)
*  [Ninja](https://github.com/ninja-build/ninja/releases) (for Linux and Android builds)
*  [Android NDK](https://developer.android.com/ndk/downloads)
*  [Android SDK tools](https://developer.android.com/studio) (install Android Studio for the full IDE experience)
*  On Windows: [Visual Studio](https://visualstudio.microsoft.com/vs/)
*  On Linux: [gcc](https://hub.docker.com/_/gcc)
*  On macOS: [Xcode](https://apps.apple.com/us/app/xcode/id497799835?mt=12)

Then,
1. Clone this repo
1. At the command line, `cd` to the repo
1. Run the `./cmake.py` script for the desired platform to run all or part of the build, test, and package processes. Run `./cmake.py -h` for more information.
1. Android only: You can open AndroidStudio/StackBlox from the CMake binary folder in Android Studio to build and run the app

## Continuous integration (CI)
The build process is automated through GitHub Actions, defined in the [main.yml](https://github.com/ssrobins/stackblox/blob/main/.github/workflows/main.yml) file. Nothing fancy here, it runs the same `cmake.py` script described above and archives the results.

## Docker build setups
The CI system uses custom Docker containers for Linux and Android builds. You can build and use them for the build setup or look at the Dockerfile for details steps on what to install. You can find them here:
* https://github.com/ssrobins/docker-linux-build
* https://github.com/ssrobins/docker-android-build

The .github/workflows/main.yml file in each repo defines the Docker image build process (yup, even the CI environments have a CI!).

## Conan packages
The packages directly used in StackBlox are listed in [conanfile.py](https://github.com/ssrobins/stackblox/blob/main/conanfile.py).

Those packages plus all dependencies are defined in these repos:
* https://github.com/ssrobins/conan-android_sdl2
* https://github.com/ssrobins/conan-bzip2
* https://github.com/ssrobins/conan-cmake_utils
* https://github.com/ssrobins/conan-freetype
* https://github.com/ssrobins/conan-gtest
* https://github.com/ssrobins/conan-libpng
* https://github.com/ssrobins/conan-sdl2
* https://github.com/ssrobins/conan-sdl2_image
* https://github.com/ssrobins/conan-sdl2_ttf
* https://github.com/ssrobins/conan-ssrobins_engine
* https://github.com/ssrobins/conan-zlib

The .github/workflows/main.yml file in each repo defines the Conan build/packaging process. These packages and more are publically available on https://bintray.com/stever/conan.
