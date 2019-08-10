set(target_name StackBlox)

set(version_major 1)
set(version_minor 1)
set(version_patch 1)
if("${ANDROID_ABI}" STREQUAL "armeabi-v7a")
    set(version_code 14)
elseif("${ANDROID_ABI}" STREQUAL "arm64-v8a")
    set(version_code 15)
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

set(icons
    StackBlox.xcassets/AppIcon.appiconset/AppIcon1024x1024~ios-marketing.png
    StackBlox.xcassets/AppIcon.appiconset/AppIcon60x60@2x.png
    StackBlox.xcassets/AppIcon.appiconset/AppIcon76x76@2x~ipad.png
    StackBlox.xcassets/AppIcon.appiconset/AppIcon76x76~ipad.png
    StackBlox.xcassets/AppIcon.appiconset/AppIcon83.5x83.5@2x~ipad.png
)

add_sdl2_executable(${target_name})

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
    Game
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

install_executable(${target_name})

add_subdirectory(Piece)
add_subdirectory(PieceTest)
add_subdirectory(Well)
add_subdirectory(WellTest)
