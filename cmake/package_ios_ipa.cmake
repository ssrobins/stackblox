function(xcode_package component)
    if(component)
        set(package_name ${component})
    else()
        get_filename_component(package_name ${CPACK_TEMPORARY_DIRECTORY} NAME)
    endif()

    message("Building ipa for ${package_name}")

    execute_process(
        COMMAND xcodebuild -exportArchive -archivePath ${package_name}.xcarchive -allowProvisioningUpdates
            -exportOptionsPlist export_options.plist -exportPath .
        WORKING_DIRECTORY ${CPACK_TEMPORARY_DIRECTORY}/${component}
        RESULT_VARIABLE xcode_package_result
    )
    if(xcode_package_result)
        message(FATAL_ERROR "Xcode error")
    endif()

    file(GLOB ipa_path_original "${CPACK_TEMPORARY_DIRECTORY}/${component}/*.ipa")
    set(ipa_path_new "${CPACK_TEMPORARY_DIRECTORY}/${component}/${package_name}.ipa")
    file(RENAME ${ipa_path_original} ${ipa_path_new})
    file(COPY ${ipa_path_new} DESTINATION ${CPACK_PACKAGE_DIRECTORY})
endfunction(xcode_package)


if(CPACK_COMPONENTS_ALL)
    foreach(component ${CPACK_COMPONENTS_ALL})
        xcode_package(${component})
    endforeach()
else()
    xcode_package("")
endif()
