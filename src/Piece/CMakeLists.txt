add_library(StackBloxPiece STATIC
    Piece.cpp
    Piece.h
)

target_include_directories(StackBloxPiece
  PUBLIC
    .
  PRIVATE
    
)

target_precompile_headers(StackBloxPiece REUSE_FROM StackBloxPiece)

target_link_libraries(StackBloxPiece
)
