#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

class FileException : public std::runtime_error
{
public:
    FileException(std::string what = ""):
        std::runtime_error(what)
    {}

};

#endif // FILEEXCEPTION_H
