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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    teacher(),
    qARepository(std::make_shared<QARepository>()),
    stateIdle(),
    stateLearn(),
    stateQuestionQiven(&stateLearn),
    stateShowAnswer(&stateLearn),
    stateAnswerVerified(&stateLearn)
{
    ui->setupUi(this);
    LoginDialog loginDialog;
    loginDialog.setModal(true);
    loginDialog.exec();
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

void MainWindow::setNewQuestion(const QString &question)
{
    currentQA.first = question;
    setNewQuestionInUI();
}

void MainWindow::setNewQuestionInUI()
{
    ui->textEditAnswer->clear();
    ui->textEditAnswer->update();

    ui->textEditQuestion->setText(currentQA.first);
    ui->textEditQuestion->update();
}

void MainWindow::updateQuestion()
{
    checkQuestionsToGo();
    setNewQuestion(teacher.getNextQuestion());
}

void MainWindow::checkQuestionsToGo()
{
    if(teacher.questionsToLearnNum()==0)
    {
        emit emptyQAContainer();
    }
}

void MainWindow::on_pushButtonKnowIt_clicked()
{
    teacher.checkAnswer(currentQA.second);
    emit questionGiven();
    updateQuestion();
}

void MainWindow::on_pushButtonDontKnowIt_clicked()
{
    teacher.checkAnswer(currentQA.second + "WRONG WRONG WRONG");
    emit questionGiven();
    updateQuestion();
}

void MainWindow::on_pushButtonShowAnswer_clicked()
{
    currentQA.second = teacher.getCorrectAnswer(currentQA.first);
    ui->textEditAnswer->setText(currentQA.second);
    emit showAnswer();
}

QString MainWindow::getFilePathToLoadFromDialog()
{
    QFileDialog dialog(this);
    QString filePath = dialog.getOpenFileName(this);
    if(filePath.isEmpty())
        throw FileException("filePath is empty");
    return filePath;
}

QString MainWindow::getFilePathToSaveFromDialog()
{
    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName(this);
    if(filePath.isEmpty())
        throw FileException("filePath is empty");
    return filePath;
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
        QQueue<QA> qas = loader.load(getFilePathToLoadFromDialog());
        std::list<QA> qasList;
        std::copy(qas.begin(), qas.end(), std::back_inserter(qasList));
        qARepository->setQuestions(qasList);
        teacher.setQuestions(qas);
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
        saver.save(qARepository->getQAs(), getFilePathToSaveFromDialog());
    }
    catch(FileException &e)
    {
        showFileErrorMessageBox(e);
    }
}

void MainWindow::on_actionStart_triggered()
{
    if(teacher.questionsToLearnNum()==0)
        return;

    updateQuestion();
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
        teacher.setQuestions(qAsQueue);
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
