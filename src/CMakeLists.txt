project(StackBlox VERSION 1.1.1)

if("${ANDROID_ABI}" STREQUAL "armeabi-v7a")
    set(version_code 14)
elseif("${ANDROID_ABI}" STREQUAL "arm64-v8a")
    set(version_code 15)
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

add_sdl2_executable(StackBlox)

target_sources(StackBlox PRIVATE
    StackBlox.h
    StackBlox.cpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

if(WIN32)
    target_sources(StackBlox PRIVATE
        icon.rc
    )
elseif(IOS)
    set(icons
        StackBlox.xcassets/AppIcon.appiconset/AppIcon1024x1024~ios-marketing.png
        StackBlox.xcassets/AppIcon.appiconset/AppIcon60x60@2x.png
        StackBlox.xcassets/AppIcon.appiconset/AppIcon76x76@2x~ipad.png
        StackBlox.xcassets/AppIcon.appiconset/AppIcon76x76~ipad.png
        StackBlox.xcassets/AppIcon.appiconset/AppIcon83.5x83.5@2x~ipad.png
    )

    target_sources(StackBlox PRIVATE
        ${icons}
    )

    set_target_properties(StackBlox PROPERTIES
        RESOURCE "${icons}"
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

if(WIN32)
    set_target_properties(StackBlox PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
elseif(APPLE AND NOT IOS)
    set_target_properties(StackBlox PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
    )
endif()

install_executable(StackBlox)

add_subdirectory(Piece)
add_subdirectory(PieceTest)
add_subdirectory(Well)
add_subdirectory(WellTest)
