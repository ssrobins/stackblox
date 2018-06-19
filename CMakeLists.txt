set(target_name StackBlox)

set(version_major 1)
set(version_minor 0)
set(version_patch 3)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

include(${CMAKE_SOURCE_DIR}/add_executable.cmake)

target_sources(${target_name} PRIVATE
    Game.h
    Game.cpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
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
