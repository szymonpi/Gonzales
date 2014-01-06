#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qa/qasaver.h>
#include <qa/qaloader.h>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stateIdle(),
    stateLearn(),
    stateAnswerVerified(&stateLearn),
    stateShowAnswer(&stateLearn),
    stateQuestionQiven(&stateLearn),
    teacher()
{
    ui->setupUi(this);

    stateLearn.setInitialState(&stateQuestionQiven);

    stateIdle.addTransition(this, SIGNAL(startLearn()), &stateLearn);

    stateLearn.addTransition(this, SIGNAL(emptyQAContainer()), &stateIdle);
    stateQuestionQiven.addTransition(this, SIGNAL(showAnswer()), &stateShowAnswer);
    stateShowAnswer.addTransition(this, SIGNAL(questionGiven()), &stateQuestionQiven);


    stateIdle.assignProperty(ui->pushButtonDontKnowIt, "enabled", false);
    stateIdle.assignProperty(ui->pushButtonKnowIt, "enabled", false);
    stateIdle.assignProperty(ui->pushButtonShowAnswer, "enabled", false);


    stateQuestionQiven.assignProperty(ui->pushButtonDontKnowIt, "disabled", true);
    stateQuestionQiven.assignProperty(ui->pushButtonKnowIt, "disabled", true);
    stateQuestionQiven.assignProperty(ui->pushButtonShowAnswer, "enabled", true);

    stateShowAnswer.assignProperty(ui->pushButtonDontKnowIt, "enabled", true);
    stateShowAnswer.assignProperty(ui->pushButtonKnowIt, "enabled", true);
    stateShowAnswer.assignProperty(ui->pushButtonShowAnswer, "disabled", true);

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
    if(teacher.questionsToLearnNum()>0)
    {
        setNewQuestion(teacher.getNextQuestion());
    }
    else
    {
        emit emptyQAContainer();
    }
}

void MainWindow::on_pushButtonKnowIt_clicked()
{
    currentQA.second = teacher.getCorrectAnswer(currentQA.first);
    ui->textEditAnswer->setText(currentQA.second);
    ui->textEditAnswer->update();
    teacher.checkAnswer(currentQA.second);
    ui->pushButtonKnowIt->setDisabled(true);
    ui->pushButtonDontKnowIt->setDisabled(true);
    if(teacher.questionsToLearnNum()==0)
    {
        emit emptyQAContainer();
    }
}

void MainWindow::on_pushButtonDontKnowIt_clicked()
{
    ui->textEditAnswer->update();
    teacher.checkAnswer(currentQA.second + "WRONG WRONG WRONG");

    if(teacher.questionsToLearnNum()==0)
    {
        emit emptyQAContainer();
    }
    emit answerVerified();
}

//void MainWindow::on_pushButtonNextWord_clicked()
//{
//    updateQuestion();
//}

void MainWindow::on_actionLoad_triggered()
{
    QFileDialog dialog(this);
    QString filePath = dialog.getOpenFileName(this);
    File file(filePath);
    QFileInfo fileInfo(filePath);

    if(filePath.isEmpty())
        return;

    file.open(QFile::ReadOnly);
    QQueue<QA> qAs;
    QALoader loader(file);
    try
    {
        qAs = loader.load();
        teacher.setQuestions(qAs);
    }
    catch(FileException &e)
    {
        qDebug() << e.what();
    }
    catch(std::logic_error &e)
    {
        qDebug() << e.what();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName();

    File file(filePath);
    file.open(QFile::WriteOnly);
    QASaver saver(file);
    try
    {
        bool saved = saver.save(teacher.getQAs());
        if(!saved)
        {
            QMessageBox saveMessage(this);
            saveMessage.setWindowTitle("save");
            saveMessage.setText("can't save file");
            saveMessage.exec();
        }

    }
    catch(FileException &e)
    {
        qDebug() << e.what();
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
    File file(filePath);
    QFileInfo fileInfo(filePath);

    if(filePath.isEmpty())
        return;

    QAFromTextFileImporter importer(file);
    try{
        QQueue<QA> importedQAs = importer.import();
        teacher.setQuestions(importedQAs);
        QMessageBox importMessage(this);
        importMessage.setWindowTitle("import");
        QString numberOfImportedItems;
        importMessage.setText(numberOfImportedItems.setNum(importedQAs.size())+"question and answer item has been imported.");
        importMessage.exec();
    }
    catch(FileException &e)
    {
        qDebug() << e.what();
    }
}

void MainWindow::on_pushButtonShowAnswer_clicked()
{
    currentQA.second = teacher.getCorrectAnswer(currentQA.first);
    ui->textEditAnswer->setText(currentQA.second);
}
