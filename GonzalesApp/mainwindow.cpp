#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QtLayerCode/teacheradapter.h>

QMap<QString, QString> getQuestionsAndAnswers()
{
    QMap<QString, QString> map;
    map["tak"] = "yes";
    map["przedimek okreslony przed rzeczownikami"] = "the";
    map["od, na, z, u"] = "of";
//    map["do"] = "to";
//    map["przedimek nieokreslony przed rzeczownikami"] = "a, an";
//    map["to"] = "that";
//    map["powiedzial"] = "said";
//    map["jest"] = "is";
//    map["on"] = "na";
//    map["ono"] = "it";
//    map["bylo"] = "was";
//    map["z"] = "with";
//    map["przy"] = "by";
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
    //todo teacher.setQuestions();
}
