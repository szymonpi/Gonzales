#ifndef IQAREPOSITORY_H
#define IQAREPOSITORY_H
#include <QString>
#include "../Common/simpletree.h"
#include "qacontainer.h"

class IQARepository
{
public:
    virtual void load() = 0;
    virtual void onQAsUpdate() = 0;
    virtual const std::vector<Node<QA> > &getQAs() const = 0;
    virtual std::vector<Node<QA> > &getQAs() = 0;
    virtual ~IQARepository(){}
};

#endif // IQAREPOSITORY_H
