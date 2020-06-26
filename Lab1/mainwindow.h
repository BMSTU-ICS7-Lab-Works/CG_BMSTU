#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

//nash class
#include "qpaintwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:


    void on_Createtable1_clicked();

    void on_Createtable2_clicked();

    void on_Calcbutton_clicked();

    void on_Delbutton1_clicked();

    void on_Delbutton2_clicked();

    void on_Adddot1button_clicked();

    void on_Adddot2button_clicked();


    void on_Detailedbutton_clicked();

private:
    Ui::MainWindow *ui;

    // Указатель на объект нашего класса
    QPaintWidget *wgt;
};

#endif // MAINWINDOW_H
