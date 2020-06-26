#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtCharts>

using namespace QtCharts;
#include <QMessageBox>
#include <QLabel>
#include "cda.h"
#include "bresint.h"
#include "bresfloat.h"
#include "wu.h"
#include "graphics.h"
#include "secdialog.h"


#include <math.h>

void BresSmooth(double xstart, double ystart, double xend, double yend, graphics_t &graphics)
{
    int I = 255;
    int deltax = xend - xstart;
    int deltay = yend - ystart;
    int sx = sign(deltax);
    int sy = sign(deltay);
    deltax = abs(deltax);
    deltay = abs(deltay);
    int exch;
    double deltaerr = double(deltay) / deltax;
    if (deltaerr > 1)
    {
        double tmp = deltax;
        deltax = deltay;
        deltay = tmp;
        deltaerr = 1 / deltaerr;
        exch = 1;
    }
    else
        exch = 0;
    double err = I / 2;
    int x = xstart;
    int y = ystart;
    deltaerr *= I;
    double w = I - deltaerr;
    QColor lncolor = graphics.pen.color();
    graphics.scene->addLine(x, y, x, y, graphics.pen);
    for (int i = 0; i <= deltax; i++)
    {
        if (err <= w)
        {
            if (exch == 0)
            {
                x += sx;
            }
            else
                y += sy;
            err += deltaerr;
        }
        else
        {
            y += sy;
            x += sx;
            err -= w;
        }
        lncolor.setAlphaF(1 - (err / I));
        graphics.pen.setColor(lncolor);
        graphics.scene->addLine(x, y, x, y, graphics.pen);
    }
}


#define WHITE {255, 255, 255}
#define RED {255, 0, 0}
#define ORANGE {255, 102, 0}
#define YELLOW {255, 255, 0}
#define GREEN {0, 255, 0}
#define BLUE {0, 0, 255}
#define PURPLE {128, 0, 128}
#define BLACK {0, 0, 0}

graphics_t graphics;
graphics_t tmp_graphics;
double xstart, ystart;
double xend, yend;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphics.scene = new QGraphicsScene(ui->graphicsView);
    graphics.scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    tmp_graphics.scene = new QGraphicsScene(ui->graphicsView);
    tmp_graphics.scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    //Начальные параметры линии
    graphics.pen.setColor(BLACK);
    tmp_graphics.pen.setColor(BLACK);

    //Начальные параметры фоны
    graphics.bg = WHITE;
    graphics.scene->setBackgroundBrush(graphics.bg);

    tmp_graphics.bg = WHITE;
    tmp_graphics.scene->setBackgroundBrush(graphics.bg);

    ui->graphicsView->setScene(graphics.scene);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonBlack_2_clicked()
{
    graphics.bg = BLACK;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonYellow_2_clicked()
{
    graphics.bg = YELLOW;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonWhite_2_clicked()
{
    graphics.bg = WHITE;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonRed_2_clicked()
{
    graphics.bg = RED;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonOrange_2_clicked()
{
    graphics.bg = ORANGE;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonPurple_2_clicked()
{
    graphics.bg = PURPLE;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonBlue_2_clicked()
{
    graphics.bg = BLUE;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonGreen_2_clicked()
{
    graphics.bg = GREEN;
    graphics.scene->setBackgroundBrush(graphics.bg);
}

void MainWindow::on_ButtonBlack_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-черный)");
    graphics.pen.setColor(BLACK);
}

void MainWindow::on_ButtonWhite_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-белый)");
    graphics.pen.setColor(WHITE);
}

void MainWindow::on_ButtonYellow_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-желтый)");
    graphics.pen.setColor(YELLOW);
}

void MainWindow::on_ButtonRed_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-красный)");
    graphics.pen.setColor(RED);
}

void MainWindow::on_ButtonOrange_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-оранжевый)");
    graphics.pen.setColor(ORANGE);
}

void MainWindow::on_ButtonPurple_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-фиолетовый)");
    graphics.pen.setColor(PURPLE);
}

void MainWindow::on_ButtonBlue_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-голубой)");
    graphics.pen.setColor(BLUE);
}

void MainWindow::on_ButtonGreen_clicked()
{
    ui->label_line->setText("Цвет линии(текущий цвет-зеленый)");
    graphics.pen.setColor(GREEN);
}

void MainWindow::on_ClearButton_clicked()
{
    graphics.scene->clear();
}

