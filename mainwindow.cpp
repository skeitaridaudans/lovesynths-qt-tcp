
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    current_operator = 0;
    adding_modulator = false;
    removing_modulator = false;
    for(int i = 0; i < 6; i++){
        oper_on[i] = false;
        vertical_position[i] = 50;
        horizontal_position[i] = 50;
    }
    update_slider_values(current_operator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::concatTextOutput(QString txt){

    ui->textBox01->setPlainText(ui->textBox01->toPlainText() + txt);
    ui->textBox01->verticalScrollBar()->setValue(ui->textBox01->verticalScrollBar()->maximum());
    QTextCursor tc = ui->textBox01->textCursor();
    tc.setPosition(ui->textBox01->document()->characterCount() - 1);
    ui->textBox01->setTextCursor(tc);
}

void MainWindow::on_actionConnect_to_server_triggered()
{
    concatTextOutput("Client starting...\n");

    // if(tcp.connectToServer("10.121.101.48", 4893)){
    if(tcp.connectToServer("127.0.0.1", 4893)){
        concatTextOutput("Connected to server!\n");
    }
    else{
        concatTextOutput("Connection failed!\n");
    }

//    concatTextOutput(tcp.sendOperatorValue(1, 1, 0, 2.0, 1.5) + "\n");
//    concatTextOutput(tcp.addCarrier(1) + "\n");
//    concatTextOutput(tcp.addModulator(0, 3) + "\n");
//    concatTextOutput(tcp.removeModulator(1, 0) + "\n");
    tcp.removeCarrier(0);
    tcp.removeCarrier(1);
    tcp.removeCarrier(2);
    tcp.removeCarrier(3);
    tcp.removeCarrier(4);
    tcp.removeCarrier(5);

    ui->attackSlider->setSliderPosition(30);
    ui->decaySlider->setSliderPosition(50);
    ui->sustainSlider->setSliderPosition(70);
    ui->releaseSlider->setSliderPosition(20);

    tcp.setAttackAmpEnvelopeSize(0);
    tcp.setAttackAmpEnvelopePoint(0, 0.0, 0.0);
//    tcp.setAttackAmpEnvelopeSize(2);
    tcp.setAttackAmpEnvelopePoint(1, 1.0, (float)ui->attackSlider->sliderPosition() / 100.0);
//    tcp.setAttackAmpEnvelopeSize(3);
    tcp.setAttackAmpEnvelopePoint(2, (float)ui->sustainSlider->sliderPosition() / 100.0, (float)(ui->attackSlider->sliderPosition() + ui->decaySlider->sliderPosition()) / 100.0);
    tcp.setReleaseAmpEnvelopeSize(0);
    tcp.setReleaseAmpEnvelopePoint(0, 0.0, (float)ui->releaseSlider->sliderPosition() / 100.0);
}


void MainWindow::on_actionClear_output_triggered()
{
    ui->textBox01->setPlainText("");
}



void MainWindow::on_pushButton_toggled(bool checked)
{
}


void MainWindow::on_actionDisconnect_from_server_triggered()
{
    tcp.disconnectFromServer();
    concatTextOutput("Disconnected from server.\n");
}

void MainWindow::press_operator_button(int oper){
    if(adding_modulator){
        tcp.addModulator(current_operator, oper);
        concatTextOutput("Operator " + QString::number(current_operator) + " is now modulated by operator " + QString::number(oper) + "!\n");
        adding_modulator = false;
    }
    else if(removing_modulator){
        tcp.removeModulator(current_operator, oper);
        concatTextOutput("Operator " + QString::number(current_operator) + " is now NOT modulated by operator " + QString::number(oper) + "!\n");
        removing_modulator = false;
    }
    else if(current_operator == oper){
        oper_on[oper] = !oper_on[oper];
        if(oper_on[oper]){
            tcp.addCarrier(oper);
            concatTextOutput("Operator " + QString::number(current_operator) + " is now a carrier!\n");
        }
        else{
            tcp.removeCarrier(oper);
            concatTextOutput("Operator " + QString::number(current_operator) + " is NOT a carrier!\n");
        }
    }
    else{
        current_operator = oper;
        update_slider_values(current_operator);
        concatTextOutput("Currently editing operator: " + QString::number(current_operator) + "\n");
    }
}

void MainWindow::on_pushButton_pressed()
{
    press_operator_button(0);
}
void MainWindow::on_pushButton_1_clicked()
{
    press_operator_button(1);
}
void MainWindow::on_pushButton_3_clicked()
{
    press_operator_button(2);
}
void MainWindow::on_pushButton_2_clicked()
{
    press_operator_button(3);
}
void MainWindow::on_pushButton_4_clicked()
{
    press_operator_button(4);
}
void MainWindow::on_pushButton_5_clicked()
{
    press_operator_button(5);
}

void MainWindow::update_slider_values(int oper){
    float freq = pow(1.90366, (float)(horizontal_position[oper] - 50) / 20.0);
    float amp = pow(1.6, (float)(vertical_position[oper] - 50) / 20.0) - 0.3;
    // concatTextOutput(QString::number(freq) + " : " + QString::number(amp) + "\n");
    tcp.sendOperatorValue(current_operator, 1, 0, freq, amp);
    ui->frequencySlider->setSliderPosition(horizontal_position[oper]);
    ui->amplitudeSlider->setSliderPosition(vertical_position[oper]);
}

void MainWindow::on_frequencySlider_sliderMoved(int position)
{
    horizontal_position[current_operator] = position;
    update_slider_values(current_operator);
}


void MainWindow::on_amplitudeSlider_sliderMoved(int position)
{
    vertical_position[current_operator] = position;
    update_slider_values(current_operator);
}


void MainWindow::on_pushButton_6_clicked()
{
    concatTextOutput("Click a modulator for operator: " + QString::number(current_operator) + "\n");
    adding_modulator = true;
    removing_modulator = false;
}


void MainWindow::on_pushButton_7_clicked()
{
    concatTextOutput("Click a modulator to remove from operator: " + QString::number(current_operator) + "\n");
    removing_modulator = true;
    adding_modulator = false;
}


void MainWindow::on_decaySlider_sliderMoved(int position)
{
    tcp.setAttackAmpEnvelopePoint(2, (float)ui->sustainSlider->sliderPosition() / 100.0, (float)(ui->attackSlider->sliderPosition() + position) / 100.0);
}


void MainWindow::on_attackSlider_sliderMoved(int position)
{
    tcp.setAttackAmpEnvelopePoint(1, 1.0, (float)position / 100.0);
    tcp.setAttackAmpEnvelopePoint(2, (float)ui->sustainSlider->sliderPosition() / 100.0, (float)(ui->attackSlider->sliderPosition() + ui->decaySlider->sliderPosition()) / 100.0);
}


void MainWindow::on_sustainSlider_sliderMoved(int position)
{
    tcp.setAttackAmpEnvelopePoint(2, (float)position / 100.0, (float)(ui->attackSlider->sliderPosition() + ui->decaySlider->sliderPosition()) / 100.0);
}


void MainWindow::on_releaseSlider_sliderMoved(int position)
{
    tcp.setReleaseAmpEnvelopePoint(0, 0.0, (float)position / 100.0);
}

