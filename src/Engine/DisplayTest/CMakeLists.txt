add_test_executable(DisplayTest)

target_sources(DisplayTest PRIVATE
    DisplayTest.cpp
)

target_include_directories(DisplayTest PRIVATE
)

target_link_libraries(DisplayTest
    Display
)
