#ifndef FILEREADER_H
#define FILEREADER_H

#include "../gmock.h"
#include "../../GonzalesApp/file.h"


class FileMock: public ReadableFile
{
public:
    MOCK_METHOD1(open, bool(QFile::OpenModeFlag));
    MOCK_METHOD1(readLine, QByteArray(qint64 maxlen));
    MOCK_METHOD0(readLine, QString());
    MOCK_METHOD0(readAll, QByteArray());
    MOCK_METHOD1(setFileName, void(const QString& fileName));

};

#endif // FILEREADER_H
