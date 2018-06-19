set(target_name StackBloxWellTest)

include(${CMAKE_SOURCE_DIR}/add_executable.cmake)

target_sources(${target_name} PRIVATE
    WellTest.cpp
)

target_include_directories(${target_name} PRIVATE
)

target_link_libraries(${target_name}
    StackBloxWell
)

include(${CMAKE_SOURCE_DIR}/testing.cmake)
