add_library(ErrorHandler STATIC
    ErrorHandler.cpp
    ErrorHandler.h
    Exceptions.h
)

set_target_properties(ErrorHandler PROPERTIES DEBUG_POSTFIX d)

target_include_directories(ErrorHandler
  PUBLIC
    .
  PRIVATE
    
)

target_link_libraries(ErrorHandler
    SDL2::SDL2-static
)
