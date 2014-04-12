#include "teacher.h"
#include <algorithm>

Teacher::Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
                 std::shared_ptr<IAnswerPresenter> answerPresenter,
                 std::shared_ptr<IQARepository> repository):
    qAToLearn(),
    lastAskedQuestion(),
    m_questionPresenter(questionPresenter),
    m_answerPresenter(answerPresenter),
    m_qAsRepository(repository)
{
    std::vector<std::shared_ptr<QA> > l_qas;

    foreach(const Node<QA> &node, m_qAsRepository->getQAs())
    {
        fillQAsToLearn(l_qas, node);
    }

    std::copy(l_qas.begin(), l_qas.end(), std::back_inserter(allQA));
    qAToLearn = allQA;
}

void Teacher::fillQAsToLearn(std::vector<std::shared_ptr<QA> > &qasToLearn,
                    const Node<QA> &node) const
{
    if(node.getNodeValue().get())
        if(node.getNodeValue()->toLearn() == true)
            qasToLearn.push_back(node.getNodeValue());
    foreach(const Node<QA> node, node.getNodes())
    {
        fillQAsToLearn(qasToLearn, node);
    }
}

void Teacher::markAsUnknown()
{
    addWrongAnsweredQAToQueue();
}

void Teacher::markAsKnown()
{
    removeCurrentAskedQA();
}

void Teacher::showCorrectAnswer() const
{
    m_answerPresenter->presentAnswer(lastAskedQuestion->answer);
}

int Teacher::questionsToLearnNum() const
{
    return qAToLearn.size();
}

void Teacher::showNextQuestion()
{
    checkIsQaQueueEmpty();
    moveCurrentQuestionToAsked();
    m_answerPresenter->clear();
    m_questionPresenter->presentQuestion(lastAskedQuestion->question);
}

void Teacher::removeCurrentAskedQA()
{
    lastAskedQuestion.reset();
}

void Teacher::addWrongAnsweredQAToQueue()
{
    qAToLearn.push_back(lastAskedQuestion);
    lastAskedQuestion.reset();
}

void Teacher::checkIsQaQueueEmpty()
{
    if(qAToLearn.empty())
        throw std::logic_error("empty questions container");
}

void Teacher::moveCurrentQuestionToAsked()
{
    lastAskedQuestion = qAToLearn.front();
    qAToLearn.pop_front();
}
