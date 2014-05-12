#ifndef QASAPPENDER_H
#define QASAPPENDER_H
#include "../Common/SimpleTree/Node.h"
#include "qacontainer.h"

class QAsAppender
{
public:
    virtual void append(std::vector<std::shared_ptr<QA> > importedQAs) = 0;
    virtual ~QAsAppender(){}
};

#endif // QASAPPENDER_H
