#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qa/qasaver.h>
#include <qa/qaloader.h>
#include <stdexcept>
#include "user/logindialog.h"
#include "qa/qarepository.h"
#include "user/UserInfo.h"
#include "common/common.h"
#include "UIAdapters.h"
#include "exceptionhandler.h"
#include <QHeaderView>
#include "filepathbydialogselector.h"
#include "qa/importedqasappender.h"
#include "dialogqaimporterselector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    qARepository(),
    stateIdle(),
    stateLearn(),
    stateQuestionQiven(&stateLearn),
    stateShowAnswer(&stateLearn),
    stateAnswerVerified(&stateLearn)
{
    ui->setupUi(this);
    std::shared_ptr<IQuestionPresenter> l_questionPresenter(new QuestionPresenter(*ui->textEditQuestion));
    std::shared_ptr<IAnswerPresenter> l_answerPresenter(new AnswerPresenter(*ui->textEditAnswer));
    std::shared_ptr<IExceptionHandler> l_exceptionHandler = std::make_shared<ExceptionHandler>();
    std::unique_ptr<IQuestionCollectionPresenter> l_questionCollectionPresenter(new QuestionCollectionPresenter(*ui->treeWidgetQuestions));

    LoginDialog loginDialog;
    loginDialog.setModal(true);
    loginDialog.exec();
    if(loginDialog.result() != QDialog::Accepted)
        exit(0);
    m_userInfo = loginDialog.getUserInfo();
    setWindowTitle(m_userInfo.login);
    setupStateMachine();

    qARepository = std::make_shared<QARepository>(m_userInfo.login,
                                                  l_exceptionHandler,
                                                  std::move(l_questionCollectionPresenter));
    qARepository->load();
    teacher.reset(new TeacherController(std::move(l_questionPresenter),
                                        std::move(l_answerPresenter),
                                        qARepository,
                                        l_exceptionHandler));

    importHandler.reset(new ImportHandler(std::make_shared<FilePathByDialogSelector>(),
                                          std::make_shared<QAFromTextFileImporter>(),
                                          std::make_shared<ImportedQAsAppender>(std::make_shared<QAsImporterSelector>(),
                                                                                qARepository),
                                          l_exceptionHandler));

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
    teacher->showNextQuestion();
}

void MainWindow::on_pushButtonKnowIt_clicked()
{
    teacher->markAsKnownAndShowNextQuestion();
    emit questionGiven();
}

void MainWindow::on_pushButtonDontKnowIt_clicked()
{
    teacher->markAsUnknownAndShowNextQuestion();
    emit questionGiven();
}

void MainWindow::on_pushButtonShowAnswer_clicked()
{
    teacher->showCorrectAnswer();
    emit showAnswer();
}

void MainWindow::on_actionStart_triggered()
{
    teacher->startTeaching();
    emit startLearn();
}

void MainWindow::on_actionImport_QA_triggered()
{
//    QFileDialog dialog(this);
//    QString filePath = dialog.getOpenFileName(this);

//    if(filePath.isEmpty())
//        return;
//    qARepository->import(filePath);
}

void MainWindow::on_treeWidgetQuestions_itemChanged(QTreeWidgetItem *item, int column)
{
    if(column != 2)
        return;

}
