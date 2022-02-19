add_library(StackBloxWell STATIC
    Well.cpp
    Well.h
)

target_include_directories(StackBloxWell
  PUBLIC
    .
  PRIVATE
    
)

target_precompile_headers(StackBloxWell REUSE_FROM StackBloxPiece)

target_link_libraries(StackBloxWell
    StackBloxPiece
)
