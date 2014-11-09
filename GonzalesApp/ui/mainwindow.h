#pragma once

#include <QMainWindow>
#include <QStateMachine>
#include <memory>
#include "qa/qaio/QAImporter.h"
#include "user/UserInfo.h"
#include "teaching/TeacherController.h"
#include "qa/ImportHandler.h"
#include <QTreeWidgetItem>
#include <qa/QAsSelection/Selectors/QAsSelector.h>

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
    void on_horizontalSlider_valueChanged(int value);
    void on_checkBoxRepetitionOnly_toggled(bool checked);
    void on_toolButtonAddPeriod_clicked();

    void on_toolButtonRemovePeriod_clicked();

    void on_spinBoxMaterialAmount_valueChanged(int);

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
    std::shared_ptr<IQASelectorSettings> selectorSettings;

    QPair<QString,QString> currentQA;
    QStateMachine stateMachine;

    QState stateIdle;
    QState stateLearn;
        QState stateQuestionQiven;
        QState stateShowAnswer;
        QState stateAnswerVerified;

    int newMaterialAmount = 0;


    void setupStateMachine();
};

