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
#include "../common/Setting.h"


class IQARepository;
class SettingsBuilder;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const UserInfo &userInfo,
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
    void loadSettings();

private slots:
    void on_pushButtonKnowIt_clicked();
    void on_pushButtonDontKnowIt_clicked();
    void on_actionStart_triggered();
    void on_actionImport_QA_triggered();
    void on_pushButtonShowAnswer_clicked();
    void on_treeWidgetQuestions_itemChanged(QTreeWidgetItem *item, int column);
    void on_horizontalSlider_valueChanged(int value);
    void on_toolButtonAddPeriod_clicked();
    void on_toolButtonRemovePeriod_clicked();
    void on_spinBoxMaterialAmount_valueChanged(int);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void startLearn();
    void emptyQA();
    void questionGiven();
    void showAnswer();
    void answerVerified();
    void stopLearn();

private:

    enum MainTabs
    {
        MainTabs_WelcomeScreen = 0,
        Maintabs_Learning,
        MainTabs_Library,
        Maintabs_Settings
    };

    Ui::MainWindow *ui;
    UserInfo userInfo;
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

    std::shared_ptr<QAsSelector> selector;
    std::vector<std::shared_ptr<ISetting>> settings;
    void setupStateMachine();
};

