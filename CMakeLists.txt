cmake_minimum_required(VERSION 3.21)

if(ANDROID_ABI)
    if(NOT EXISTS $ENV{ANDROID_NDK_ROOT})
        message(FATAL_ERROR "Environment variable ANDROID_NDK_ROOT needs to point to a valid Android NDK installation")
    else()
        cmake_path(CONVERT $ENV{ANDROID_NDK_ROOT} TO_CMAKE_PATH_LIST ANDROID_NDK_ROOT NORMALIZE)
        set(CMAKE_TOOLCHAIN_FILE ${ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake)
    endif()

    if(NOT EXISTS $ENV{ANDROID_SDK_ROOT})
        message(FATAL_ERROR "Environment variable ANDROID_SDK_ROOT needs to point to a valid Android SDK installation")
    endif()
    set(android_sdk_version 31)
endif()

if(ANDROID_ABI STREQUAL armeabi-v7a)
    set(android_min_sdk_version 16)
    set(ANDROID_PLATFORM android-${android_min_sdk_version})
    set(version_code 26)
    set(android_arch armv7)
elseif(ANDROID_ABI STREQUAL arm64-v8a)
    set(android_min_sdk_version 21)
    set(ANDROID_PLATFORM android-${android_min_sdk_version})
    set(version_code 27)
    set(android_arch armv8)
endif()

project(StackBlox VERSION 1.2.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    string(REGEX MATCH "[0-9]+\.[0-9]+" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
elseif(MSVC)
    string(REGEX MATCH "[0-9]+\.[0-9]" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
    string(REPLACE "." "" compiler_version ${compiler_version})
else()
    string(REGEX MATCH "[0-9]+" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND ${compiler_version} LESS 8)
        string(REGEX MATCH "[0-9]+\.[0-9]+" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
    endif()
endif()

if(ANDROID)
    set(conan_args os=Android;os.api_level=${android_min_sdk_version};arch=${android_arch};compiler=clang;compiler.version=${compiler_version};compiler.libcxx=c++_static;compiler.cppstd=${CMAKE_CXX_STANDARD})
elseif(IOS)
    set(CMAKE_OSX_ARCHITECTURES "armv7 arm64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 9.0)
    set(conan_args os=iOS;arch=armv7;os.version=${CMAKE_OSX_DEPLOYMENT_TARGET};compiler.version=${compiler_version};compiler.cppstd=${CMAKE_CXX_STANDARD})
    set(bluetooth_statement "App uses the SDL2 library, which supports Bluetooth controllers, but it's not currently used. No data is being collected!")
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
    set(conan_args os.version=${CMAKE_OSX_DEPLOYMENT_TARGET};compiler.version=${compiler_version};compiler.cppstd=${CMAKE_CXX_STANDARD})
elseif(UNIX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(compiler clang)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(compiler gcc)
    else()
        message("Unhandled compiler, ${CMAKE_CXX_COMPILER_ID}, Conan install command may fail")
    endif()
    set(conan_args compiler=${compiler};compiler.version=${compiler_version};compiler.libcxx=libstdc++11;compiler.cppstd=${CMAKE_CXX_STANDARD})
elseif(MSVC)
    set(conan_args arch=x86;compiler=msvc;compiler.version=${compiler_version};compiler.runtime=static;compiler.cppstd=${CMAKE_CXX_STANDARD})
else()
    message("Unhandled platform, Conan install command may fail")
endif()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

option(CONAN_BUILD_MISSING_PKGS "Build missing Conan packages" ON)
if(CONAN_BUILD_MISSING_PKGS)
    set(conan_build_option missing)
endif()

conan_add_remote(NAME artifactory-ssrobins
    INDEX 0
    URL https://ssrobins.jfrog.io/artifactory/api/conan/conan
    VERIFY_SSL True)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
    conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR}
        BUILD ${conan_build_option}
        UPDATE
        SETTINGS ${conan_args};build_type=${TYPE})
endforeach()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_FIND_ROOT_PATH ${CMAKE_BINARY_DIR})

find_package(cmake_utils REQUIRED)
find_package(gtest REQUIRED)
find_package(ssrobins_engine REQUIRED)
find_package(stackblox_assets REQUIRED)

include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/global_settings.cmake)

# Helper functions
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/add_executable_custom.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/add_sdl2_executable.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/add_test_executable.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/install_executable.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/target_assets.cmake)

enable_testing()

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StackBlox)

set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_${platform})
include(CPack)
