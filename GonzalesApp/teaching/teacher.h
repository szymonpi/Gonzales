#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>
#include <memory>
#include <stack>
#include <vector>
#include "../qa/QA.h"
#include "../uiobservers/IQuestionPresenter.h"
#include "../uiobservers/IAnswerPresenter.h"
#include "../qa/QAsToLearnProvider.h"

class Teacher
{
public:
    typedef QA QAPair;
    typedef QQueue<std::shared_ptr<QA> > QAQueue;

    Teacher(std::shared_ptr<IQuestionPresenter> questionPresenter,
            std::shared_ptr<IAnswerPresenter> answerPresenter,
            std::shared_ptr<IQAsToLearnProvider> qAsProvider);

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

    std::shared_ptr<QA> lastAskedQuestion;
    std::shared_ptr<IQuestionPresenter> m_questionPresenter;
    std::shared_ptr<IAnswerPresenter> m_answerPresenter;
    QAQueue m_qAsToLearn;
};

