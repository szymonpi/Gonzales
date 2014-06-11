/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart;
    QAction *actionImport_QA;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *MainTab;
    QWidget *learning;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxQuestions;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEditQuestion;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEditAnswer;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonKnowIt;
    QPushButton *pushButtonDontKnowIt;
    QPushButton *pushButtonShowAnswer;
    QWidget *questions;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBoxQuestionsInGroup;
    QVBoxLayout *verticalLayout_10;
    QTreeWidget *treeWidgetQuestions;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(646, 535);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/icons/learn.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon);
        actionImport_QA = new QAction(MainWindow);
        actionImport_QA->setObjectName(QStringLiteral("actionImport_QA"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/resources/icons/import.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport_QA->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        MainTab = new QTabWidget(centralWidget);
        MainTab->setObjectName(QStringLiteral("MainTab"));
        MainTab->setMinimumSize(QSize(0, 0));
        MainTab->setMaximumSize(QSize(852, 16777215));
        MainTab->setTabPosition(QTabWidget::North);
        MainTab->setTabShape(QTabWidget::Rounded);
        MainTab->setIconSize(QSize(32, 32));
        MainTab->setDocumentMode(false);
        MainTab->setTabsClosable(false);
        learning = new QWidget();
        learning->setObjectName(QStringLiteral("learning"));
        verticalLayout_5 = new QVBoxLayout(learning);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBoxQuestions = new QGroupBox(learning);
        groupBoxQuestions->setObjectName(QStringLiteral("groupBoxQuestions"));
        groupBoxQuestions->setAlignment(Qt::AlignCenter);
        groupBoxQuestions->setCheckable(false);
        verticalLayout = new QVBoxLayout(groupBoxQuestions);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEditQuestion = new QTextEdit(groupBoxQuestions);
        textEditQuestion->setObjectName(QStringLiteral("textEditQuestion"));
        QFont font;
        font.setPointSize(16);
        textEditQuestion->setFont(font);
        textEditQuestion->setAutoFillBackground(true);
        textEditQuestion->setReadOnly(true);

        verticalLayout->addWidget(textEditQuestion);


        verticalLayout_3->addWidget(groupBoxQuestions);

        groupBox = new QGroupBox(learning);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textEditAnswer = new QTextEdit(groupBox);
        textEditAnswer->setObjectName(QStringLiteral("textEditAnswer"));
        QFont font1;
        font1.setPointSize(14);
        textEditAnswer->setFont(font1);
        textEditAnswer->setReadOnly(true);

        verticalLayout_2->addWidget(textEditAnswer);


        verticalLayout_3->addWidget(groupBox);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonKnowIt = new QPushButton(learning);
        pushButtonKnowIt->setObjectName(QStringLiteral("pushButtonKnowIt"));
        pushButtonKnowIt->setEnabled(false);
        pushButtonKnowIt->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(pushButtonKnowIt);

        pushButtonDontKnowIt = new QPushButton(learning);
        pushButtonDontKnowIt->setObjectName(QStringLiteral("pushButtonDontKnowIt"));
        pushButtonDontKnowIt->setEnabled(false);
        pushButtonDontKnowIt->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(pushButtonDontKnowIt);


        verticalLayout_4->addLayout(horizontalLayout);

        pushButtonShowAnswer = new QPushButton(learning);
        pushButtonShowAnswer->setObjectName(QStringLiteral("pushButtonShowAnswer"));
        pushButtonShowAnswer->setMinimumSize(QSize(0, 32));

        verticalLayout_4->addWidget(pushButtonShowAnswer);


        verticalLayout_5->addLayout(verticalLayout_4);

        QIcon icon2;
        icon2.addFile(QStringLiteral(":/resources/icons/learning.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainTab->addTab(learning, icon2, QString());
        questions = new QWidget();
        questions->setObjectName(QStringLiteral("questions"));
        verticalLayout_7 = new QVBoxLayout(questions);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        groupBoxQuestionsInGroup = new QGroupBox(questions);
        groupBoxQuestionsInGroup->setObjectName(QStringLiteral("groupBoxQuestionsInGroup"));
        verticalLayout_10 = new QVBoxLayout(groupBoxQuestionsInGroup);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        treeWidgetQuestions = new QTreeWidget(groupBoxQuestionsInGroup);
        treeWidgetQuestions->setObjectName(QStringLiteral("treeWidgetQuestions"));
        treeWidgetQuestions->setAutoFillBackground(false);
        treeWidgetQuestions->setFrameShape(QFrame::StyledPanel);
        treeWidgetQuestions->setMidLineWidth(0);
        treeWidgetQuestions->setAutoScrollMargin(2);
        treeWidgetQuestions->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeWidgetQuestions->setTabKeyNavigation(false);
        treeWidgetQuestions->setProperty("showDropIndicator", QVariant(false));
        treeWidgetQuestions->setDragEnabled(false);
        treeWidgetQuestions->setDragDropMode(QAbstractItemView::NoDragDrop);
        treeWidgetQuestions->setAlternatingRowColors(true);
        treeWidgetQuestions->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeWidgetQuestions->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeWidgetQuestions->setIconSize(QSize(20, 20));
        treeWidgetQuestions->setTextElideMode(Qt::ElideRight);
        treeWidgetQuestions->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        treeWidgetQuestions->setUniformRowHeights(false);
        treeWidgetQuestions->setSortingEnabled(true);
        treeWidgetQuestions->setAnimated(true);
        treeWidgetQuestions->setWordWrap(true);
        treeWidgetQuestions->header()->setCascadingSectionResizes(true);
        treeWidgetQuestions->header()->setHighlightSections(true);

        verticalLayout_10->addWidget(treeWidgetQuestions);


        verticalLayout_7->addWidget(groupBoxQuestionsInGroup);

        QIcon icon3;
        icon3.addFile(QStringLiteral(":/resources/icons/book.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainTab->addTab(questions, icon3, QString());

        verticalLayout_6->addWidget(MainTab, 0, Qt::AlignTop);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 646, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(0, 0));
        mainToolBar->setIconSize(QSize(32, 32));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addSeparator();
        mainToolBar->addAction(actionStart);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionImport_QA);

        retranslateUi(MainWindow);

        MainTab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionStart->setText(QApplication::translate("MainWindow", "start learn", 0));
#ifndef QT_NO_TOOLTIP
        actionStart->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Start learning!</span></p><p>If you checked questions that you want to learn lets start!</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionImport_QA->setText(QApplication::translate("MainWindow", "import QA", 0));
#ifndef QT_NO_TOOLTIP
        actionImport_QA->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">Import your Questions and answers!</span></p><p align=\"justify\">File line should have format:</p><p align=\"justify\">Q: your question A: your answer</p><p align=\"justify\">or</p><p align=\"justify\">your question - your answer</p><p align=\"justify\">Import and Enjoy!</p><p align=\"justify\"><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBoxQuestions->setTitle(QApplication::translate("MainWindow", "Question", 0));
        textEditQuestion->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:16pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Answer", 0));
        pushButtonKnowIt->setText(QApplication::translate("MainWindow", "I know it!", 0));
        pushButtonDontKnowIt->setText(QApplication::translate("MainWindow", "I don't know", 0));
        pushButtonShowAnswer->setText(QApplication::translate("MainWindow", "Show answer", 0));
        MainTab->setTabText(MainTab->indexOf(learning), QApplication::translate("MainWindow", "Learning", 0));
        groupBoxQuestionsInGroup->setTitle(QApplication::translate("MainWindow", "Questions & Answers", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidgetQuestions->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "check to learn", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "answer", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "question", 0));
        MainTab->setTabText(MainTab->indexOf(questions), QApplication::translate("MainWindow", "Questions", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
