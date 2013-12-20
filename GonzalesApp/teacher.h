#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <memory>
#include <stack>
#include "qacontainer.h"

class Teacher
{
public:
    typedef QA QAPair;
    typedef std::deque< QAPair > QAQueue;

    Teacher();
    Teacher(const QAQueue &questions);
    void setQuestions(const QAQueue &questions);

    bool checkAnswer(const Answer &answer);
    Answer getCorrectAnswer(const Question &question) const;
    int questionsToLearnNum();

    Question getNextQuestion();

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
};

#endif // TEACHER_H