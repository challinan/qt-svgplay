#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void OnConsoleKeyPressed(char c);
private slots:
    void on_close_button_clicked();


    void on_KeyButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
