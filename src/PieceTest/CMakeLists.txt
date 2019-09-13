add_test_executable(StackBloxPieceTest)

target_sources(StackBloxPieceTest PRIVATE
    PieceTest.cpp
)

target_include_directories(StackBloxPieceTest PRIVATE
)

target_link_libraries(StackBloxPieceTest
    StackBloxPiece
)
