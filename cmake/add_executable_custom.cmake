set(current_file_path ${CMAKE_CURRENT_LIST_DIR})

function(add_executable_custom target_name)
    set(properties ${ARGV})
    list(REMOVE_AT properties 0)

    if(ANDROID)
        add_library(${target_name} SHARED)
    else()
        add_executable(${target_name} ${properties})
    endif()

    if(APPLE)
        set_target_properties(${target_name} PROPERTIES
            MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
            MACOSX_BUNDLE_INFO_PLIST "${current_file_path}/info.plist.in"
            XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${xcode_code_sign_identity}"
            XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${xcode_dev_team}"
            XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${MACOSX_BUNDLE_GUI_IDENTIFIER}"
        )
    endif()

    if(IOS)
        if(${ENABLE_BITCODE})
            set(xcode_bitcode YES)
        else()
            set(xcode_bitcode NO)
        endif()

        set_target_properties(${target_name} PROPERTIES
            XCODE_ATTRIBUTE_ENABLE_BITCODE "${xcode_bitcode}"
            XCODE_ATTRIBUTE_INSTALL_PATH "$(LOCAL_APPS_DIR)"
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2" # 1=iPhone/iPod, 2=iPad
        )
    else(APPLE)
        set_target_properties(${target_name} PROPERTIES
            XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Manual"
        )
    endif()
endfunction(add_executable_custom)
