execute_process(
    COMMAND xcodebuild -workspace @CMAKE_BINARY_DIR@/@PROJECT_NAME@.xcodeproj/project.xcworkspace
        -scheme @target_name@ archive -archivePath @component_name@.xcarchive
        -destination generic/platform=iOS
    COMMAND_ECHO STDOUT
    RESULT_VARIABLE xcode_archive_result
    WORKING_DIRECTORY @CMAKE_CURRENT_BINARY_DIR@
    )
    if(xcode_archive_result)
        message(FATAL_ERROR "Xcode error")
    endif()

file(INSTALL "@CMAKE_CURRENT_BINARY_DIR@/@component_name@.xcarchive" DESTINATION "${CMAKE_INSTALL_PREFIX}/.")
