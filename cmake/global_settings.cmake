set(company dnqpy)

if(IOS)
    set(xcode_code_sign_identity "iPhone Developer")
elseif(APPLE)
    set(xcode_code_sign_identity "Developer ID Application")
endif()
if(APPLE)
    set(xcode_dev_team MLPC343Q5F)
    set(MACOSX_BUNDLE_BUNDLE_NAME "\${PRODUCT_NAME:identifier}")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.${company}.\${PRODUCT_NAME:identifier}")
endif()

if(MSVC)
    add_compile_options(
        $<$<CONFIG:Release>:/GL> # Whole program optimization
        $<$<CONFIG:Release>:/Gy> # Enable function-level linking
        /MP # Multi-processor compilation
        $<$<CONFIG:Release>:/Oi> # Generate intrinsic functions
        /permissive- # Standard C++ conformance
        /sdl # Enable additional security checks
        /WX # Warning as error
        $<$<CONFIG:Debug>:/ZI> # Produces a program database (PDB) that supports edit and continue
        $<$<CONFIG:Release>:/Zi> # Produces a program database (PDB)
    )

    add_link_options(
        $<$<CONFIG:Release>:/DEBUG> # Generate debug information
        $<$<CONFIG:Release>:/LTCG:incremental> # Link-time code generation
        $<$<CONFIG:Release>:/OPT:ICF> # Perform identical COMDAT folding
        $<$<CONFIG:Release>:/OPT:REF> # Eliminates functions and/or data that are never referenced
        /SAFESEH:NO # Don't produce an image with a table of safe exceptions handlers
        /WX # Warning as error
    )

    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    add_compile_options(
        -Werror # Warning as error
    )
    add_link_options(
        -Werror # Warning as error
    )
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_link_options(
        -static-libgcc
        -static-libstdc++
    )
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Allow organizing source files into subdirectories
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
define_property(
    TARGET
    PROPERTY FOLDER
    INHERITED
    BRIEF_DOCS "Set the folder name."
    FULL_DOCS  "Use to organize targets in an IDE."
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(bitness 64)
else()
    set(bitness 32)
endif()

if(ANDROID)
    set(CPACK_GENERATOR External)
    set(CPACK_EXTERNAL_PACKAGE_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/package_android_apk.cmake)
    set(CPACK_EXTERNAL_ENABLE_STAGING true)
    set(CPACK_BUILD_CONFIG ${CMAKE_BUILD_TYPE})
    set(platform Android)
    set(CPACK_ANDROID_ABI ${ANDROID_ABI})
elseif(IOS)
    set(CPACK_GENERATOR External)
    set(CPACK_EXTERNAL_PACKAGE_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/package_ios_ipa.cmake)
    set(CPACK_EXTERNAL_ENABLE_STAGING true)
    set(platform iOS)
elseif(APPLE)
    set(CPACK_GENERATOR ZIP)
    set(platform macOS)
elseif(WIN32)
    set(CPACK_GENERATOR ZIP)
    set(platform Windows)
else()
    set(CPACK_GENERATOR TGZ)
    set(platform Linux${bitness})
endif()

# Settings for install and packaging
if(IOS)
    # Ensure iOS 'archive' step can locate dependent libraries for linking
    # without running the build first
    # https://stackoverflow.com/questions/33020245
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY .)
endif()
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/_install)
set(CPACK_PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/_package/\${CPACK_BUILD_CONFIG})
set(CPACK_COMPONENTS_GROUPING IGNORE)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
