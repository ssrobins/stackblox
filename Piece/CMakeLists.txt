add_library(StackBloxPiece STATIC
    Piece.cpp
    Piece.h
)

target_include_directories(StackBloxPiece
  PUBLIC
    .
  PRIVATE
    
)

target_link_libraries(StackBloxPiece
)
