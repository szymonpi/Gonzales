#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>
#include <memory>
#include <stack>
#include <vector>
#include "../qa/QA.h"
#include "../qa/QAsSelection/QAsToLearnProvider.h"
#include "../qa/QAView.h"

class Teacher
{
public:
    typedef QA QAPair;
    typedef QQueue<std::shared_ptr<QA> > QAQueue;

    Teacher(std::shared_ptr<IQAsToLearnProvider> qAsProvider);

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

    std::shared_ptr<QAView> lastAskedQuestion;
    QQueue<std::shared_ptr<QAView> > m_qAViewsToLearn;
};

