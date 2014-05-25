#pragma once

#include <QString>
#include "../Common/SimpleTree/Node.h"
#include "QA.h"
#include "QAsProvider.h"

class IQARepository: public QAsProvider
{
public:
    virtual void load() = 0;
    virtual void onQAsImport() = 0;
    virtual void onQAsUpdate() = 0;
};
