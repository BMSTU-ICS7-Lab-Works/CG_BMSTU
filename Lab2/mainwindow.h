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


    void on_Resetbutton_clicked();

    void on_Movebutton_clicked();

    void on_Scalebutton_clicked();

    void on_Translatebutton_clicked();

    void on_Undobutton_clicked();

private:
    Ui::MainWindow *ui;

    // Указатель на объект нашего класса
    QPaintWidget *wgt;
};

#endif // MAINWINDOW_H
