#include "ErrorHandler.h"
#include "Exceptions.h"
#include "SDL_messagebox.h"
#include <fstream>
#include <iostream>
#ifdef __ANDROID__
#include <android/log.h>
#endif

ErrorHandler::ErrorHandler(std::string const& logFileName)
    : m_logFileName(logFileName)
{
    // Remove the file so we don't see errors from a previous run of the program
    std::remove(m_logFileName.c_str());
}

ErrorHandler::~ErrorHandler()
{
}

void ErrorHandler::showError(Exception& error)
{
#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_VERBOSE, "Error", "%s", error.what());
#endif

    *this << error.what() << std::endl;
    std::cerr << error.what() << std::endl;

    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        "Error",
        error.what(),
        nullptr);
}

std::ofstream ErrorHandler::operator<<(std::string const& error)
{
    std::ofstream outputFileStream;

    // Open the file now instead of in the constructor so an error log file is only created
    // when there is an error to report.
    // Append to the file, in case there are multiple error messages in the same session.
    outputFileStream.open(m_logFileName.c_str(), std::ofstream::app);

    outputFileStream << error;
    return outputFileStream;
}
