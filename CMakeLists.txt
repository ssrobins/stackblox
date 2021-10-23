cmake_minimum_required(VERSION 3.21)

if(ANDROID_ABI)
    if(NOT EXISTS $ENV{ANDROID_NDK_ROOT})
        message(FATAL_ERROR "Environment variable ANDROID_NDK_ROOT needs to point to a valid Android NDK installation")
    else()
        cmake_path(CONVERT $ENV{ANDROID_NDK_ROOT} TO_CMAKE_PATH_LIST ANDROID_NDK_ROOT NORMALIZE)
        set(CMAKE_TOOLCHAIN_FILE ${ANDROID_NDK_ROOT}/build/cmake/android.toolchain.cmake)
        message(STATUS "ANDROID_NDK_ROOT: ${ANDROID_NDK_ROOT}")
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

if(MSVC)
    string(REGEX MATCH "[0-9]+" compiler_version ${CMAKE_GENERATOR})
elseif(APPLE)
    string(REGEX MATCH "[0-9]+\.[0-9]+" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
else()
    string(REGEX MATCH "[0-9]+" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND ${compiler_version} LESS 8)
        string(REGEX MATCH "[0-9]+\.[0-9]+" compiler_version ${CMAKE_CXX_COMPILER_VERSION})
    endif()
endif()

if(ANDROID)
    set(conan_args -s os=Android -s os.api_level=${android_min_sdk_version} -s arch=${android_arch} -s compiler=clang -s compiler.version=${compiler_version} -s compiler.libcxx=c++_static)
elseif(IOS)
    set(CMAKE_OSX_ARCHITECTURES "armv7 arm64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 9.0)
    set(conan_args -s os=iOS -s arch=armv7 -s os.version=${CMAKE_OSX_DEPLOYMENT_TARGET} -s compiler.version=${compiler_version})
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
    set(conan_args -s os.version=${CMAKE_OSX_DEPLOYMENT_TARGET} -s compiler.version=${compiler_version})
elseif(UNIX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(compiler clang)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(compiler gcc)
    else()
        message("Unhandled compiler, ${CMAKE_CXX_COMPILER_ID}, Conan install command may fail")
    endif()
    set(conan_args -s compiler=${compiler} -s compiler.version=${compiler_version} -s compiler.libcxx=libstdc++11)
elseif(MSVC)
    set(conan_args -s arch=x86 -s compiler.version=${compiler_version} -s compiler.runtime=MT)
else()
    message("Unhandled platform, Conan install command may fail")
endif()

option(CONAN_BUILD_MISSING_PKGS "Build missing Conan packages" ON)
if(CONAN_BUILD_MISSING_PKGS)
    set(conan_build_option --build=missing)
endif()

execute_process(
    COMMAND conan remote add artifactory-ssrobins https://ssrobins.jfrog.io/artifactory/api/conan/conan --insert --force
    COMMAND conan install --install-folder ${CMAKE_BINARY_DIR} --update ${CMAKE_SOURCE_DIR} ${conan_build_option} ${conan_args}
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
