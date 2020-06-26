#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <math.h>

char lastact;
double xscale;
double yscale;
double kxscale;
double kyscale;

double xrotate;
double yrotate;
double angle;

double masx[21];
double masy[21];
const long int N = 100000;
double mashead[N][2];
double masbody[N][2];
double masleye[N][2];
double masreye[N][2];
double massmile[N / 2][2];
double dotpos[2];

double xmove = 0;
double ymove = 0;
double dx = 0;
double dy = 0;
double rotateangle = 0;
bool flag;
bool flag1;
bool flag2;
bool flag3;
const double pi = 3.1415926535;

void defaultdots()
{
    dotpos[0] = -2;
    dotpos[1] = -2;
    //left leg
    masx[0] = -5;
    masy[0] = 38.8;
    masx[1] = -5;
    masy[1] = 60;
    masx[2] = -15;
    masy[2] = 60;
    //right leg
    masx[3] = 5;
    masy[3] = 38.8;
    masx[4] = 5;
    masy[4] = 60;
    masx[5] = 15;
    masy[5] = 60;
    //right arm
    masx[6] = 10;
    masy[6] = -10;
    masx[7] = 40;
    masy[7] = -40;
    masx[8] = 10;
    masy[8] = 10;
    //left arm
    masx[9] = -10;
    masy[9] = -10;
    masx[10] = -40;
    masy[10] = -40;
    masx[11] = -10;
    masy[11] = 10;
    //brows
    //left brow
    masx[12] = 0;
    masy[12] = -70;
    masx[13] = -10;
    masy[13] = -90;
    masx[14] = -20;
    masy[14] = -90;
    //right brow
    masx[15] = 0;
    masy[15] = -70;
    masx[16] = 10;
    masy[16] = -90;
    masx[17] = 20;
    masy[17] = -90;
    double h = 80.0 / N;
    double hsmile = 40.0 / N;
    double heyes = 16.0 / N;
    for (int i = 0; i < N / 2; i ++)
    {
        masbody[i][0] =  i * h - 20;
        masbody[i][1] =  - sqrt(1 -  masbody[i][0] *  masbody[i][0] / (20 * 20)) * 40;
        masbody[i + N / 2][0] =  i * h - 20;
        masbody[i + N / 2][1] =  sqrt(1 -  masbody[i + N / 2][0] *  masbody[i + N / 2][0] / (20 * 20)) * 40;

        mashead[i][0] = i * h - 20;
        mashead[i][1] = -60 - sqrt(1 -  mashead[i][0] *  mashead[i][0] / (20 * 20)) * 20;
        mashead[i + N / 2][0] = i * h - 20;
        mashead[i + N / 2][1] = -60 + sqrt(1 -  mashead[i + N / 2][0] *  mashead[i + N / 2][0] / (20 * 20)) * 20;

        massmile[i][0] = i * hsmile - 10;
        massmile[i][1] = -60 + sqrt(1 -  massmile[i][0] *  massmile[i][0] / (12 * 12)) * 10;

        masleye[i][0] = i * heyes - 12;
        masleye[i][1] = -65 - sqrt(1 - (masleye[i][0] + 8) * (masleye[i][0] + 8) / (4 * 4)) * 4;
        masleye[i + N / 2][0] = i * heyes - 12;
        masleye[i + N / 2][1] = -65 + sqrt(1 - (masleye[i + N / 2][0] + 8) *  (masleye[i + N / 2][0] + 8) / (4 * 4)) * 4;
        //qDebug() << "masleye = " << masleye[i][1] << "masleye x = " << masleye[i][0];
        masreye[i][0] = i * heyes + 4;
        masreye[i][1] = -65 - sqrt(1 - ((masreye[i][0] - 8) * (masreye[i][0] - 8)) / (4 * 4)) * 4;
        masreye[i + N / 2][0] = i * heyes + 4;
        masreye[i + N / 2][1] = -65 + sqrt(1 - ((masreye[i + N / 2][0] - 8) *  (masreye[i + N / 2][0] - 8)) / (4 * 4)) * 4;
        //qDebug() << "masreye = " << masreye[i][1] << "masreye x = " << masreye[i][0];
    }
}

