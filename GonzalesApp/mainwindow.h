#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <memory>
#include "qa/qaimporter.h"
#include "user/UserInfo.h"
#include "teaching/teachercontroller.h"

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
    void showNextQuestion();
private slots:

    void on_pushButtonKnowIt_clicked();
    void on_pushButtonDontKnowIt_clicked();
    void on_actionStart_triggered();
    void on_actionImport_QA_triggered();
    void on_pushButtonShowAnswer_clicked();

signals:
    void startLearn();
    void emptyQAContainer();
    void questionGiven();
    void showAnswer();
    void answerVerified();
    void stopLearn();

private:
    Ui::MainWindow *ui;

    QPair<QString,QString> currentQA;
    QStateMachine stateMachine;
    std::shared_ptr<IQARepository> qARepository;

    QState stateIdle;
    QState stateLearn;
        QState stateQuestionQiven;
        QState stateShowAnswer;
        QState stateAnswerVerified;

    UserInfo m_userInfo;
    std::unique_ptr<TeacherController> teacher;

    void setupStateMachine();
};

#endif // MAINWINDOW_H
