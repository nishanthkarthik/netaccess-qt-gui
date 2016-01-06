#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "curl/curl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton* button = findChild<QPushButton*>("clickMeButton");
    connect(button, SIGNAL (released()),this, SLOT (handleButton()));
}

int MainWindow::handleButton()
{
    QMessageBox messageBox;
    messageBox.setText("Hello world from Qt");
    qDebug("Button click logged");
    int retCode = messageBox.exec();
    return retCode;
}

MainWindow::~MainWindow()
{
    delete ui;
}
