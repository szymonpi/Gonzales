#include "DialogQAImporterSelector.h"
#include "ui_dialogqaimporterselector.h"
#include <QInputDialog>

DialogQAImporterSelector::DialogQAImporterSelector(QMap<QString, QStringList> groupsMap, QStringList importedQAs, QWidget *parent) :
    QDialog(parent),
    m_groupsMap(groupsMap),
    m_importedQAs(importedQAs),
    ui(new Ui::DialogQAImporterSelector)
{
    ui->setupUi(this);
}

bool DialogQAImporterSelector::select()
{
    ui->listWidgetQuestions->addItems(m_importedQAs);
    ui->comboBoxSubjects->addItems(m_groupsMap.keys());
    ui->comboBoxGroups->clear();
    ui->comboBoxGroups->addItems(m_groupsMap[ui->comboBoxSubjects->currentText()]);
    exec();
    return ui->comboBoxSubjects->currentText().size()>0
           && ui->comboBoxGroups->currentText().size()>0;
}

DialogQAImporterSelector::~DialogQAImporterSelector()
{
    delete ui;
}

QString DialogQAImporterSelector::getSubject() const
{
    return ui->comboBoxSubjects->currentText();
}

QString DialogQAImporterSelector::getGroup() const
{
    return ui->comboBoxGroups->currentText();
}

void DialogQAImporterSelector::on_buttonBox_accepted()
{
    close();
}

void DialogQAImporterSelector::on_toolButtonCreateSubject_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(0, tr("Creaete new subject"),
                                         tr("Subject:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        if(!m_groupsMap.contains(text))
        {
            ui->comboBoxSubjects->addItem(text);
            ui->comboBoxGroups->clear();
        }
        ui->comboBoxSubjects->setCurrentText(text);
    }
}

void DialogQAImporterSelector::on_toolButtonCreateGroup_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(0, tr("Creaete new groups"),
                                         tr("Group:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
    {
        if(!m_groupsMap[ui->comboBoxSubjects->currentText()].contains(text))
        {
            ui->comboBoxGroups->addItem(text);
            m_groupsMap[ui->comboBoxSubjects->currentText()].append(text);
        }
        ui->comboBoxGroups->setCurrentText(text);
    }
}

void DialogQAImporterSelector::on_comboBoxSubjects_currentIndexChanged(const QString &arg1)
{
    ui->comboBoxGroups->clear();
    ui->comboBoxGroups->addItems(m_groupsMap[arg1]);
}
