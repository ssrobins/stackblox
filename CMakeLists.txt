cmake_minimum_required(VERSION 3.19)

if(ANDROID_ABI)
    if(NOT EXISTS $ENV{ANDROID_NDK_ROOT})
        message(FATAL_ERROR "Environment variable ANDROID_NDK_ROOT needs to point to a valid Android NDK installation")
    else()
        set(CMAKE_TOOLCHAIN_FILE $ENV{ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake)
    endif()

    if(NOT EXISTS $ENV{ANDROID_SDK_ROOT})
        message(FATAL_ERROR "Environment variable ANDROID_SDK_ROOT needs to point to a valid Android SDK installation")
    endif()
endif()

if(ANDROID_ABI STREQUAL armeabi-v7a)
    set(android_min_sdk_version 16)
    set(ANDROID_PLATFORM android-${android_min_sdk_version})
    set(version_code 14)
    set(android_arch armv7)
elseif(ANDROID_ABI STREQUAL arm64-v8a)
    set(android_min_sdk_version 21)
    set(ANDROID_PLATFORM android-${android_min_sdk_version})
    set(version_code 15)
    set(android_arch armv8)
endif()

project(StackBlox VERSION 1.1.7)

if(ANDROID)
    set(conan_args -s os=Android -s os.api_level=${android_min_sdk_version} -s arch=${android_arch} -s compiler=clang -s compiler.version=12 -s compiler.libcxx=c++_static)
elseif(IOS)
    set(CMAKE_OSX_ARCHITECTURES "armv7 arm64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 9.0)
    set(conan_args -s os=iOS -s arch=armv7 -s os.version=${CMAKE_OSX_DEPLOYMENT_TARGET})
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
    set(conan_args -s os.version=${CMAKE_OSX_DEPLOYMENT_TARGET})
elseif(UNIX)
    set(conan_args -s compiler.libcxx=libstdc++11)
elseif(WIN32)
    set(conan_args -s arch=x86 -s compiler.version=16 -s compiler.runtime=MT)
endif()

execute_process(
    COMMAND conan remote add artifactory-ssrobins https://ssrobins.jfrog.io/artifactory/api/conan/conan --insert --force
    COMMAND conan install --install-folder ${CMAKE_BINARY_DIR} --update ${CMAKE_SOURCE_DIR} --build=missing ${conan_args}
    RESULT_VARIABLE conan_result
)
if(conan_result)
    message(FATAL_ERROR "Conan error")
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

include(${CONAN_CMAKE_UTILS_ROOT}/global_settings.cmake)

# Helper functions
include(${CONAN_CMAKE_UTILS_ROOT}/add_executable_custom.cmake)
include(${CONAN_CMAKE_UTILS_ROOT}/add_sdl2_executable.cmake)
include(${CONAN_CMAKE_UTILS_ROOT}/add_test_executable.cmake)
include(${CONAN_CMAKE_UTILS_ROOT}/install_executable.cmake)
include(${CONAN_CMAKE_UTILS_ROOT}/target_assets.cmake)

enable_testing()

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StackBlox)

set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_${platform})
include(CPack)
