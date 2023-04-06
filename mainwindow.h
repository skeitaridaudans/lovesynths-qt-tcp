
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lovecommunicationtcp.h"


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

    void on_pushButton_pressed();

    void on_pushButton_toggled(bool checked);

    void on_actionDisconnect_from_server_triggered();

    void on_pushButton_1_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_frequencySlider_sliderMoved(int position);

    void on_amplitudeSlider_sliderMoved(int position);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_decaySlider_sliderMoved(int position);

    void on_attackSlider_sliderMoved(int position);

    void on_sustainSlider_sliderMoved(int position);

    void on_releaseSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    LoveCommunicationTcp tcp;

    void update_slider_values(int oper);
    void press_operator_button(int oper);

    int current_operator;
    bool oper_on[6];
    float horizontal_position[6];
    float vertical_position[6];
    bool adding_modulator;
    bool removing_modulator;
};

#endif // MAINWINDOW_H
