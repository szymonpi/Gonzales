/********************************************************************************
** Form generated from reading UI file 'dialogqaimporterselector.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGQAIMPORTERSELECTOR_H
#define UI_DIALOGQAIMPORTERSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogQAImporterSelector
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidgetQuestions;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxSubjects;
    QToolButton *toolButtonCreateSubject;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBoxGroups;
    QToolButton *toolButtonCreateGroup;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogQAImporterSelector)
    {
        if (DialogQAImporterSelector->objectName().isEmpty())
            DialogQAImporterSelector->setObjectName(QStringLiteral("DialogQAImporterSelector"));
        DialogQAImporterSelector->resize(400, 300);
        verticalLayout_5 = new QVBoxLayout(DialogQAImporterSelector);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(DialogQAImporterSelector);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidgetQuestions = new QListWidget(groupBox);
        listWidgetQuestions->setObjectName(QStringLiteral("listWidgetQuestions"));

        verticalLayout->addWidget(listWidgetQuestions);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DialogQAImporterSelector);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBoxSubjects = new QComboBox(groupBox_2);
        comboBoxSubjects->setObjectName(QStringLiteral("comboBoxSubjects"));

        horizontalLayout->addWidget(comboBoxSubjects);

        toolButtonCreateSubject = new QToolButton(groupBox_2);
        toolButtonCreateSubject->setObjectName(QStringLiteral("toolButtonCreateSubject"));

        horizontalLayout->addWidget(toolButtonCreateSubject);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(DialogQAImporterSelector);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        comboBoxGroups = new QComboBox(groupBox_3);
        comboBoxGroups->setObjectName(QStringLiteral("comboBoxGroups"));

        horizontalLayout_2->addWidget(comboBoxGroups);

        toolButtonCreateGroup = new QToolButton(groupBox_3);
        toolButtonCreateGroup->setObjectName(QStringLiteral("toolButtonCreateGroup"));

        horizontalLayout_2->addWidget(toolButtonCreateGroup);


        verticalLayout_4->addWidget(groupBox_3);

        buttonBox = new QDialogButtonBox(DialogQAImporterSelector);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(DialogQAImporterSelector);

        QMetaObject::connectSlotsByName(DialogQAImporterSelector);
    } // setupUi

    void retranslateUi(QDialog *DialogQAImporterSelector)
    {
        DialogQAImporterSelector->setWindowTitle(QApplication::translate("DialogQAImporterSelector", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DialogQAImporterSelector", "Imported QAs", 0));
        groupBox_2->setTitle(QApplication::translate("DialogQAImporterSelector", "subject", 0));
        toolButtonCreateSubject->setText(QApplication::translate("DialogQAImporterSelector", "New", 0));
        groupBox_3->setTitle(QApplication::translate("DialogQAImporterSelector", "group", 0));
        toolButtonCreateGroup->setText(QApplication::translate("DialogQAImporterSelector", "New", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogQAImporterSelector: public Ui_DialogQAImporterSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGQAIMPORTERSELECTOR_H
