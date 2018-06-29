set(target_name StackBloxDisplayTest)

include(${CMAKE_SOURCE_DIR}/add_executable.cmake)

target_sources(${target_name} PRIVATE
    DisplayTest.cpp
)

target_include_directories(${target_name} PRIVATE
)

target_link_libraries(${target_name}
    StackBloxDisplay
)

include(${CMAKE_SOURCE_DIR}/testing.cmake)
