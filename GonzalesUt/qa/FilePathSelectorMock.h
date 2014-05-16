#ifndef FILEPATHSELECTORMOCK_H
#define FILEPATHSELECTORMOCK_H
#include "../../GonzalesApp/uiobservers/FilePathSelector.h"
#include "../gmock.h"

class FilePathSelectorMock: public FilePathSelector
{
public:
    MOCK_METHOD0(select, bool());
    MOCK_CONST_METHOD0(getSelected, QString());
};
#endif // FILEPATHSELECTORMOCK_H
