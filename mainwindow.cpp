
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "lovecommunicationtcp.h"

#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    LoveCommunicationTcp tcp;
    // tcp.connectToServer("127.0.0.1", 4893);
    tcp.connectToServer("10.121.101.122", 4893);

    for(int i = 0; i < 3; i++){
        QString msg = tcp.getMessageString();
        concatTextOutput("Some data: ");
        concatTextOutput(msg);
        concatTextOutput("\n");
        tcp.sendMessageString((msg));
    }
    QString msg = tcp.getMessageString();
    concatTextOutput("Some data: ");
    concatTextOutput(msg);
    concatTextOutput("\n");
    concatTextOutput(tcp.sendOperatorValue(3, true, 0, 1.2, 2.3));
    tcp.disconnectFromServer();
}


void MainWindow::on_actionClear_output_triggered()
{
    ui->textBox01->setPlainText("");
}

