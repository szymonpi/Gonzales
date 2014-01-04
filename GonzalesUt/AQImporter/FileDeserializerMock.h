#ifndef FILEDESERIALIZERMOCK_H
#define FILEDESERIALIZERMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/file/filedeserializer.h"

class FileDeserializerMock : public CanDeserializeData
{
public:
    MOCK_METHOD1(deserialize, void(bool &i));
    MOCK_METHOD1(deserialize, void(qint8 &i));
    MOCK_METHOD1(deserialize, void(quint8 &i));
    MOCK_METHOD1(deserialize, void(quint16 &i));
    MOCK_METHOD1(deserialize, void(qint16 &i));
    MOCK_METHOD1(deserialize, void(qint32 &i));
    MOCK_METHOD1(deserialize, void(quint32 &i));
    MOCK_METHOD1(deserialize, void(qint64 &i));
    MOCK_METHOD1(deserialize, void(quint64 &i));
    MOCK_METHOD1(deserialize, void(float &i));
    MOCK_METHOD1(deserialize, void(double &i));
    MOCK_METHOD1(deserialize, void(char *&i));
    MOCK_METHOD0(status, QDataStream::Status());
    MOCK_METHOD0(atEnd, bool());

};

#endif // FILEDESERIALIZERMOCK_H
