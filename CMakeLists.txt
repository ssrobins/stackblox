set(target_name StackBlox)

set(version_major 1)
set(version_minor 0)
set(version_patch 0)
if(ANDROID)
    set(version_code 2)
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

set(icons
    StackBlox.xcassets/AppIcon.appiconset/Icon76x76.png
    StackBlox.xcassets/AppIcon.appiconset/Icon120x120.png
    StackBlox.xcassets/AppIcon.appiconset/Icon152x152.png
    StackBlox.xcassets/AppIcon.appiconset/Icon167x167.png
    StackBlox.xcassets/AppIcon.appiconset/Icon1024x1024.png
)

include(${CMAKE_SOURCE_DIR}/add_executable.cmake)

target_sources(${target_name} PRIVATE
    StackBlox.h
    StackBlox.cpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)
if(WIN32)
    target_sources(${target_name} PRIVATE
        icon.rc
    )
elseif(IOS)
    target_sources(${target_name} PRIVATE
        ${icons}
    )
endif()

target_include_directories(${target_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${target_name}
    Display
    ErrorHandler
    SDL2-static
    SDL2_image
    SDL2_ttf
    StackBloxPiece
    StackBloxWell
)

if(WIN32)
    set_target_properties(${target_name}
        PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
elseif(APPLE AND NOT IOS)
    set_target_properties(${target_name}
        PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
    )
endif()

include(${CMAKE_SOURCE_DIR}/copy_files_to_binary_dir.cmake)

add_subdirectory(Piece)
add_subdirectory(PieceTest)
add_subdirectory(Well)
add_subdirectory(WellTest)
