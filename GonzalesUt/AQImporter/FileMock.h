#ifndef FILEREADER_H
#define FILEREADER_H

#include "../gmock.h"
#include "../../GonzalesApp/common/qtproxies/IFile.h"
#include "../../GonzalesApp/common/qtproxies/filefactory.h"

class FileFactoryMock : public IFileFactory
{
public:
    MOCK_CONST_METHOD1(create, std::shared_ptr<IFile>(const QString &));
};


class FileMock: public IFile
{
public:
    MOCK_METHOD1(open, bool(QFile::OpenModeFlag));
    MOCK_METHOD0(readLine, QString());
    MOCK_METHOD1(setFileName, void(const QString& fileName));
    MOCK_METHOD0(getIODevice, QIODevice *());
    MOCK_METHOD0(isWritable, bool());
    MOCK_METHOD0(isReadable, bool());
    MOCK_METHOD0(isOpen, bool());

};

#endif // FILEREADER_H
