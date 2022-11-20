# Building happiness in your life...with StackBlox
I couldn't find a simple C++ CMake/Conan build setup with continuous integration that uses the latest compilers and builds a shippable application on mobile and desktop platforms so I made one! And in the process, I also made StackBlox. I even did a [CppCon lightning talk](https://youtu.be/uu143M26z5E)

## Whoa, I didn't sign up for this code stuff, I just want to play the game!
[Get StackBlox now](http://dnqpy.com/stackblox/)
(it's free and ad-free)

## Building StackBlox

### Required tools
If you want to build from source, download the **latest versions** of the following tools:
*  [CMake](https://cmake.org/download/)
*  [Conan](https://conan.io/downloads.html)
*  [Ninja](https://github.com/ninja-build/ninja/releases) (for Linux and Android builds)
*  [Android NDK](https://developer.android.com/ndk/downloads)
*  [Android SDK tools](https://developer.android.com/studio) (install Android Studio for the full IDE experience)
*  On Windows: [Visual Studio](https://visualstudio.microsoft.com/vs/)
*  On Linux: [gcc](https://hub.docker.com/_/gcc)
*  On macOS: [Xcode](https://apps.apple.com/us/app/xcode/id497799835?mt=12)

Then, Clone this repo

### Build
The whole development workflow is driven by [CMake presets](
https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) to make it easy to select all the supported configurations! Presets are defined in [CMakePresets.json](CMakePresets.json). In the preset names, you'll see references to the platform name, build configuration, and `Iwyu`, which runs the [include-what-you-use](https://github.com/include-what-you-use/include-what-you-use) check.

#### Build with the CMake GUI
1. Open the CMake GUI. On macOS, make sure to open from the terminal with the command `open -a cmake` so that environment variables are loaded.
1. Click Browse Source... and navigate to the repo
1. Click the Preset dropdown and select the platform you want to build
1. Click Generate
1. For Visual Studio and Xcode, click Open Project to launch the project in the IDE. For Android, the button is grayed out, but you can open Android Studio and select the project in AndroidStudio/StackBlox from the CMake binary folder.
1. Build from the IDE as you normally would

#### Build at the command line
1. At the command line, `cd` to the repo
1. Run `cmake --workflow --list-presets` to see available presets
1. Run `cmake --workflow --preset=<preset-name>` to run the full CMake workflow for that build (example: macOS build/test/packaging with release build config would be `cmake --workflow --preset=macosRelease`).

## Continuous integration (CI)
The build process is automated through [GitHub Actions](https://github.com/features/actions), defined in the [main.yml](.github/workflows/main.yml) file. Nothing fancy here, it runs CMake's configure, build, test, and package commands and archives the results.

## Build environments
All the builds run on the Windows, Linux, and macOS build environments provided by GitHub. More information at https://github.com/actions/runner-images.

## Conan packages
The [Conan](https://conan.io/) packages directly used in StackBlox are listed in [conanfile.py](conanfile.py). For more details, check out https://github.com/ssrobins/conan-recipes.
