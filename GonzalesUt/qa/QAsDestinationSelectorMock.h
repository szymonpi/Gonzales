#ifndef QASDESTINATIONSELECTORMOCK_H
#define QASDESTINATIONSELECTORMOCK_H

#include "../../GonzalesApp/uiobservers/QAsDestinationSelector.h"
#include "../gmock.h"

class QAsDestinationSelectorMock: public QAsDestinationSelector
{
public:
    MOCK_METHOD2(select, bool(QMap<QString, QStringList> groupsMap, QStringList importedQAs));
    MOCK_CONST_METHOD0(getSubject, QString());
    MOCK_CONST_METHOD0(getGroup, QString());
};

#endif // QASDESTINATIONSELECTORMOCK_H
