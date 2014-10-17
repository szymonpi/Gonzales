#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <stdexcept>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../qa/IQARepository.h"
#include "../user/UserInfo.h"
#include "../common/Common.h"
#include "../uiobservers/QuestionCollectionPresenter.h"
#include "../qa/QAsSelection/QAsToLearnByUserChecker.h"
#include "TeacherControllerFactory.h"
#include "../uiobservers/QAPresenter.h"

void MainWindow::loadUserData()
{
    qARepository->load();
}

MainWindow::MainWindow(const UserInfo &userInfo,
                       std::shared_ptr<IQARepository> qARepository,
                       std::shared_ptr<ImportHandler> importHandler,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userInfo(userInfo),
    qARepository(qARepository),
    importHandler(importHandler),
    stateIdle(),
    stateLearn(),
    stateQuestionQiven(&stateLearn),
    stateShowAnswer(&stateLearn),
    stateAnswerVerified(&stateLearn)
{
    ui->setupUi(this);
    setupWindowUI();
    setupControllers();
    loadUserData();

}

void MainWindow::setupWindowUI()
{
    setWindowTitle("Logged as "+m_userInfo.login);
    setupStateMachine();
}

void MainWindow::setupControllers()
{
    std::shared_ptr<IQuestionCollectionPresenter> l_questionCollectionPresenter(
                                new QuestionCollectionPresenter(*ui->treeWidgetQuestions));

    std::shared_ptr<IQAPresenter> l_qaPresenter =
            std::make_shared<QAPresenter>(*ui->textEditQuestion,
                                          *ui->textEditAnswer);

    qARepository->registerQuestionCollectionPresenter(l_questionCollectionPresenter);
    TeacherControllerFactory teacherControllerFactory(qARepository);
    teacherController = teacherControllerFactory.create(l_qaPresenter);
    connect(teacherController.get(), SIGNAL(stopLearn()), this, SIGNAL(stopLearn()));
}

void MainWindow::setupStateMachine()
{
    stateLearn.setInitialState(&stateQuestionQiven);
    stateIdle.addTransition(this, SIGNAL(startLearn()), &stateLearn);

    stateLearn.addTransition(this, SIGNAL(emptyQA()), &stateIdle);
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
    ui->MainTab->setCurrentIndex(0);
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

void MainWindow::on_spinBoxNewMaterialAmount_editingFinished()
{

}
