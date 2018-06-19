set(target_name StackBloxPiece)

add_library(${target_name} STATIC
    Piece.cpp
    Piece.h
)

target_include_directories(${target_name}
  PUBLIC
    .
  PRIVATE
    
)

target_link_libraries(${target_name}
)
