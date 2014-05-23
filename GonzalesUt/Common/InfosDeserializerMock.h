#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/common/SimpleTree/IInfosSerializer.h"

class InfosSerializerMock : public SimpleTree::Utils::IInfosSerializer
{
public:
    MOCK_METHOD2(deserialize, void(IDataDeserializer &, QMap<quint8, QVariant>&));
    MOCK_METHOD2(serialize, void(IDataSerializer &, const QMap<quint8, QVariant>&));

};
