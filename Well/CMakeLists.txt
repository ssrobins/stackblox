set(target_name StackBloxWell)

add_library(${target_name} STATIC
    Well.cpp
    Well.h
)

target_include_directories(${target_name}
  PUBLIC
    .
  PRIVATE
    
)

target_link_libraries(${target_name}
    StackBloxPiece
)
