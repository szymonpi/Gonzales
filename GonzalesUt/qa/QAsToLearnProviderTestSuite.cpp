#include <memory>
#include "../gtest.h"
#include "../gmock.h"
#include "../../GonzalesApp/qa/QAsSelection/QAsToLearnProvider.h"
#include "../../GonzalesApp/common/SimpleTree/Node.h"
#include "QAsToLearnCheckedByUserProviderMock.h"
#include "../../GonzalesApp/common/Common.h"
#include "QAsSelectorMock.h"
#include "QAToViewConverterMock.h"

using namespace testing;

class QAsToLearnProviderTestSuite: public testing::Test
{
protected:
    QAsToLearnProviderTestSuite():
        m_qasCheckedByUserProvider(std::make_shared<QAsToLearnCheckedByUserProviderMock>()),
        m_qasSelectorMock(std::make_shared<QAsSelectorMock>()),
        m_qasToLearnProvider(m_qasCheckedByUserProvider, m_qasSelectorMock)
    {

    }
    std::shared_ptr<QAsSelectorMock> m_qasSelectorMock;
    std::shared_ptr<QAsToLearnCheckedByUserProviderMock> m_qasCheckedByUserProvider;
    QAsToLearnProvider m_qasToLearnProvider;
    std::shared_ptr<QA> m_qa = std::make_shared<QA>(Question("question"), Answer("answer"));
    std::shared_ptr<StrictMock<QAToViewConverterMock>> m_qaToViweConverter = std::make_shared<StrictMock<QAToViewConverterMock>>();
};




