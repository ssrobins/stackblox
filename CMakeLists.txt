cmake_minimum_required(VERSION 3.14)

project(StackBlox VERSION 1.1.1)

if("${ANDROID_ABI}" STREQUAL "armeabi-v7a")
    set(version_code 14)
elseif("${ANDROID_ABI}" STREQUAL "arm64-v8a")
    set(version_code 15)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)

include(${CONAN_SSROBINS_ENGINE_ROOT}/cmake/global_settings.cmake)

# Helper functions
include(${CONAN_SSROBINS_ENGINE_ROOT}/cmake/add_executable_custom.cmake)
include(${CONAN_SSROBINS_ENGINE_ROOT}/cmake/add_sdl2_executable.cmake)
include(${CONAN_SSROBINS_ENGINE_ROOT}/cmake/add_test_executable.cmake)
include(${CONAN_SSROBINS_ENGINE_ROOT}/cmake/install_executable.cmake)

enable_testing()

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT StackBlox)

set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}_${PROJECT_VERSION}_${platform})
include(CPack)