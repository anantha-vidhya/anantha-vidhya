#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showTime();
    void showDate();

    void on_Status_Read_clicked();

    void on_i2creg_write_clicked();

    void on_set_date_clicked();

private:
    Ui::MainWindow *ui;
    void update_date_time();
};

#endif // MAINWINDOW_H
