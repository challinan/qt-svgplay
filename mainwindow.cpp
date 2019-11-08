#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keyb-utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    KeyHandler *keyHandler = new KeyHandler();
    connect (keyHandler, SIGNAL (KeyPressed(char)), this, SLOT(OnConsoleKeyPressed(char)));
    keyHandler->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_close_button_clicked()
{
    QApplication::quit();
}

void MainWindow::OnConsoleKeyPressed(char c)
{
    QMessageBox msgBox;
    QString str = "This key has been pressed: ";
    str.insert(str.size(), QChar(c));
    msgBox.setText(str);
    msgBox.exec();
}

void MainWindow::on_KeyButton_clicked()
{
    OnConsoleKeyPressed('x');
}
