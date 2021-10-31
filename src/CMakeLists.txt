add_sdl2_executable(StackBlox MACOSX_BUNDLE WIN32)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

target_sources(StackBlox PRIVATE
    StackBlox.h
    StackBlox.cpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

target_assets(StackBlox
    assets
)

if(WIN32)
    target_sources(StackBlox PRIVATE
        icon.rc
    )
elseif(APPLE AND NOT IOS)
    target_assets(StackBlox
        icon.icns
    )
    set_target_properties(StackBlox PROPERTIES
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
    )
elseif(IOS)
    target_assets(StackBlox
        StackBlox.xcassets
    )
endif()

target_include_directories(StackBlox PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(StackBlox
    CONAN_PKG::ssrobins_engine
    StackBloxPiece
    StackBloxWell
)

install_executable(StackBlox)

add_subdirectory(Piece)
add_subdirectory(PieceTest)
add_subdirectory(Well)
add_subdirectory(WellTest)
