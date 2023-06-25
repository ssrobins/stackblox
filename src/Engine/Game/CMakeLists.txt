add_library(Game STATIC
    Game.cpp
    Game.h
)

set_target_properties(Game PROPERTIES DEBUG_POSTFIX d)

target_include_directories(Game
  PUBLIC
    .
  PRIVATE
    
)

target_link_libraries(Game
    Display
    ErrorHandler
    SDL2::SDL2-static
    sdl_image::sdl_image
    sdl_mixer::sdl_mixer
    sdl_ttf::sdl_ttf
)