void movedots(double centerx, double centery)
{
    lastact = 'm';
    dotpos[0] += centerx;
    dotpos[1] += centery;
    for (int i = 0; i < 21; i++)
    {
        masx[i] += centerx;
        masy[i] += centery;
    }
    for (int i = 0; i < N; i++)
    {
        mashead[i][0] += centerx ;
        mashead[i][1] += centery;

        masbody[i][0] += centerx;
        masbody[i][1] += centery;

        masleye[i][0] += centerx;
        masleye[i][1] += centery;

        masreye[i][0] += centerx;
        masreye[i][1] += centery;
    }
    for (int j = 0; j < N / 2; j++)
    {
        massmile[j][0] += centerx;
        massmile[j][1] += centery;
    }
}

void scaledots(double xscale, double yscale, double kxscale, double kyscale)
{
    for (int i = 0; i < 21; i++)
    {
        masx[i] = kxscale * masx[i] + (1 - kxscale) * xscale;
        masy[i] = kyscale * masy[i] + (1 - kyscale) * yscale;
    }
    for (int i = 0; i < N; i++)
    {
        mashead[i][0] = kxscale * mashead[i][0] + (1 - kxscale) * xscale;
        mashead[i][1] = kyscale * mashead[i][1] + (1 - kyscale) * yscale;

        masbody[i][0] = kxscale * masbody[i][0] + (1 - kxscale) * xscale;
        masbody[i][1] = kyscale * masbody[i][1] + (1 - kyscale) * yscale;

        masleye[i][0] = kxscale * masleye[i][0] + (1 - kxscale) * xscale;
        masleye[i][1] = kyscale * masleye[i][1] + (1 - kyscale) * yscale;

        masreye[i][0] = kxscale * masreye[i][0] + (1 - kxscale) * xscale;
        masreye[i][1] = kyscale * masreye[i][1] + (1 - kyscale) * yscale;
    }
    for (int j = 0; j < N / 2; j++)
    {
        massmile[j][0] = kxscale * massmile[j][0] + (1 - kxscale) * xscale;
        massmile[j][1] = kyscale * massmile[j][1] + (1 - kyscale) * yscale;
    }
}

