function(target_assets target_name)
    set(assets_path_list ${ARGV})
    list(REMOVE_AT assets_path_list 0)

    set(androidstudio_path ${CMAKE_BINARY_DIR}/AndroidStudio/${target_name})

    foreach(assets_path ${assets_path_list})
        get_filename_component(assets_dir "${assets_path}" NAME)

        get_filename_component(assets_path "${assets_path}"
            REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

        get_target_property(MACOSX_BUNDLE ${target_name} MACOSX_BUNDLE)

        if(APPLE AND MACOSX_BUNDLE)
            target_sources(${target_name} PRIVATE
                ${assets_path}
            )
            set_source_files_properties(${assets_path} PROPERTIES
                MACOSX_PACKAGE_LOCATION Resources
            )
        else()
            if(ANDROID)
                set(assets_dest_path ${androidstudio_path}/app/src/main/assets/${assets_dir})
            else()
                set(assets_dest_path $<TARGET_FILE_DIR:${target_name}>/${assets_dir})
            endif()
            add_custom_command(
                TARGET ${target_name}
                PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${assets_path}
                    ${assets_dest_path}
            )
        endif()

        if(NOT MACOSX_BUNDLE AND NOT ANDROID)
            set(component_name ${target_name}_${PROJECT_VERSION}_${platform})
            install(DIRECTORY ${assets_path} DESTINATION ${target_name}/${assets_install_dir} COMPONENT ${component_name})
        endif()

        # Stage assets so Visual Studio will find them.
        # Not needed if an absolute path is used.
        if(MSVC)
            add_custom_command(
                TARGET ${target_name}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${assets_path}
                    ${CMAKE_CURRENT_BINARY_DIR}/assets
            )
        endif()
    endforeach()
endfunction(target_assets)
