#include "dialogqaimporterselector.h"
#include "ui_dialogqaimporterselector.h"
#include <QInputDialog>

DialogQAImporterSelector::DialogQAImporterSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogQAImporterSelector)
{
    ui->setupUi(this);
}

bool DialogQAImporterSelector::select(QMap<QString, QStringList> groupsMap, QStringList importedQAs)
{
    ui->listWidgetQuestions->insertItems(0, importedQAs);
    ui->comboBoxSubjects->insertItems(0,groupsMap.keys());
    ui->comboBoxGroups->insertItems(0,groupsMap[ui->comboBoxSubjects->currentText()]);
    exec();
    if(result()!=QDialog::Accepted)
        return false;
    else
        return true;
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
    return ui->comboBoxSubjects->currentText();
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
        ui->comboBoxSubjects->addItem(text);
}

void DialogQAImporterSelector::on_toolButtonCreateGroup_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(0, tr("Creaete new groups"),
                                         tr("Group:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok)
        ui->comboBoxGroups->addItem(text);
}
