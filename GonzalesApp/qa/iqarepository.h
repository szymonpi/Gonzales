#pragma once

#include <QString>
#include "../Common/SimpleTree/Node.h"
#include "QA.h"
#include "QAsSelection/QAsProvider.h"
#include "../uiobservers/IQuestionCollectionPresenter.h"

class IQARepository: public QAsProvider
{
public:
    virtual void load() = 0;
    virtual void onQAsImport() = 0;
    virtual void onQAsUpdate() = 0;
    virtual void registerQuestionCollectionPresenter(std::shared_ptr<IQuestionCollectionPresenter> presenter) = 0;
};
