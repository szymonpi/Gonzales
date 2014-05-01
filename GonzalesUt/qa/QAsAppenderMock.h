#ifndef QASAPPENDERMOCK_H
#define QASAPPENDERMOCK_H

#include "../../GonzalesApp/qa/QAsAppender.h"
#include "../gmock.h"

class QAsAppenderMock: public QAsAppender
{
public:
    MOCK_METHOD1(append, void(std::vector<std::shared_ptr<QA> > importedQAs));
};

#endif // QASAPPENDERMOCK_H
