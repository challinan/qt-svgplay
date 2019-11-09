#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // KeyHandler *keyHandler = new KeyHandler();
    // connect (keyHandler, SIGNAL (KeyPressed(char)), this, SLOT(OnConsoleKeyPressed(char)));
    // keyHandler->start();

    // event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
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

/////  Keyboard key handlers
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        ui->myQLabel->setText("ESC Pressed");
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        ui->myQLabel->setText("ESC Released");
    }
}

void MainWindow::on_setTextButton_clicked()
{
    QString lStr = toggle ? "On" : "Off";
    qDebug("setTextLable button pushed");
    ui->myQLabel->setText(lStr);
    toggle = !toggle;
}

