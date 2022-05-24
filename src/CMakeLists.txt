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
    ${CONAN_STACKBLOX_ASSETS_ROOT}/assets
)

if(ANDROID)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CONAN_STACKBLOX_ASSETS_ROOT}/assets_dontship/Android/icon_48x48.png
            ${CMAKE_BINARY_DIR}/AndroidStudio/StackBlox/app/src/main/res/mipmap-mdpi/ic_launcher.png
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CONAN_STACKBLOX_ASSETS_ROOT}/assets_dontship/Android/icon_72x72.png
            ${CMAKE_BINARY_DIR}/AndroidStudio/StackBlox/app/src/main/res/mipmap-hdpi/ic_launcher.png
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CONAN_STACKBLOX_ASSETS_ROOT}/assets_dontship/Android/icon_96x96.png
            ${CMAKE_BINARY_DIR}/AndroidStudio/StackBlox/app/src/main/res/mipmap-xhdpi/ic_launcher.png
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CONAN_STACKBLOX_ASSETS_ROOT}/assets_dontship/Android/icon_144x144.png
            ${CMAKE_BINARY_DIR}/AndroidStudio/StackBlox/app/src/main/res/mipmap-xxhdpi/ic_launcher.png
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CONAN_STACKBLOX_ASSETS_ROOT}/assets_dontship/Android/icon_192x192.png
            ${CMAKE_BINARY_DIR}/AndroidStudio/StackBlox/app/src/main/res/mipmap-xxxhdpi/ic_launcher.png
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CONAN_STACKBLOX_ASSETS_ROOT}/assets_dontship/Android/icon_512x512.png
            ${CMAKE_BINARY_DIR}/AndroidStudio/StackBlox/app/src/main/ic_launcher-web.png
    )
elseif(WIN32)
    target_sources(StackBlox PRIVATE
        ${CONAN_STACKBLOX_ASSETS_ROOT}/icon.rc
    )
elseif(APPLE)
    target_assets(StackBlox
        ${CONAN_STACKBLOX_ASSETS_ROOT}/StackBlox.xcassets
    )
endif()

target_include_directories(StackBlox PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(StackBlox
    ssrobins_engine::ssrobins_engine
    StackBloxPiece
    StackBloxWell
)

install_executable(StackBlox)

add_subdirectory(Piece)
add_subdirectory(PieceTest)
add_subdirectory(Well)
add_subdirectory(WellTest)