void rotatedots(double xrotate, double yrotate, double angle)
{
    double reserv;
    for (int i = 0; i < 21; i++)
    {
        reserv = masx[i];
        masx[i] = xrotate + (masx[i] - xrotate) * cos(angle * pi / 180) + (masy[i] - yrotate) * sin(angle * pi / 180);
        masy[i] = yrotate - (reserv - xrotate) * sin(angle * pi /180) + (masy[i] - yrotate) * cos(angle * pi / 180);
    }
    for (int i = 0; i < N; i++)
    {
        reserv = mashead[i][0];
        mashead[i][0] = xrotate + (mashead[i][0] - xrotate) * cos(angle * pi / 180) + (mashead[i][1] - yrotate) * sin(angle * pi / 180);
        mashead[i][1] = yrotate - (reserv - xrotate) * sin(angle * pi /180) + (mashead[i][1] - yrotate) * cos(angle * pi / 180);

        reserv = masbody[i][0];
        masbody[i][0] = xrotate + (masbody[i][0] - xrotate) * cos(angle * pi / 180) + (masbody[i][1] - yrotate) * sin(angle * pi / 180);
        masbody[i][1] = yrotate - (reserv - xrotate) * sin(angle * pi /180) + (masbody[i][1] - yrotate) * cos(angle * pi / 180);

        reserv = masleye[i][0];
        masleye[i][0] = xrotate + (masleye[i][0] - xrotate) * cos(angle * pi / 180) + (masleye[i][1] - yrotate) * sin(angle * pi / 180);
        masleye[i][1] = yrotate - (reserv - xrotate) * sin(angle * pi /180) + (masleye[i][1] - yrotate) * cos(angle * pi / 180);

        reserv = masreye[i][0];
        masreye[i][0] = xrotate + (masreye[i][0] - xrotate) * cos(angle * pi / 180) + (masreye[i][1] - yrotate) * sin(angle * pi / 180);
        masreye[i][1] = yrotate - (reserv - xrotate) * sin(angle * pi /180) + (masreye[i][1] - yrotate) * cos(angle * pi / 180);
    }
    for (int j = 0; j < N / 2; j++)
    {
        reserv = massmile[j][0];
        massmile[j][0] = xrotate + (massmile[j][0] - xrotate) * cos(angle * pi / 180) + (massmile[j][1] - yrotate) * sin(angle * pi / 180);
        massmile[j][1] = yrotate - (reserv - xrotate) * sin(angle * pi /180) + (massmile[j][1] - yrotate) * cos(angle * pi / 180);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    defaultdots();
    // Создаем виджет
    wgt = new QPaintWidget(this);
    // И кладём его в лайаут
    ui->verticalLayout->addWidget(wgt);
}

MainWindow::~MainWindow()
{
    // Подчищаем
    wgt->deleteLater();
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_Resetbutton_clicked()
{
    delete wgt;
    defaultdots();
    wgt = new QPaintWidget(this);
    ui->verticalLayout->addWidget(wgt);
}

void MainWindow::on_Movebutton_clicked()
{

    QString xmovestr = ui->xmove->text();
    dx = xmovestr.toFloat(&flag);
    QString ymovestr = ui->ymove->text();
    dy = ymovestr.toFloat(&flag1);
    if (!flag || !flag1)
        QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод координат переноса");
    else
    {
        lastact = 'm';
        movedots(dx, dy);
        delete wgt;
        wgt = new QPaintWidget(this);
        ui->verticalLayout->addWidget(wgt);
    }

}

void MainWindow::on_Scalebutton_clicked()
{    
    QString xscalestr = ui->xscale->text();
    xscale = xscalestr.toFloat(&flag);

    QString yscalestr = ui->yscale->text();
    yscale = yscalestr.toFloat(&flag1);

    QString kxscalestr = ui->kxscale->text();
    kxscale = kxscalestr.toFloat(&flag2);

    QString kyscalestr = ui->kyscale->text();
    kyscale = kyscalestr.toFloat(&flag3);

    if (!flag || !flag1 || !flag2 || !flag3)
    {
        QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод данных для масштабирования");
    }
    else
    {
        lastact = 's';
        scaledots(xscale, yscale, kxscale, kyscale);
        dotpos[0] = xscale - 2;
        dotpos[1] = yscale - 2;
        delete wgt;
        wgt = new QPaintWidget(this);
        ui->verticalLayout->addWidget(wgt);
    }
}

void MainWindow::on_Translatebutton_clicked()
{

    QString xrotatestr = ui->xrotate->text();
    xrotate = xrotatestr.toFloat(&flag);

    QString yrotatestr = ui->yrotate->text();
    yrotate = yrotatestr.toFloat(&flag1);

    QString rotateanglestr = ui->rotateangle->text();
    angle = rotateanglestr.toFloat(&flag2);

    if (!flag || !flag1 || !flag2)
    {
        QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод данных для поворота");
    }
    else
    {
        lastact = 'r';
        rotatedots(xrotate, yrotate, angle);
        dotpos[0] = xrotate - 2;
        dotpos[1] = yrotate - 2;
        delete wgt;
        wgt = new QPaintWidget(this);
        ui->verticalLayout->addWidget(wgt);
    }
}

void MainWindow::on_Undobutton_clicked()
{
    if (lastact == 'm')
    {
        movedots(-dx, -dy);
        delete wgt;
        wgt = new QPaintWidget(this);
        ui->verticalLayout->addWidget(wgt);
    }
    else if (lastact == 's')
    {
        scaledots(xscale, yscale, 1 / kxscale, 1 / kyscale);
        delete wgt;
        wgt = new QPaintWidget(this);
        ui->verticalLayout->addWidget(wgt);
    }
    else if (lastact == 'r')
    {
        rotatedots(xrotate, yrotate, -angle);
        delete wgt;
        wgt = new QPaintWidget(this);
        ui->verticalLayout->addWidget(wgt);
    }
    lastact = '0';
}
