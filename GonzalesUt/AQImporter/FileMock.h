#ifndef FILEREADER_H
#define FILEREADER_H

#include "../gmock.h"
#include "../../GonzalesApp/file.h"


class FileMock: public ReadableWritableFile
{
public:
    MOCK_METHOD1(open, bool(QFile::OpenModeFlag));
    MOCK_METHOD0(readLine, QString());
    MOCK_METHOD1(setFileName, void(const QString& fileName));
    MOCK_METHOD0(getIODevice, QIODevice *());

};

#endif // FILEREADER_H
