#pragma once

#include <QVector>
#include "../QA.h"
#include <memory>

class IQAsSelector
{
public:
    virtual ~IQAsSelector(){}
    virtual std::vector<std::shared_ptr<QA>> select(std::vector<std::shared_ptr<QA> > &qas) = 0;
};
