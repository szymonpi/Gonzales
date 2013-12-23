#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtLayerCode/teacheradapter.h>
#include <qasaver.h>

QMap<QString, QString> getQuestionsAndAnswers()
{
    QMap<QString, QString> map;
    map["tak"] = "yes";
    map["przedimek okreslony przed rzeczownikami"] = "the";
    map["od, na, z, u"] = "of";
    return map;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    teacher(getQuestionsAndAnswers())
{
    ui->setupUi(this);
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
        ui->pushButtonNextWord->setDisabled(true);
        ui->pushButtonDontKnowIt->setDisabled(true);
        ui->pushButtonKnowIt->setDisabled(true);
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

    if(fileInfo.suffix()=="qa")
    {
        // load qa;
    }
    else
    {
        QAFromTextFileImporter importer(file);
        QQueue<QA> importedQAs = importer.import();
        teacher.setQuestions(importedQAs);
        QMessageBox importMessage(this);
        importMessage.setWindowTitle("import");
        QString numberOfImportedItems;
        importMessage.setText(numberOfImportedItems.setNum(importedQAs.size())+"question and answer item has been imported.");
        importMessage.exec();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName();

    File file(filePath);
    file.open(QFile::WriteOnly);
    QASaver saver(file);
    //saver.save()
}
