#ifndef IUIADAPTERS_H
#define IUIADAPTERS_H
#include "Common/simpletree.h"

class Answer;
class Question;

class IQuestionCollectionPresenter
{
public:
    virtual void presentQuestions(const std::vector<Node<QA>> &p_questions) = 0;
    virtual ~IQuestionCollectionPresenter(){}
};

class IQuestionPresenter
{
public:
    virtual void presentQuestion(const Question &question) = 0;
    virtual void clear() = 0;
    virtual ~IQuestionPresenter(){}
};

class IAnswerPresenter
{
public:
    virtual void presentAnswer(const Answer &question) = 0;
    virtual void clear() = 0;
    virtual ~IAnswerPresenter(){}
};

#endif // IUIADAPTERS_H
