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
    std::shared_ptr<QAsSelectorMock> m_qasSelectorMock =
            std::make_shared<QAsSelectorMock>();
    std::shared_ptr<QAsToLearnCheckedByUserProviderMock> m_qasCheckedByUserProvider =
            std::make_shared<QAsToLearnCheckedByUserProviderMock>();
    std::shared_ptr<QA> m_qa = std::make_shared<QA>("question", "answer");
    std::shared_ptr<StrictMock<QAToViewConverterMock>> m_qaToViweConverter =
            std::make_shared<StrictMock<QAToViewConverterMock>>();
    QAsToLearnProvider m_qasToLearnProvider{m_qasCheckedByUserProvider,
                                            m_qasSelectorMock,
                                            m_qaToViweConverter};
};




