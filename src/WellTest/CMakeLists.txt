add_test_executable(StackBloxWellTest)

target_sources(StackBloxWellTest PRIVATE
    WellTest.cpp
)

target_include_directories(StackBloxWellTest PRIVATE
)

target_precompile_headers(StackBloxWellTest REUSE_FROM StackBloxPiece)

target_link_libraries(StackBloxWellTest
    StackBloxWell
)
