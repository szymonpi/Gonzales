#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <memory>
#include <stack>
#include <vector>
#include "../qa/qacontainer.h"
#include "../IUIAdapters.h"
#include "../qa/iqarepository.h"

class Teacher
{
public:
    typedef QA QAPair;
    typedef std::deque< QAPair > QAQueue;

    Teacher(std::shared_ptr<ITextPresenter> questionPresenter,
            std::shared_ptr<ITextPresenter> answerPresenter,
            std::shared_ptr<QasProvider> qAsProvider);
    void setQuestions(const std::vector<QA> &questions);
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

    QAQueue qAToLearn;
    QAQueue allQA;
    QAContainer lastAskedQuestion;
    std::shared_ptr<ITextPresenter> m_questionPresenter;
    std::shared_ptr<ITextPresenter> m_answerPresenter;
    std::shared_ptr<QasProvider> m_qAsProvider;
};

#endif // TEACHER_H
