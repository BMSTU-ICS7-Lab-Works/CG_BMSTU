#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "qcustomplot.h"
#include "graphics.h"
#include "bresenham.h"
#include "canonic.h"
#include "midpoint.h"
#include "parametric.h"
#include "plot.h"
#include "dialog.h"
#include "time.h"
#include <QtCharts>

using namespace QtCharts;
#include <QLabel>

#define WHITE {255, 255, 255}
#define RED {255, 0, 0}
#define ORANGE {255, 102, 0}
#define YELLOW {255, 255, 0}
#define GREEN {0, 255, 0}
#define BLUE {0, 0, 255}
#define PURPLE {128, 0, 128}
#define BLACK {0, 0, 0}

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

    void on_DrawEllipse_clicked();

    void on_AnalyzeButton_clicked();

    void on_AnalyzeEffButton_clicked();

    void on_EllSpectre_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *dialog;
};

#endif // MAINWINDOW_H