void MainWindow::on_DrawButton_clicked()
{
    xstart = ui->Xstart->text().toDouble();
    ystart = ui->Ystart->text().toDouble();
    xend = ui->Xend->text().toDouble();
    yend = ui->Yend->text().toDouble();
    //qDebug() << "xstart = " << xstart << "strung = " << ui->Xstart->text();
    if (ui->ButtonBA->isChecked())
    {
        //algorithm = BA;
        graphics.scene->addLine(round(xstart), round(ystart), round(xend), round(yend), graphics.pen);
    }
    else if (ui->ButtonBF->isChecked())
    {
        //algorithm = BF;
        BresFloat(xstart, ystart, xend, yend, graphics);
    }
    else if (ui->ButtonBI->isChecked())
    {
        //algorithm = BI;
        BresInt(xstart, ystart, xend, yend, graphics);
    }
    else if (ui->ButtonBS->isChecked())
    {
       // algorithm = BS;
        QColor lncolor = graphics.pen.color();
        BresSmooth(xstart, ystart, xend, yend, graphics);
        graphics.pen.setColor(lncolor);
    }
    else if (ui->ButtonCD->isChecked())
    {
        //algorithm = CD;
        cda(xstart, ystart, xend, yend, graphics);
    }
    else if (ui->ButtonWU->isChecked())
    {
        QColor lncolor = graphics.pen.color();
        Wu(xstart, ystart, xend, yend, graphics);
        graphics.pen.setColor(lncolor);
    }
    else
    {
        QMessageBox::critical(NULL, "ERROR", "Не выбран алгоритм");
    }
}

void library_algorithm(double xstart, double ystart, double xend, double yend, graphics_t &graphics)
{
    graphics.scene->addLine(round(xstart), round(ystart), round(xend), round(yend), graphics.pen);
}

void draw_analyze(double xstart, double ystart, double xend, double yend, int angle,\
                  void(*algorithm)(double x0, double y0, double x1, double y1, graphics_t &graphics),\
                  graphics_t &graphics)
{
    double tmp;
    int i = 0;
    int count = 360 / angle;
    do
    {
        algorithm(xstart, ystart, xend, yend, graphics);
        tmp = xstart + (xend - xstart) * cos(angle * M_PI / 180) + (yend - ystart) * sin(angle * M_PI / 180);
        yend = ystart - (xend - xstart) * sin(angle * M_PI / 180) + (yend - ystart) * cos(angle * M_PI / 180);
        xend = tmp;
        i++;
    }while (i < count);
}



void MainWindow::on_AnalyzeButton_clicked()
{
    double xstart = ui->Xstart->text().toDouble();
    double ystart = ui->Ystart->text().toDouble();
    double xend = ui->Xend->text().toDouble();
    double yend = ui->Yend->text().toDouble();
    double angle = ui->Angleline->value();
    if (ui->ButtonBA->isChecked())
    {
        draw_analyze(xstart, ystart, xend, yend, round(angle), library_algorithm, graphics);
    }
    else if (ui->ButtonBF->isChecked())
    {
        draw_analyze(xstart, ystart, xend, yend, round(angle), BresFloat, graphics);
    }
    else if (ui->ButtonBI->isChecked())
    {
        draw_analyze(xstart, ystart, xend, yend, round(angle), BresInt, graphics);
    }
    else if (ui->ButtonBS->isChecked())
    {
        draw_analyze(xstart, ystart, xend, yend, round(angle), BresSmooth, graphics);
    }
    else if (ui->ButtonCD->isChecked())
    {
        draw_analyze(xstart, ystart, xend, yend, round(angle), cda, graphics);
    }
    else if (ui->ButtonWU->isChecked())
    {
        draw_analyze(xstart, ystart, xend, yend, round(angle), Wu, graphics);
    }
    else
    {
        QMessageBox::critical(NULL, "ERROR", "Не выбран алгоритм");
    }
}

void MainWindow::on_AnalyzeEffButton_clicked()
{
    QBarSet *set0 = new QBarSet("Алгоритмы");

    *set0 << 0.000168 << 0.00014 << 0.00011 << 0.000168 << 0.000275;

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Среднее время построения отрезка длиной 100, в секундах");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "ЦДА" << "Брезенхем с действ." << "Брезенхем с целоч." << "Брезенхем с устр. ступенч." << "Ву";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,0.0003);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    secDialog = new SecDialog(this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(chartView);
    secDialog->setLayout(layout);
    secDialog->resize(420, 300);
    secDialog->show();
}

void MainWindow::on_AnalyzeStepButton_clicked()
{
    QLineSeries *series = new QLineSeries();
    int res[91] = {0};
    /*

    */

    double tmp;
    int i = 0;
    int count = 91;
    double xn = 0;
    double yn = 0;
    double xk = 199;
    double yk = 0;
    do
    {
        res[i] = cda_steps(xn, yn, xk, yk);
        tmp = xn + (xk - xn) * cos(M_PI / 180) + (yk - yn) * sin(M_PI / 180);
        yk = yn - (xk - xn) * sin(M_PI / 180) + (yk - yn) * cos(M_PI / 180);
        xk = tmp;
        i++;

    }while (i < count);

    for (int i = 0; i < 91; i ++)
    {
        qDebug() << "i = " << i << "res[i] = " << res[i];
        if (i == 45)
        {
            series->append(i, 1);
        }
        else
        {
            series->append(i, res[i]);
        }
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Анализ ступенчатости");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    thirdDialog = new ThirdDialog(this);
    QGridLayout *layout = new QGridLayout;
    QLabel *label = new QLabel(thirdDialog);
    label->setText("                                    зеленый - Брезенхем действительный\n                \
                    красный - Брезенхем целочисленный\n                                    синий - цифровой дифференциальный анализатор");
    label->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(chartView);
    thirdDialog->setLayout(layout);
    //thirdDialog->resize(420, 300);
    thirdDialog->show();

}


