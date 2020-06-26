#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <string>
#include <math.h>

bool flag;
const int N = 10000;
double masx1[N];
double masy1[N];
double masx2[N];
double masy2[N];

double xr1, yr1;
double xr2, yr2;
double rad1, rad2;

double rad1res, rad2res;

double xr1res, yr1res;
double xr2res, yr2res;

double a, b, c;
double kaslen;

double xkas1, ykas1;
double xkas1res, ykas1res;

double xkas2, ykas2;
double xkas2res, ykas2res;

double xmax, xmin;
double ymax, ymin;

double square = -1;
double squareres = -1;

int RowCount1 = 0;
int RowCount2 = 0;

double sqr(double x)
{
    return x * x;
}

void tangents(double x, double y, double r1, double r2)
{
    double r = r2 - r1;
    double z = sqr(x) + sqr(y);
    double d = z - sqr(r);
    d = sqrt(abs(d));
    a = (x * r + y * d) / z;
    b = (y * r - x * d) / z;
    c = r1;
    c -= a * xr1 + b * yr1;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Table1->setColumnCount(2);
    ui->Table2->setColumnCount(2);
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

void MainWindow::on_Createtable1_clicked()
{
   QString RowCountString = ui->Createtable1line->text();
   bool flag;
   RowCount1 = RowCountString.toInt(&flag);
   if (flag)
   {
       if (RowCount1 <= 0)
           QMessageBox::critical(this,"Ошибка ввода", "Кол-во точек не может быть отрицательным");
       else
           ui->Table1->setRowCount(RowCount1);
   }
   else
   {
       QMessageBox::critical(this,"Ошибка ввода", "Некорректный ввод кол-ва точек");
   }
}

void MainWindow::on_Createtable2_clicked()
{
    QString RowCountString = ui->Createtable2line->text();
    bool flag;
    RowCount2 = RowCountString.toInt(&flag);
    if (flag)
    {
        if (RowCount2 <= 0)
            QMessageBox::critical(this,"Ошибка ввода", "Кол-во точек не может быть отрицательным");
        else
            ui->Table2->setRowCount(RowCount2);
    }
    else
    {
        QMessageBox::critical(this,"Ошибка ввода", "Некорректный ввод кол-ва точек");
    }
}

void MainWindow::on_Calcbutton_clicked()
{
    RowCount1 = ui->Table1->rowCount();
    RowCount2 = ui->Table2->rowCount();
    qDebug() << "rowcount1 = " << RowCount1 << "rowcount2 = " << RowCount2;
    if (RowCount1 < 3 || RowCount2 < 3)
    {
        QMessageBox::critical(this,"Ошибка", "В таблице(ах) менее 3 точек");
        return;
    }
    square = -1;
    squareres = -1;
    for (int i = 0; i < RowCount1; i++)
    {
        //nullptr item c=sohuld be checked
        QString item_table = ui->Table1->item(i,0)->text();
        double item = item_table.toDouble(&flag);
        if (!flag)
        {
            QMessageBox::critical(this,"Ошибка ввода", "Некорректная(ые) или незаполненная(ые) координата(ы)");
            return;
        }
        masx1[i] = item;
        item_table = ui->Table1->item(i,1)->text();
        item = item_table.toDouble(&flag);
        if (!flag)
        {
            QMessageBox::critical(this,"Ошибка ввода", "Некорректная(ые) или незаполненная(ые) координата(ы)");
            return;
        }
        masy1[i] = item;
    }
    for (int i = 0; i < RowCount2; i++)
    {
        QString item_table = ui->Table2->item(i,0)->text();
        double item = item_table.toDouble(&flag);
        if (!flag)
        {
            QMessageBox::critical(this,"Ошибка ввода", "Некорректная(ые) или незаполненная(ые) координата(ы)");
            return;
        }
        masx2[i] = item;
        item_table = ui->Table2->item(i,1)->text();
        item = item_table.toDouble(&flag);
        if (!flag)
        {
            QMessageBox::critical(this,"Ошибка ввода", "Некорректная(ые) или незаполненная(ые) координата(ы)");
            return;
        }
        masy2[i] = item;
    }
    for (int i = 0; i < RowCount1 - 2; i++)
    {
        for (int j = 1; j < RowCount1 - 1; j++)
        {
            for (int k = 2; k < RowCount1; k++)
            {
                for (int l = 0; l < RowCount2 - 2; l++)
                {
                    for (int m = 1; m < RowCount2 - 1; m ++)
                    {
                        for (int n = 2; n < RowCount2; n++)
                        {
                            xr1 = -1.0/2 * (masy1[i] * (sqr(masx1[j]) + sqr(masy1[j])
                                                    - sqr(masx1[k]) - sqr(masy1[k])) +
                                          masy1[j] * (sqr(masx1[k]) + sqr(masy1[k])
                                                      - sqr(masx1[i]) - sqr(masy1[i])) +
                                          masy1[k] * (sqr(masx1[i]) + sqr(masy1[i])
                                                      - sqr(masx1[j]) - sqr(masy1[j]))) /
                                    (masx1[i] * (masy1[j] - masy1[k]) +
                                     masx1[j] * (masy1[k] - masy1[i]) +
                                     masx1[k] * (masy1[i] - masy1[j]));
                            yr1 = 1.0/2 * (masx1[i] * (sqr(masx1[j]) + sqr(masy1[j])
                                                     - sqr(masx1[k]) - sqr(masy1[k])) +
                                           masx1[j] * (sqr(masx1[k]) + sqr(masy1[k])
                                                       - sqr(masx1[i]) - sqr(masy1[i])) +
                                           masx1[k] * (sqr(masx1[i]) + sqr(masy1[i])
                                                       - sqr(masx1[j]) - sqr(masy1[j]))) /
                                     (masx1[i] * (masy1[j] - masy1[k]) +
                                      masx1[j] * (masy1[k] - masy1[i]) +
                                      masx1[k] * (masy1[i] - masy1[j]));

                            xr2 = -1.0/2 * (masy2[l] * (sqr(masx2[m]) + sqr(masy2[m])
                                                    - sqr(masx2[n]) - sqr(masy2[n])) +
                                          masy2[m] * (sqr(masx2[n]) + sqr(masy2[n])
                                                      - sqr(masx2[l]) - sqr(masy2[l])) +
                                          masy2[n] * (sqr(masx2[l]) + sqr(masy2[l])
                                                      - sqr(masx2[m]) - sqr(masy2[m]))) /
                                    (masx2[l] * (masy2[m] - masy2[n]) +
                                     masx2[m] * (masy2[n] - masy2[l]) +
                                     masx2[n] * (masy2[l] - masy2[m]));
                            yr2 = 1.0/2 * (masx2[l] * (sqr(masx2[m]) + sqr(masy2[m])
                                                     - sqr(masx2[n]) - sqr(masy2[n])) +
                                           masx2[m] * (sqr(masx2[n]) + sqr(masy2[n])
                                                       - sqr(masx2[l]) - sqr(masy2[l])) +
                                           masx2[n] * (sqr(masx2[l]) + sqr(masy2[l])
                                                       - sqr(masx2[m]) - sqr(masy2[m]))) /
                                     (masx2[l] * (masy2[m] - masy2[n]) +
                                      masx2[m] * (masy2[n] - masy2[l]) +
                                      masx2[n] * (masy2[l] - masy2[m]));
                            qDebug() << "xr1 = " << xr1 << "yr1 = " << yr1 << "xr2 = " << xr2 << "yr2 = " << yr2;

                            rad1 = sqrt(sqr(masx1[i] - xr1) + sqr(masy1[i] - yr1));
                            rad2 = sqrt(sqr(masx2[l] - xr2) + sqr(masy2[l] - yr2));

                            qDebug() << "rad1 = " << rad1 << "rad2 = " << rad2;
                            tangents(xr2 - xr1, yr2 - yr1, rad1, rad2);
                            qDebug() << "a = " << a << "b= " << b << "c = " << c;
                            xkas1 = (xr1 - a * c / sqr(b) - a * yr1 / b) / (1 + sqr(a) / sqr(b));
                            ykas1 = -(a * xkas1 + c) / b;

                            xkas2 = (xr2 - a * c / sqr(b) - a * yr2 / b) / (1 + sqr(a) / sqr(b));
                            ykas2 = -(a * xkas2 + c) / b;

                            qDebug() << "xkas1 = " << xkas1 << "ykas1 = " << ykas1;
                            qDebug() << "xkas2 = " << xkas2 << "ykas2 = " << ykas2;
                            kaslen = sqrt(sqr(xr1 - xr2) + sqr(yr1 - yr2));
                            square = (rad1 + rad2) * kaslen / 2;
                            qDebug() << "square = " << square;
                            if (square > squareres)
                            {
                                squareres = square;
                                xr1res = xr1;
                                yr1res = yr1;

                                xr2res = xr2;
                                yr2res = yr2;
                                xkas1res = xkas1;
                                ykas1res = ykas1;

                                xkas2res = xkas2;
                                ykas2res = ykas2;

                                rad1res = rad1;
                                rad2res = rad2;
                                if (xr1 - rad1 < xr2 - rad2)
                                {
                                    xmin = xr1 - rad1;
                                }
                                else
                                    xmin = xr2 - rad2;

                                if (xr1 + rad1 < xr2 + rad2)
                                {
                                    xmax = xr2 + rad2;
                                }
                                else
                                    xmax = xr1 + rad1;

                                if (yr1 - rad1 < yr2 - rad2)
                                {
                                    ymin = yr1 - rad1;
                                }
                                else
                                    ymin = yr2 - rad2;

                                if (yr1 + rad1 < yr2 + rad2)
                                {
                                    ymax = yr2 + rad2;
                                }
                                else
                                    ymax = yr1 + rad1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (squareres == -1 || squareres > 9999999999)
    {
        QMessageBox::critical(this,"Ошибка", "Решение не было найдено");
        return;
    }
    QString result = QString("Площадь полученного прямоугольника = %1\n"
                             "Радиус первой окржуности = %2\n"
                             "Радиус второй окружности = %3\n"
                             "Длина касательной = %4").arg(squareres).arg(rad1res).arg(rad2res).arg(kaslen);
    QMessageBox::information(this,"Подробная информация", result);
    delete wgt;
    wgt = new QPaintWidget(this);
    ui->verticalLayout->addWidget(wgt);
}

void MainWindow::on_Delbutton1_clicked()
{
    if (ui->Table1->rowCount() == 0)
    {
        QMessageBox::critical(this,"Ошибка", "Первая таблица пуста!");
        return;
    }
    QString point = ui->Delline1->text();
    int num_point=point.toInt(&flag);
    if (flag)
    {
        if ((num_point < 1) || (num_point > ui->Table1->rowCount()))
            QMessageBox::critical(this,"Ошибка ввода", "Некорректный ввод номера строки");
        else
            ui->Table1->removeRow(num_point - 1);
    }
    else
    {
        QMessageBox::critical(this,"Ошибка ввода", "Некорректный ввод номера точки");
    }
}

void MainWindow::on_Delbutton2_clicked()
{
    if (ui->Table2->rowCount() == 0)
    {
        QMessageBox::critical(this,"Ошибка", "Первая таблица пуста!");
        return;
    }
    QString point = ui->Delline2->text();
    int num_point=point.toInt(&flag);
    if (flag)
    {
        if ((num_point < 1) || (num_point > ui->Table2->rowCount()))
            QMessageBox::critical(this,"Ошибка ввода", "Некорректный ввод номера строки");
        else
            ui->Table2->removeRow(num_point - 1);
    }
    else
    {
        QMessageBox::critical(this,"Ошибка ввода", "Некорректный ввод номера точки");
    }
}

void MainWindow::on_Adddot1button_clicked()
{
    ui->Table1->setRowCount(ui->Table1->rowCount() + 1);
    QString str;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    str = ui->Dotx1line->text();
    str.toDouble(&flag);
    if (flag)
    {
        item1->setText(str);
        ui->Table1->setItem(ui->Table1->rowCount() - 1 , 0,item1);
        str = ui->Doty1line->text();
        str.toDouble(&flag);
        if (flag)
        {
            item2->setText(str);
            ui->Table1->setItem(ui->Table1->rowCount() - 1 , 1,item2);
        }
        else
        {
            ui->Table1->setRowCount(ui->Table1->rowCount() - 1);
            QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод точки");
        }
    }
    else
    {
        ui->Table1->setRowCount(ui->Table1->rowCount() - 1);
        QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод точки");
    }
}

void MainWindow::on_Adddot2button_clicked()
{
    ui->Table2->setRowCount(ui->Table2->rowCount() + 1);
    QString str;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    str = ui->Dotx2line->text();
    str.toDouble(&flag);
    if (flag)
    {
        item1->setText(str);
        ui->Table2->setItem(ui->Table2->rowCount() - 1 , 0,item1);
        str = ui->Doty2line->text();
        str.toDouble(&flag);
        if (flag)
        {
            item2->setText(str);
            ui->Table2->setItem(ui->Table2->rowCount() - 1 , 1,item2);
        }
        else
        {
            ui->Table2->setRowCount(ui->Table2->rowCount() - 1);
            QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод точки");
        }
    }
    else
    {
        ui->Table2->setRowCount(ui->Table2->rowCount() - 1);
        QMessageBox::critical(this, "Ошибка ввода", "Некорректный ввод точки");
    }
}


void MainWindow::on_Detailedbutton_clicked()
{
    if (squareres == -1 || squareres > 9999999999)
    {
        QMessageBox::critical(this,"Ошибка", "Решения еще нет");
        return;
    }
    QString result = QString("Площадь полученного прямоугольника = %1\n"
                             "Радиус первой окржуности = %2\n"
                             "Радиус второй окружности = %3\n"
                             "Длина касательной = %4").arg(squareres).arg(rad1res).arg(rad2res).arg(kaslen);
    QMessageBox::information(this,"Подробная информация", result);
}
