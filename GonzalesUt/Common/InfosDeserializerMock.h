#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/common/SimpleTree/IInfosSerializer.h"

class InfosSerializerMock : public SimpleTree::Utils::IInfosSerializer
{
public:
    MOCK_METHOD2(deserialize, void(IDataDeserializer &, std::map<quint8, QVariant>&));
    MOCK_METHOD2(serialize, void(IDataSerializer &, const std::map<quint8, QVariant>&));

};
