add_library(Display STATIC
    Display.cpp
    Display.h
)

set_target_properties(Display PROPERTIES DEBUG_POSTFIX d)

target_include_directories(Display
  PUBLIC
    .
  PRIVATE
    
)

target_link_libraries(Display
)
