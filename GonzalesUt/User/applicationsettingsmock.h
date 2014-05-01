#ifndef APPLICATIONSETTINGSMOCK_H
#define APPLICATIONSETTINGSMOCK_H

#include "../gmock.h"
#include "../../GonzalesApp/common/qtproxies/applicationsettings.h"

class ApplicationSettingsMock: public IApplicationSettings
{
public:
    MOCK_METHOD2(setValue, void(const QString&, const QVariant&));
    MOCK_CONST_METHOD1(contains, bool(const QString &));
    MOCK_METHOD1(remove, void(const QString &));
    MOCK_CONST_METHOD2(value, QVariant(const QString &, const QVariant &));
    MOCK_METHOD1(beginGroup, void(const QString &str));
    MOCK_METHOD0(group, QString());
    MOCK_CONST_METHOD0(childKeys, QStringList());
    MOCK_CONST_METHOD0(allKeys, QStringList());
    MOCK_CONST_METHOD0(childGroups, QStringList());
};

#endif // APPLICATIONSETTINGSMOCK_H
