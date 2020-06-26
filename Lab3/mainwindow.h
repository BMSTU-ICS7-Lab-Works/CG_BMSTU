#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphics.h"
#include "secdialog.h"
#include "thirddialog.h"

namespace Ui {
    class MainWindow;

}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonBlack_2_clicked();

    void on_ButtonYellow_2_clicked();

    void on_ButtonWhite_2_clicked();

    void on_ButtonRed_2_clicked();

    void on_ButtonOrange_2_clicked();

    void on_ButtonPurple_2_clicked();

    void on_ButtonBlue_2_clicked();

    void on_ButtonGreen_2_clicked();

    void on_ButtonBlack_clicked();

    void on_ButtonWhite_clicked();

    void on_ButtonYellow_clicked();

    void on_ButtonRed_clicked();

    void on_ButtonOrange_clicked();

    void on_ButtonPurple_clicked();

    void on_ButtonBlue_clicked();

    void on_ButtonGreen_clicked();

    void on_ClearButton_clicked();

    void on_DrawButton_clicked();

    void on_AnalyzeButton_clicked();

    void on_AnalyzeEffButton_clicked();

    void on_AnalyzeStepButton_clicked();

private:
    Ui::MainWindow *ui;
    SecDialog *secDialog;
    ThirdDialog *thirdDialog;
};

#endif // MAINWINDOW_H
