#ifndef IQAREPOSITORY_H
#define IQAREPOSITORY_H
#include <QString>
#include "../Common/SimpleTree/Node.h"
#include "qacontainer.h"

class QAsProvider
{
public:
    virtual const SimpleTree::Node<QA> &getQAs() const = 0;
    virtual SimpleTree::Node<QA> &getQAs() = 0;
    virtual ~QAsProvider(){}
};

class IQARepository: public QAsProvider
{
public:
    virtual void load() = 0;
    virtual void onQAsUpdate() = 0;
};

#endif // IQAREPOSITORY_H
