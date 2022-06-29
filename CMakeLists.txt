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
    set(android_sdk_version 32)
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

project(StackBlox VERSION 1.2.4)

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
    set(conan_args  -s os=Android -s os.api_level=${android_min_sdk_version} -s arch=${android_arch} -s compiler=clang -s compiler.version=${compiler_version} -s compiler.libcxx=c++_static -s compiler.cppstd=${CMAKE_CXX_STANDARD})
elseif(IOS)
    set(CMAKE_OSX_ARCHITECTURES "armv7 arm64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 9.0)
    set(conan_args -s os=iOS -s arch=armv7 -s os.sdk=iphoneos -s os.version=${CMAKE_OSX_DEPLOYMENT_TARGET} -s compiler=apple-clang -s compiler.libcxx=libc++ -s compiler.version=${compiler_version} -s compiler.cppstd=${CMAKE_CXX_STANDARD})
    set(bluetooth_statement "App uses the SDL2 library, which supports Bluetooth controllers, but it's not currently used. No data is being collected!")
elseif(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(conan_arch "armv8")
    else()
        set(conan_arch ${CMAKE_SYSTEM_PROCESSOR})
    endif()
    set(conan_args -s os=Macos -s arch=${conan_arch} -s os.version=${CMAKE_OSX_DEPLOYMENT_TARGET} -s compiler=apple-clang -s compiler.libcxx=libc++ -s compiler.version=${compiler_version} -s compiler.cppstd=${CMAKE_CXX_STANDARD})
elseif(UNIX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(compiler clang)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(compiler gcc)
    else()
        message("Unhandled compiler, ${CMAKE_CXX_COMPILER_ID}, Conan install command may fail")
    endif()
    set(conan_args -s os=Linux -s arch=${CMAKE_SYSTEM_PROCESSOR} -s compiler=${compiler} -s compiler.version=${compiler_version} -s compiler.libcxx=libstdc++11 -s compiler.cppstd=${CMAKE_CXX_STANDARD})
elseif(MSVC)
    set(conan_args -s os=Windows -s arch=x86 -s compiler=msvc -s compiler.version=${compiler_version} -s compiler.runtime=static -s compiler.cppstd=${CMAKE_CXX_STANDARD})
else()
    message("Unhandled platform, Conan install command may fail")
endif()

execute_process(
    COMMAND conan --version
    ERROR_QUIET
    OUTPUT_VARIABLE conan_output
    RESULT_VARIABLE conan_result
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(conan_result)
    message(FATAL_ERROR "Conan not found, is it installed?")
elseif(conan_output MATCHES 1.)
    message(FATAL_ERROR "Conan 1.x found, you must install Conan 2.x.")
endif()

option(CONAN_BUILD_MISSING_PKGS "Build missing Conan packages" ON)
if(CONAN_BUILD_MISSING_PKGS)
    set(conan_build_option --build=missing)
endif()

set(conan_remote_name artifactory-ssrobins)
set(conan_remote_url https://ssrobins.jfrog.io/artifactory/api/conan/conan)
execute_process(
    COMMAND conan remote update ${conan_remote_name} --url ${conan_remote_url}
    ERROR_QUIET
    RESULT_VARIABLE conan_result
)
if(conan_result)
    execute_process(
        COMMAND conan remote add ${conan_remote_name} ${conan_remote_url}
        RESULT_VARIABLE conan_result
    )
    if(conan_result)
        message(FATAL_ERROR "Conan error")
    endif()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
    execute_process(
        COMMAND conan install --output-folder ${CMAKE_BINARY_DIR} --remote ${conan_remote_name} --update ${CMAKE_SOURCE_DIR} ${conan_build_option} ${conan_args} -s build_type=${TYPE} -pr:b ${CMAKE_SOURCE_DIR}/profile.jinja -pr:h ${CMAKE_SOURCE_DIR}/profile.jinja
        RESULT_VARIABLE conan_result
    )
    if(conan_result)
        message(FATAL_ERROR "Conan error")
    endif()
endforeach()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_BINARY_DIR})

find_package(cmake_utils REQUIRED)
find_package(gtest REQUIRED)
find_package(ssrobins_engine REQUIRED)

include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/global_settings.cmake)

# Helper functions
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/add_executable_custom.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/add_sdl_executable.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/add_test_executable.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/install_executable.cmake)
include(${cmake_utils_PACKAGE_FOLDER_RELEASE}/target_assets.cmake)

enable_testing()

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StackBlox)

set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_${platform})
include(CPack)
