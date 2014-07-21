#pragma once
#include <memory>

class QAView;
class QA;


class QAToViewConverter
{
public:
    virtual std::shared_ptr<QAView> convert(const std::shared_ptr<QA> &qaData) const = 0;
    virtual ~QAToViewConverter(){}
};
