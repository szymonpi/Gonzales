#ifndef DataSerializerMOCK_H
#define DataSerializerMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/common/qtproxies/IDataSerializer.h"

class DataSerializerMock : public IDataSerializer
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
    MOCK_METHOD1(serialize, void(const std::string &str));
    MOCK_METHOD1(serialize, void(const QString &));
    MOCK_METHOD1(serialize, void(const QDateTime &));
    MOCK_METHOD1(serialize, void(const QDate &));
    MOCK_METHOD0(status, QDataStream::Status());

};

#endif // FILESERIALIZEMOCK_H
