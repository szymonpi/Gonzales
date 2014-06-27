#pragma once
#include "../QA.h"
#include <memory>
#include <vector>

class IQAsForRepeatSelector
{
public:
    virtual std::vector<std::shared_ptr<QA>> select(std::vector<std::shared_ptr<QA>>& qas) = 0;
    ~IQAsForRepeatSelector(){}
};
