#pragma once

#include <fstream>

class Exception;

class ErrorHandler {
public:
    ErrorHandler(std::string const&);
    ~ErrorHandler();

    void showError(Exception& error);

    std::ofstream operator<<(std::string const&);

private:
    std::string m_logFileName;
};