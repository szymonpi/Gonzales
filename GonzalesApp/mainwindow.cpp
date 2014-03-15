#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qa/qasaver.h>
#include <qa/qaloader.h>
#include <stdexcept>
#include "user/logindialog.h"
#include "qa/qarepository.h"
#include "user/UserInfo.h"
#include "common/common.h"
#include "UIAdapters.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    qARepository(std::make_shared<QARepository>()),
    stateIdle(),
    stateLearn(),
    stateQuestionQiven(&stateLearn),
    stateShowAnswer(&stateLearn),
    stateAnswerVerified(&stateLearn)
{
    ui->setupUi(this);
    m_questionPresenter = std::make_shared<TextPresenter>(*ui->textEditQuestion);
    m_answerPresenter = std::make_shared<TextPresenter>(*ui->textEditAnswer);
    teacher = std::make_shared<TeacherAdapter>(m_questionPresenter, m_answerPresenter);

    LoginDialog loginDialog;
    loginDialog.setModal(true);
    loginDialog.exec();
    if(!loginDialog.result() != QDialog::Accepted)
        exit(0);
    m_userInfo = loginDialog.getUserInfo();
    setWindowTitle(m_userInfo.login);
    setupStateMachine();
}

void MainWindow::setupStateMachine()
{
    stateLearn.setInitialState(&stateQuestionQiven);
    stateIdle.addTransition(this, SIGNAL(startLearn()), &stateLearn);

    stateLearn.addTransition(this, SIGNAL(emptyQAContainer()), &stateIdle);
    stateQuestionQiven.addTransition(this, SIGNAL(showAnswer()), &stateShowAnswer);
    stateShowAnswer.addTransition(this, SIGNAL(questionGiven()), &stateQuestionQiven);

    stateIdle.assignProperty(ui->pushButtonDontKnowIt, "enabled", false);
    stateIdle.assignProperty(ui->pushButtonKnowIt, "enabled", false);
    stateIdle.assignProperty(ui->pushButtonShowAnswer, "enabled", false);

    stateQuestionQiven.assignProperty(ui->pushButtonDontKnowIt, "enabled", false);
    stateQuestionQiven.assignProperty(ui->pushButtonKnowIt, "enabled", false);
    stateQuestionQiven.assignProperty(ui->pushButtonShowAnswer, "enabled", true);

    stateShowAnswer.assignProperty(ui->pushButtonDontKnowIt, "enabled", true);
    stateShowAnswer.assignProperty(ui->pushButtonKnowIt, "enabled", true);
    stateShowAnswer.assignProperty(ui->pushButtonShowAnswer, "enabled", false);

    stateMachine.addState(&stateIdle);
    stateMachine.addState(&stateLearn);

    stateMachine.setInitialState(&stateIdle);
    stateMachine.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonKnowIt_clicked()
{
    teacher->markAsKnown();
    emit questionGiven();

    try
    {
        teacher->showNextQuestion();
    }
    catch(std::logic_error)
    {
        emit emptyQAContainer();
    }
}

void MainWindow::on_pushButtonDontKnowIt_clicked()
{
    teacher->markAsUnknown();
    emit questionGiven();

    try
    {
        teacher->showNextQuestion();
    }
    catch(std::logic_error)
    {
        emit emptyQAContainer();
    }
}

void MainWindow::on_pushButtonShowAnswer_clicked()
{
    teacher->showCorrectAnswer();
    emit showAnswer();
}

QString MainWindow::getFilePathToQas()
{
    QDir homeDirectory = QDir::homePath();
    if(!homeDirectory.cd(g_Company))
    {
        homeDirectory.mkdir(g_Company);
        homeDirectory.cd(g_Company);
    }
    if(!homeDirectory.cd(g_Company))
    {
        homeDirectory.mkdir(g_Project);
        homeDirectory.cd(g_Project);
    }
    QString path = homeDirectory.path()+"/"+m_userInfo.login+".qas";
    return path;
}

void MainWindow::showFileErrorMessageBox(const FileException &e)
{
    QMessageBox saveMessage(this);
    saveMessage.setWindowTitle("file");
    saveMessage.setText(e.what());
    saveMessage.exec();
}


void MainWindow::on_actionLoad_triggered()
{
    QALoader loader;
    try
    {
        QQueue<QA> qas = loader.load(getFilePathToQas());
        std::list<QA> qasList;
        std::copy(qas.begin(), qas.end(), std::back_inserter(qasList));
        qARepository->setQuestions(qasList);
        teacher->setQuestions(qas);
    }
    catch(FileException &e)
    {
        showFileErrorMessageBox(e);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QASaver saver;
    try
    {
        saver.save(qARepository->getQAs(), getFilePathToQas());
    }
    catch(FileException &e)
    {
        showFileErrorMessageBox(e);
    }
}

void MainWindow::on_actionStart_triggered()
{
    if(teacher->questionsToLearnNum()==0)
        return;

    emit startLearn();
}

void MainWindow::on_actionImport_QA_triggered()
{
    QFileDialog dialog(this);
    QString filePath = dialog.getOpenFileName(this);

    if(filePath.isEmpty())
        return;

    QAFromTextFileImporter importer;
    try{
        std::list<QA> importedQAs = importer.import(filePath);
        QQueue<QA> qAsQueue;
        std::copy(importedQAs.begin(), importedQAs.end(), std::back_inserter(qAsQueue));
        qARepository->setQuestions(importedQAs);
        teacher->setQuestions(qAsQueue);
        QMessageBox importMessage(this);
        importMessage.setWindowTitle("import");
        QString numberOfImportedItems;
        importMessage.setText(numberOfImportedItems.setNum(importedQAs.size())+"question and answer item has been imported.");
        importMessage.exec();
    }
    catch(FileException &e)
    {
        showFileErrorMessageBox(e);
    }
}
