#pragma once

#include <exception>
#include <sstream>

class Exception : public std::exception {
public:
    Exception(std::string error)
        : m_error(error)
    {
    }
    ~Exception() throw() { }
    virtual const char* what() const throw()
    {
        return m_error.c_str();
    }

private:
    std::string m_error;
};