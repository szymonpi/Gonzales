#ifndef QADESTINATIONSELECTOR_H
#define QADESTINATIONSELECTOR_H
#include <QMap>
#include <QStringList>

class QAsDestinationSelector
{
public:
    virtual bool select(QMap<QString, QStringList> groupsMap, QStringList importedQAs) = 0;
    virtual QString getSubject() const = 0;
    virtual QString getGroup() const = 0;
    virtual ~QAsDestinationSelector(){}
};

#endif // QADESTINATIONSELECTOR_H
