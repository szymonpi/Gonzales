#ifndef DIALOGQAIMPORTERSELECTOR_H
#define DIALOGQAIMPORTERSELECTOR_H

#include <QDialog>
#include <QMap>
#include "QAsDestinationSelector.h"

namespace Ui {
class DialogQAImporterSelector;
}

class DialogQAImporterSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DialogQAImporterSelector(QWidget *parent = 0);
    ~DialogQAImporterSelector();
    bool select(QMap<QString, QStringList> groupsMap, QStringList importedQAs);
    QString getSubject() const;
    QString getGroup() const;

private slots:
    void on_buttonBox_accepted();

    void on_toolButtonCreateSubject_clicked();

    void on_toolButtonCreateGroup_clicked();

private:
    Ui::DialogQAImporterSelector *ui;
};

class QAsImporterSelector: public QAsDestinationSelector
{
public:
    bool select(QMap<QString, QStringList> groupsMap, QStringList importedQAs)
    {
        return m_selector.select(groupsMap, importedQAs);
    }

    QString getSubject() const
    {
        return m_selector.getSubject();
    }
    QString getGroup() const
    {
        return m_selector.getGroup();
    }
private:
    DialogQAImporterSelector m_selector;
};

#endif // DIALOGQAIMPORTERSELECTOR_H
