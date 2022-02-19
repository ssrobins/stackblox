add_test_executable(StackBloxPieceTest)

target_sources(StackBloxPieceTest PRIVATE
    PieceTest.cpp
)

target_include_directories(StackBloxPieceTest PRIVATE
)

target_precompile_headers(StackBloxPieceTest REUSE_FROM StackBloxPiece)

target_link_libraries(StackBloxPieceTest
    StackBloxPiece
)
