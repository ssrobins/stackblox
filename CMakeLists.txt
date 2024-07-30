cmake_minimum_required(VERSION 3.25)

if(ANDROID_ABI)
    set(ANDROID_STL c++_static)
    if(EXISTS $ENV{ANDROID_NDK_ROOT})
        cmake_path(CONVERT $ENV{ANDROID_NDK_ROOT} TO_CMAKE_PATH_LIST ANDROID_NDK_ROOT NORMALIZE)
        set(CMAKE_TOOLCHAIN_FILE ${ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake)
        set(ANDROID_USE_LEGACY_TOOLCHAIN_FILE false)
    else()
        message(FATAL_ERROR "Environment variable ANDROID_NDK_ROOT needs to point to a valid Android NDK installation")
    endif()

    if(NOT EXISTS $ENV{ANDROID_SDK_ROOT})
        message(FATAL_ERROR "Environment variable ANDROID_SDK_ROOT needs to point to a valid Android SDK installation")
    endif()
    set(android_sdk_version 33)
endif()

if(ANDROID_ABI STREQUAL armeabi-v7a)
    set(android_min_sdk_version 19)
    set(ANDROID_PLATFORM android-${android_min_sdk_version})
    set(version_code 36)
elseif(ANDROID_ABI STREQUAL arm64-v8a)
    set(android_min_sdk_version 21)
    set(ANDROID_PLATFORM android-${android_min_sdk_version})
    set(version_code 37)
endif()

find_package(Python3 REQUIRED)
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/export_conan_recipes.py
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE conan_export_result
)
if(conan_export_result)
    message(FATAL_ERROR "Conan export error")
endif()

list(APPEND CONAN_INSTALL_ARGS
    "--build=missing"
    "--conf=tools.system.package_manager:mode=install"
    "--conf=tools.system.package_manager:sudo=True"
    "--conf=tools.cmake.cmaketoolchain:generator=Ninja Multi-Config"
)

option(CONAN_UPDATE "Check for newer Conan packages" OFF)
if(CONAN_UPDATE)
    list(APPEND CONAN_INSTALL_ARGS "--update")
endif()

set(conan_provider_file "${CMAKE_BINARY_DIR}/conan_provider.cmake")
if(NOT EXISTS "${conan_provider_file}")
    message(STATUS "Downloading conan_provider.cmake")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/develop2/conan_provider.cmake"
        "${conan_provider_file}"
        TLS_VERIFY ON)
endif()
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${conan_provider_file}")

project(StackBlox VERSION 1.3.1)

include(cmake/global_settings.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OPTIMIZE_DEPENDENCIES true)

if(CMAKE_CXX_INCLUDE_WHAT_YOU_USE)
    find_program(iwyu_path include-what-you-use)
    if(NOT iwyu_path)
        message(FATAL_ERROR "include-what-you-use binary not found")
    endif()
endif()

if(IOS)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 11.0)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    set(bluetooth_statement "App uses the SDL2 library, which supports Bluetooth controllers, but it's not currently used. No data is being collected!")
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

find_package(GTest REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Helper functions
include(cmake/add_executable_custom.cmake)
include(cmake/add_sdl_executable.cmake)
include(cmake/add_test_executable.cmake)
include(cmake/install_executable.cmake)
include(cmake/target_assets.cmake)

enable_testing()

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StackBlox)

set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_${platform})
include(CPack)
