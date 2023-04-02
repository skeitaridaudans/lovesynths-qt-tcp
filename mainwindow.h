
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void concatTextOutput(QString txt);

private slots:
    void on_actionConnect_to_server_triggered();

    void on_actionClear_output_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
