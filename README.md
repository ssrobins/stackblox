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
*  On Windows: [Visual Studio 2019](https://visualstudio.microsoft.com/vs/)
*  On Linux: [gcc 9](https://hub.docker.com/_/gcc)
*  On macOS: [Xcode 11](https://apps.apple.com/us/app/xcode/id497799835?mt=12)

Then,
1. Clone this repo
1. At the command line, `cd` to the repo
1. Run the `build_*` script for the desired platform to run the full build process

## Continuous integration (CI)
The build process is automated through GitLab's built-in CI, defined in the [.gitlab-ci.yml](https://gitlab.com/ssrobins/stackblox/blob/master/.gitlab-ci.yml) file. Nothing fancy here, it runs the same `build_*` scripts described above and archives the results.

## Docker build setups
The CI system uses custom Docker containers for Linux and Android builds. You can build and use them for the build setup or look at the Dockerfile for details steps on what to install. You can find them here:
* https://gitlab.com/ssrobins/docker-linux-build
* https://gitlab.com/ssrobins/docker-android-build

I also have a Windows-based Docker, though it's not hooked up to the CI yet:
* https://gitlab.com/ssrobins/docker-windows-build

The .gitlab-ci.yml file in each repo defines the Docker image build process (yup, even the CI environments have a CI!).

## Conan packages
The packages directly used in StackBlox are listed in [conanfile.py](https://gitlab.com/ssrobins/stackblox/blob/master/conanfile.py).

Those packages plus all dependencies are defined in these repos:
* https://gitlab.com/ssrobins/conan-android_sdl2
* https://gitlab.com/ssrobins/conan-bzip2
* https://gitlab.com/ssrobins/conan-cmake_utils
* https://gitlab.com/ssrobins/conan-freetype
* https://gitlab.com/ssrobins/conan-gtest
* https://gitlab.com/ssrobins/conan-libpng
* https://gitlab.com/ssrobins/conan-sdl2
* https://gitlab.com/ssrobins/conan-sdl2_image
* https://gitlab.com/ssrobins/conan-sdl2_ttf
* https://gitlab.com/ssrobins/conan-ssrobins_engine
* https://gitlab.com/ssrobins/conan-zlib

The .gitlab-ci.yml file in each repo defines the Conan build/packaging process. These packages and more are publically available on https://bintray.com/stever/conan.
