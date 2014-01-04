#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include "teaching/teacheradapter.h"
#include "qa/qaimporter.h"

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
    void on_pushButtonNextWord_clicked();
    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_actionStart_triggered();

    void on_actionImport_QA_triggered();

signals:
    void emptyQAContainer();

private:
    Ui::MainWindow *ui;
    TeacherAdapter teacher;
    QPair<QString,QString> currentQA;
    QStateMachine stateMachine;
    QState idleState;
    QState startLearn;

};

#endif // MAINWINDOW_H
