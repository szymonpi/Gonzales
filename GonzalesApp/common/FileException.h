#pragma once

#include <stdexcept>

class FileException : public std::runtime_error
{
public:
    FileException(std::string what = ""):
        std::runtime_error(what)
    {}

};
