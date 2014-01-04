#ifndef FILESERIALIZEMOCK_H
#define FILESERIALIZEMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/file/fileserializer.h"

class FileSerializerMock : public CanSerializeData
{
public:
    MOCK_METHOD1(serialize, void(bool i));
    MOCK_METHOD1(serialize, void(qint8 i));
    MOCK_METHOD1(serialize, void(quint8 i));
    MOCK_METHOD1(serialize, void(quint16 i));
    MOCK_METHOD1(serialize, void(qint16 i));
    MOCK_METHOD1(serialize, void(qint32 i));
    MOCK_METHOD1(serialize, void(quint32 i));
    MOCK_METHOD1(serialize, void(qint64 i));
    MOCK_METHOD1(serialize, void(quint64 i));
    MOCK_METHOD1(serialize, void(float i));
    MOCK_METHOD1(serialize, void(double i));
    MOCK_METHOD1(serialize, void(const char *i));
    MOCK_METHOD0(status, QDataStream::Status());

};

#endif // FILESERIALIZEMOCK_H
