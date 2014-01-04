#ifndef FILESERIALIZERFACTORYMOCK_H
#define FILESERIALIZERFACTORYMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/file/fileserializerfactory.h"

class FileSerializerFactoryMock : public IFileSerializerFactory
{
public:
    MOCK_CONST_METHOD1(create, std::shared_ptr<CanSerializeData>(QIODevice *));
};


#endif // FILESERIALIZERMOCK_H
