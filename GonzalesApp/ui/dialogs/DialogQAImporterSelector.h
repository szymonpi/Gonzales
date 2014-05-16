#pragma once

#include <QDialog>
#include <QMap>
#include "../../uiobservers/QAsDestinationSelector.h"

namespace Ui {
class DialogQAImporterSelector;
}

class DialogQAImporterSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DialogQAImporterSelector(QMap<QString, QStringList> groupsMap, QStringList importedQAs, QWidget *parent = 0);
    ~DialogQAImporterSelector();
    bool select();
    QString getSubject() const;
    QString getGroup() const;

private slots:
    void on_buttonBox_accepted();

    void on_toolButtonCreateSubject_clicked();

    void on_toolButtonCreateGroup_clicked();

    void on_comboBoxSubjects_currentIndexChanged(const QString &arg1);

private:
    QMap<QString, QStringList> m_groupsMap;
    QStringList m_importedQAs;
    Ui::DialogQAImporterSelector *ui;
};

class QAsImporterSelector: public QAsDestinationSelector
{
public:
    bool select(QMap<QString, QStringList> groupsMap, QStringList importedQAs)
    {
        DialogQAImporterSelector m_selector(groupsMap, importedQAs);
        if(m_selector.select())
        {
            m_subject = m_selector.getSubject();
            m_group = m_selector.getGroup();
            return true;
        }
        return false;
    }

    QString getSubject() const
    {
        return m_subject;
    }
    QString getGroup() const
    {
        return m_group;
    }
private:
    QString m_subject;
    QString m_group;
};
