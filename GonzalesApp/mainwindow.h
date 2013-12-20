#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtLayerCode/teacheradapter.h"
#include "qaimporter.h"

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

    void on_actionImportQA_triggered();

private:
    Ui::MainWindow *ui;
    TeacherQtAdapter teacher;
    QPair<QString,QString> currentQA;
};

#endif // MAINWINDOW_H
