add_test_executable(StackBloxWellTest)

target_sources(StackBloxWellTest PRIVATE
    WellTest.cpp
)

target_include_directories(StackBloxWellTest PRIVATE
)

target_link_libraries(StackBloxWellTest
    StackBloxWell
)
