#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <queue>
#include <stdexcept>
#include <memory>
#include <stack>
#include <vector>
#include "../qa/qacontainer.h"
#include "../IUIAdapters.h"
#include "../qa/IQARepository.h"

class Teacher
{
public:
    typedef QA QAPair;
    typedef std::deque<std::shared_ptr<QA> > QAQueue;

    Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
            std::shared_ptr<IAnswerPresenter> answerPresenter,
            std::shared_ptr<IQARepository> qAsProvider);
    void markAsUnknown();
    void markAsKnown();
    void showCorrectAnswer() const;
    void showNextQuestion();
    int questionsToLearnNum() const;

private:

    bool isCurrentAnswerCorrect(const Answer &answer);
    void checkIsAskedQuestionEmpty();
    void removeCurrentAskedQA();
    void addWrongAnsweredQAToQueue();
    void checkIsQaQueueEmpty();
    void moveCurrentQuestionToAsked();
    void fillQAsToLearn(std::vector<std::shared_ptr<QA> > &qasToLearn, const SimpleTree::Node<QA> &node) const;

    QAQueue qAToLearn;
    QAQueue allQA;
    std::shared_ptr<QA> lastAskedQuestion;
    std::shared_ptr<IQuestionPresenter> m_questionPresenter;
    std::shared_ptr<IAnswerPresenter> m_answerPresenter;
    std::shared_ptr<IQARepository> m_qAsRepository;
};

#endif // TEACHER_H
