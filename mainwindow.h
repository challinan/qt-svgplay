#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnConsoleKeyPressed(char c);
private slots:
    void on_close_button_clicked();
    void on_KeyButton_clicked();
    void on_setTextButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::MainWindow *ui;
    // QKeyEvent *event;
    // QLabel *notice1Label;
    bool toggle;
};

#endif // MAINWINDOW_H
