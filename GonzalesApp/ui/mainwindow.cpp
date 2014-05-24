#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <stdexcept>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../qa/qasaver.h"
#include "../qa/qaloader.h"
#include "../ui/dialogs/LoginDialog.h"
#include "../qa/qarepository.h"
#include "../user/UserInfo.h"
#include "../common/common.h"
#include "../uiobservers/AnswerPresenter.h"
#include "../uiobservers/QuestionPresenter.h"
#include "../uiobservers/QuestionCollectionPresenter.h"
#include "../uiobservers/exceptionhandler.h"
#include "../uiobservers/filepathbydialogselector.h"
#include "../qa/QAsAppender.h"
#include "../ui/dialogs/DialogQAImporterSelector.h"
#include "../uiobservers/QAsDestinationSelector.h"
#include "../qa/QALoader.h"
#include "../TeacherControllerFactory.h"
#include "../ImportHandlerFactory.h"
#include "../QARepositoryFactory.h"
#include "../qa/QAsToLearnByUserChecker.h"

void MainWindow::loadUserData()
{
    qARepository->load();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stateIdle(),
    stateLearn(),
    stateQuestionQiven(&stateLearn),
    stateShowAnswer(&stateLearn),
    stateAnswerVerified(&stateLearn)
{
    ui->setupUi(this);
    authorize();
    setupWindowUI();
    setupControllers();
    loadUserData();

}

void MainWindow::authorize()
{
    LoginDialog loginDialog;
    loginDialog.setModal(true);
    loginDialog.exec();
    if(!loginDialog.isAuthorized())
        exit(0);
    m_userInfo = loginDialog.getUserInfo();
}

void MainWindow::setupWindowUI()
{
    setWindowTitle(m_userInfo.login);
    setupStateMachine();
}

void MainWindow::setupControllers()
{
    QARepositoryFactory qARepositoryFactory(*ui->treeWidgetQuestions,
                                            m_userInfo.login);
    qARepository = qARepositoryFactory.create();

    TeacherControllerFactory teacherControllerFactory(qARepository, *ui->textEditQuestion, *ui->textEditAnswer);
    ImportHandlerFactory importFactory(qARepository);

    teacherController = teacherControllerFactory.create();
    importHandler = importFactory.create();
}

void MainWindow::setupStateMachine()
{
    stateLearn.setInitialState(&stateQuestionQiven);
    stateIdle.addTransition(this, SIGNAL(startLearn()), &stateLearn);

    stateLearn.addTransition(this, SIGNAL(emptyQAContainer()), &stateIdle);
    stateLearn.addTransition(this, SIGNAL(stopLearn()), &stateIdle);
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

void MainWindow::showNextQuestion()
{
    teacherController->showNextQuestion();
}

void MainWindow::on_pushButtonKnowIt_clicked()
{
    teacherController->markAsKnownAndShowNextQuestion();
    emit questionGiven();
}

void MainWindow::on_pushButtonDontKnowIt_clicked()
{
    teacherController->markAsUnknownAndShowNextQuestion();
    emit questionGiven();
}

void MainWindow::on_pushButtonShowAnswer_clicked()
{
    teacherController->showCorrectAnswer();
    emit showAnswer();
}

void MainWindow::on_actionStart_triggered()
{
    teacherController->startTeaching();
    emit startLearn();
}

void MainWindow::on_actionImport_QA_triggered()
{
    importHandler->import();
}

void MainWindow::on_treeWidgetQuestions_itemChanged(QTreeWidgetItem *item, int column)
{
    if(column != 2)
        return;
    QAsToLearnByUserChecker selector(qARepository);
    selector.select(*item);
}
