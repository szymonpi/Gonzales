#ifndef QASIMPORTERMOCK_H
#define QASIMPORTERMOCK_H
#include "../../GonzalesApp/qa/qaio/QAImporter.h"
#include "../gmock.h"

class QAsImporterMock: public QAsImporter
{
public:
    MOCK_METHOD1(import, std::vector<std::shared_ptr<QA> >(const QString &));
};
#endif // QASIMPORTERMOCK_H
