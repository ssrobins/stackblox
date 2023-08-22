function(gradle_build component)
    if(component)
        set(package_name ${component})
    else()
        get_filename_component(package_name ${CPACK_TEMPORARY_DIRECTORY} NAME)
    endif()

    message("\n\nBuilding APK for ${package_name}")

    find_program(gradle_path gradle)
    if(gradle_path)
        message(STATUS "Gradle was found at: ${gradle_path}")
        set(gradle_command ${gradle_path})
    else()
        message(STATUS "Gradle was not found, using wrapper instead")
        if(WIN32)
            set(gradle_command gradlew.bat)
        else()
            set(gradle_command ./gradlew)
        endif()
    endif()
    if(WIN32)
        set(gradle_extra_params -Dorg.gradle.daemon.idletimeout=1000)
    endif()

    execute_process(
        COMMAND ${gradle_command} assemble${CPACK_BUILD_CONFIG} ${gradle_extra_params}
        WORKING_DIRECTORY ${CPACK_TEMPORARY_DIRECTORY}/${component}
        RESULT_VARIABLE gradle_result
    )
    if(gradle_result)
        message(FATAL_ERROR "Gradle error")
    endif()

    string(TOLOWER ${CPACK_BUILD_CONFIG} build_config_lower)
    set(apk_path "${CPACK_TEMPORARY_DIRECTORY}/${component}/app/build/outputs/apk/${build_config_lower}/${package_name}_${CPACK_ANDROID_ABI}.apk")
    file(COPY ${apk_path} DESTINATION ${CPACK_PACKAGE_DIRECTORY})
endfunction(gradle_build)


if(CPACK_COMPONENTS_ALL)
    foreach(component ${CPACK_COMPONENTS_ALL})
        gradle_build(${component})
    endforeach()
else()
    gradle_build("")
endif()
