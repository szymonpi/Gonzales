#pragma once

#include <QMainWindow>
#include <QStateMachine>
#include <memory>
#include "qa/qaimporter.h"
#include "user/UserInfo.h"
#include "teaching/teachercontroller.h"
#include "qa/ImportHandler.h"
#include <QTreeWidgetItem>

class IQARepository;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const UserInfo &m_userInfo,
                        std::shared_ptr<IQARepository> qARepository,
                        std::shared_ptr<ImportHandler> importHandler,
                        std::shared_ptr<TeacherController> teacherController,
                        QWidget *parent = 0);
    ~MainWindow();

    void updateQuestion();
    void showNextQuestion();
    void authorize();
    void setupWindowUI();
    void setupControllers();
    void loadUserData();
private slots:

    void on_pushButtonKnowIt_clicked();
    void on_pushButtonDontKnowIt_clicked();
    void on_actionStart_triggered();
    void on_actionImport_QA_triggered();
    void on_pushButtonShowAnswer_clicked();
    
    void on_treeWidgetQuestions_itemChanged(QTreeWidgetItem *item, int column);

signals:
    void startLearn();
    void emptyQA();
    void questionGiven();
    void showAnswer();
    void answerVerified();
    void stopLearn();

private:
    Ui::MainWindow *ui;
    UserInfo m_userInfo;
    std::shared_ptr<IQARepository> qARepository;
    std::shared_ptr<ImportHandler> importHandler;
    std::shared_ptr<TeacherController> teacherController;

    QPair<QString,QString> currentQA;
    QStateMachine stateMachine;

    QState stateIdle;
    QState stateLearn;
        QState stateQuestionQiven;
        QState stateShowAnswer;
        QState stateAnswerVerified;


    void setupStateMachine();
};

