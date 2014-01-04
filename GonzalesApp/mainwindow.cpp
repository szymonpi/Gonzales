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
    teacher()
{
    ui->setupUi(this);

    idleState.assignProperty(ui->pushButtonDontKnowIt, "enabled", false);
    idleState.assignProperty(ui->pushButtonKnowIt, "enabled", false);
    idleState.assignProperty(ui->pushButtonNextWord, "enabled", false);

    startLearn.assignProperty(ui->pushButtonDontKnowIt, "enabled", true);
    startLearn.assignProperty(ui->pushButtonKnowIt, "enabled", true);
    startLearn.assignProperty(ui->pushButtonNextWord, "enabled", true);

    stateMachine.addState(&idleState);
    stateMachine.addState(&startLearn);

    idleState.addTransition(ui->actionStart, SIGNAL(triggered()), &startLearn);
    startLearn.addTransition(this, SIGNAL(emptyQAContainer()), &idleState);

    stateMachine.setInitialState(&idleState);
    stateMachine.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateQuestion()
{
    if(teacher.questionsToLearnNum()>0)
    {
        currentQA.first = teacher.getNextQuestion();
        ui->textEditAnswer->clear();
        ui->textEditAnswer->update();
        ui->pushButtonDontKnowIt->setEnabled(true);
        ui->pushButtonKnowIt->setEnabled(true);
        ui->textEditQuestion->setText(currentQA.first);
        ui->textEditQuestion->update();
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
        ui->pushButtonNextWord->setDisabled(true);
        ui->pushButtonDontKnowIt->setDisabled(true);
        ui->pushButtonKnowIt->setDisabled(true);
    }
}

void MainWindow::on_pushButtonDontKnowIt_clicked()
{
    currentQA.second = teacher.getCorrectAnswer(currentQA.first);
    ui->textEditAnswer->setText(currentQA.second);
    ui->textEditAnswer->update();

    teacher.checkAnswer(currentQA.second + "WRONG WRONG WRONG");
    ui->pushButtonKnowIt->setDisabled(true);
    ui->pushButtonDontKnowIt->setDisabled(true);

    if(teacher.questionsToLearnNum()==0)
    {
        ui->pushButtonNextWord->setDisabled(true);
        ui->pushButtonDontKnowIt->setDisabled(true);
        ui->pushButtonKnowIt->setDisabled(true);
    }
}

void MainWindow::on_pushButtonNextWord_clicked()
{
    updateQuestion();
}

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
    qDebug() << "dupa";
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
