set(target_name StackBloxPieceTest)

include(${CMAKE_SOURCE_DIR}/add_executable.cmake)

target_sources(${target_name} PRIVATE
    PieceTest.cpp
)

target_include_directories(${target_name} PRIVATE
)

target_link_libraries(${target_name}
    StackBloxPiece
)

include(${CMAKE_SOURCE_DIR}/testing.cmake)
