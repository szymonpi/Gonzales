#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <memory>
#include "teaching/teacheradapter.h"
#include "qa/qaimporter.h"

class IQARepository;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateQuestion();
private slots:

    void on_pushButtonKnowIt_clicked();
    void on_pushButtonDontKnowIt_clicked();
    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionStart_triggered();

    void on_actionImport_QA_triggered();

    void on_pushButtonShowAnswer_clicked();

signals:
    void startLearn();
    void emptyQAContainer();
    void questionGiven();
    void showAnswer();
    void answerVerified();

private:
    Ui::MainWindow *ui;
    TeacherAdapter teacher;
    QPair<QString,QString> currentQA;
    QStateMachine stateMachine;
    std::shared_ptr<IQARepository> qARepository;

    QState stateIdle;
    QState stateLearn;
        QState stateQuestionQiven;
        QState stateShowAnswer;
        QState stateAnswerVerified;

    void setNewQuestionInUI();
    void setNewQuestion(const QString &question);
    void setupStateMachine();
    void checkQuestionsToGo();
    QString getFilePathToLoadFromDialog();
    void showFileErrorMessageBox(const FileException &e);
    QString getFilePathToSaveFromDialog();
};

#endif // MAINWINDOW_H
