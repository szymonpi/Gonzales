#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsToLearnProvider.h"
#include "../../GonzalesApp/common/SimpleTree/Node.h"
#include "QAsToLearnCheckedByUserProviderMock.h"
#include "../../GonzalesApp/common/Common.h"

using namespace testing;

class QAsToLearnProviderTestSuite: public testing::Test
{
protected:
    QAsToLearnProviderTestSuite():
        m_qasProvider(std::make_shared<QAsToLearnCheckedByUserProviderMock>()),
        m_qasToLearnProvider(m_qasProvider)
    {

    }
    std::shared_ptr<QAsToLearnCheckedByUserProviderMock> m_qasProvider;
    QAsToLearnProvider m_qasToLearnProvider;
    std::shared_ptr<QA> m_qa = std::make_shared<QA>(Question("question"), Answer("answer"));
};




