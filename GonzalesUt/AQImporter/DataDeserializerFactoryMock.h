#pragma once

#include "../gmock.h"
#include "../../GonzalesApp/common/qtproxies/DataDeserializerfactory.h"

class DataDeserializerFactoryMock : public IDataDeserializerFactory
{
public:
    MOCK_CONST_METHOD1(create, std::shared_ptr<IDataDeserializer>(QIODevice *));
};

