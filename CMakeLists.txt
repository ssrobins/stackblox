set(target_name StackBlox)

set(version_major 0)
set(version_minor 9)
set(version_patch 0)

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
    Game.h
    Game.cpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
    ${icons}
)

target_include_directories(${target_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${target_name}
    ErrorHandler
    SDL2-static
    SDL2_ttf
    StackBloxPiece
    StackBloxWell
)

set_target_properties(${target_name}
    PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(${CMAKE_SOURCE_DIR}/copy_files_to_binary_dir.cmake)

add_subdirectory(Piece)
add_subdirectory(PieceTest)
add_subdirectory(Well)
add_subdirectory(WellTest)
