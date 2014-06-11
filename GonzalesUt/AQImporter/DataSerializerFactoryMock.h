#ifndef DataSerializerFACTORYMOCK_H
#define DataSerializerFACTORYMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/common/qtproxies/DataSerializerFactory.h"

class DataSerializerFactoryMock : public IDataSerializerFactory
{
public:
    MOCK_CONST_METHOD1(create, std::shared_ptr<IDataSerializer>(QIODevice *));
};


#endif // DataSerializerMOCK_H
