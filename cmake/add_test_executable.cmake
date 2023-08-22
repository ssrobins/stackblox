function(add_test_executable target_name)
    add_executable_custom(${target_name})

    target_link_libraries(${target_name} 
        gtest::gtest
    )

    if(NOT ANDROID AND NOT IOS)
        add_test(NAME ${target_name} COMMAND ${target_name})
    endif()
endfunction(add_test_executable)
