# Building happiness in your life...with StackBlox
I couldn't find a simple C++ CMake/Conan build setup with continuous integration that uses the latest compilers and builds a shippable application on mobile and desktop platforms so I made one! And in the process, I also made StackBlox.

## Whoa, I didn't sign up for this code stuff, I just want to play the game!
[Get StackBlox now](http://dnqpy.com/stackblox/)
(it's free and ad-free)

## Building StackBlox
If you want to build from source, you'll need the following tools installed:
*  [CMake](https://cmake.org/download/) (Download directly from CMake, your favorite package manager may not have a new enough version)
*  [Conan](https://conan.io/downloads.html)
*  [Android NDK](https://developer.android.com/ndk/downloads)
*  [Android SDK tools](https://developer.android.com/studio) (install Android Studio for the full IDE experience)
*  On Windows: [Visual Studio 2019](https://visualstudio.microsoft.com/vs/)
*  On Linux: [gcc 9](https://hub.docker.com/_/gcc)
*  On macOS: [Xcode 10](https://apps.apple.com/us/app/xcode/id497799835?mt=12)

Clone this repo and run the `build_` script from the main directory to build.

## Continuous integration (CI)
The build process is automated through GitLab's built-in CI, defined in the [.gitlab-ci.yml](https://gitlab.com/ssrobins/stackblox/blob/master/.gitlab-ci.yml) file. Nothing fancy here, it runs the same `build_` script scripts described above and archives the results.

## Docker build setups
The CI system uses custom Docker containers for Linux and Android builds. You can build and use them for the build setup or look at the Dockerfile for details steps on what to install. You can find them here:
* https://gitlab.com/ssrobins/docker-linux-build
* https://gitlab.com/ssrobins/docker-android-build

I also have a Windows-based Docker, though it's not hooked up to the CI yet:
* https://gitlab.com/ssrobins/docker-windows-build

The .gitlab-ci.yml file in each repo describes the Docker image build process (yup, even the CI environments have a CI!).

## Conan packages
The packages used in StackBlox are listed in [conanfile.py](https://gitlab.com/ssrobins/stackblox/blob/master/conanfile.py).

I build and publish the packages from here:
* https://gitlab.com/ssrobins/conan-gtest
* https://gitlab.com/ssrobins/conan-sdl2
* https://gitlab.com/ssrobins/conan-sdl2_image
* https://gitlab.com/ssrobins/conan-sdl2_ttf

These packages and more are publically available on https://bintray.com/stever/conan.
