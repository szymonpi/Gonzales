#ifndef FILEDESERIALIZERFACTORYMOCK_H
#define FILEDESERIALIZERFACTORYMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/common/qtproxies/filedeserializerfactory.h"

class FileDeserializerFactoryMock : public IFileDeserializerFactory
{
public:
    MOCK_CONST_METHOD1(create, std::shared_ptr<CanDeserializeData>(QIODevice *));
};

#endif // FILEDESERIALIZERFACTORYMOCK_H
