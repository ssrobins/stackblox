set(target_name StackBloxWellTest)

add_test_executable(${target_name})

target_sources(${target_name} PRIVATE
    WellTest.cpp
)

target_include_directories(${target_name} PRIVATE
)

target_link_libraries(${target_name}
    StackBloxWell
)
