#ifndef PRINTTO_H
#define PRINTTO_H

inline void PrintTo(const QString &str, std::ostream *os)
{
    *os << str.toStdString();
}

#endif // PRINTTO_H
