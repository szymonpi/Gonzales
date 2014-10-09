#ifndef PRESENTERSMOCK_H
#define PRESENTERSMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/uiobservers/IQAPresenter.h"

class QAPresenterMock: public IQAPresenter
{
public:
    MOCK_METHOD1(presentAnswer, void(const QString &));
    MOCK_METHOD1(presentQuestion, void(const QString &));
};

#endif // PRESENTERSMOCK_H
