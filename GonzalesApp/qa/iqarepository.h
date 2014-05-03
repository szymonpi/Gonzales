#ifndef IQAREPOSITORY_H
#define IQAREPOSITORY_H
#include <QString>
#include "../Common/SimpleTree/node.h"
#include "qacontainer.h"

class IQARepository
{
public:
    virtual void load() = 0;
    virtual void onQAsUpdate() = 0;
    virtual const std::vector<SimpleTree::Node<QA> > &getQAs() const = 0;
    virtual std::vector<SimpleTree::Node<QA> > &getQAs() = 0;
    virtual ~IQARepository(){}
};

#endif // IQAREPOSITORY_H
