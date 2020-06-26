#include "mainwindow.h"
#include "ui_mainwindow.h"

graphics_t graphics;
//graphics_t tmp_graphics;
double xc, yc;
double rad;
double max_time;
QVector<double> radius, time_c, time_p, time_b, time_m;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphics.scene = new QGraphicsScene(ui->graphicsView);
    graphics.scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    //Начальные параметры линии
    graphics.pen.setColor(BLACK);

    //Начальные параметры фоны
    graphics.bg = WHITE;
    graphics.scene->setBackgroundBrush(graphics.bg);

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
    ui->label_line->setText("Цвет рисования(текущий цвет-черный)");
    graphics.pen.setColor(BLACK);
}

void MainWindow::on_ButtonWhite_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-белый)");
    graphics.pen.setColor(WHITE);
}

void MainWindow::on_ButtonYellow_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-желтый)");
    graphics.pen.setColor(YELLOW);
}

void MainWindow::on_ButtonRed_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-красный)");
    graphics.pen.setColor(RED);
}

void MainWindow::on_ButtonOrange_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-оранжевый)");
    graphics.pen.setColor(ORANGE);
}

void MainWindow::on_ButtonPurple_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-фиолетовый)");
    graphics.pen.setColor(PURPLE);
}

void MainWindow::on_ButtonBlue_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-голубой)");
    graphics.pen.setColor(BLUE);
}

void MainWindow::on_ButtonGreen_clicked()
{
    ui->label_line->setText("Цвет рисования(текущий цвет-зеленый)");
    graphics.pen.setColor(GREEN);
}

void MainWindow::on_ClearButton_clicked()
{
    graphics.scene->clear();
}

void MainWindow::on_DrawButton_clicked()
{
    xc = ui->Xc->text().toDouble();
    yc = ui->Yc->text().toDouble();
    rad = ui->Rad->text().toDouble();

    if (ui->ButtonBA->isChecked())
    {
        graphics.scene->addEllipse(xc - rad, yc - rad, rad * 2, rad * 2, graphics.pen);
    }
    else if (ui->ButtonBR->isChecked())
    {
        Bresenham(xc, yc, rad, graphics);
    }
    else if (ui->ButtonMP->isChecked())
    {
        midpoint(xc, yc, rad, graphics);
    }
    else if (ui->ButtonPA->isChecked())
    {
        parametric(xc, yc, rad, graphics);
    }
    else if (ui->ButtonCA->isChecked())
    {
        canonic(xc, yc, rad, graphics);
    }
    else
    {
        QMessageBox::critical(NULL, "ERROR", "Не выбран алгоритм");
    }
}

void MainWindow::on_DrawEllipse_clicked()
{
    double xc = ui->XcE->text().toDouble();
    double yc = ui->YcE->text().toDouble();
    double ra = ui->Ra->text().toDouble();
    double rb = ui->Rb->text().toDouble();

    if (ui->ButtonBA->isChecked())
    {
        graphics.scene->addEllipse(xc - ra, yc - rb, ra * 2, rb * 2, graphics.pen);
    }
    else if (ui->ButtonBR->isChecked())
    {
        Bresenham_Ellipse(xc, yc, ra, rb, graphics);
    }
    else if (ui->ButtonMP->isChecked())
    {
        midpoint_ellipse(xc, yc, ra, rb, graphics);
    }
    else if (ui->ButtonPA->isChecked())
    {
        parametric_ellipse(xc, yc, ra, rb, graphics);
    }
    else if (ui->ButtonCA->isChecked())
    {
        canonic_ellipse(xc, yc, ra, rb, graphics);
    }
    else
    {
        QMessageBox::critical(NULL, "ERROR", "Не выбран алгоритм");
    }
}

void analyze(int xc, int yc, int beg, int end, int step, int circlenum, \
             void(*algorithm)(double xc, double yc, double r, graphics_t &graphics),\
             graphics_t &graphics, int alg)
{
    if (alg == 0)
    {
        for (int i = beg; i <= end; i += step)
        {
            algorithm(xc, yc, i, graphics);
        }
    }
    else if (alg == 1)
    {
        for (int i = beg; i <= end; i += (end - beg) / step)
        {
            algorithm(xc, yc, i, graphics);
        }
    }
    else if (alg == 2)
    {
        int count = 0;
        int curr = step;
        while (count < circlenum)
        {
            algorithm(xc, yc, step, graphics);
            curr += step;
            count++;
        }
    }

}

void MainWindow::on_AnalyzeButton_clicked()
{
    int xc = ui->Xc_2->text().toDouble();
    int yc = ui->Yc_2->text().toDouble();
    int beg = ui->RBeg->text().toDouble();
    int end = ui->REnd->text().toDouble();
    int step = ui->RStep->text().toDouble();
    int circlenum = ui->Circlenum->text().toDouble();
    int alg = -1;
    if (ui->RBeg->text() != "" && ui->REnd->text() != "" && ui->RStep->text() != "")
    {
        alg = 0;
    }
    else if (ui->RBeg->text() != "" && ui->REnd->text() != "" && ui->Circlenum->text() != "")
    {
        alg = 1;
    }
    else if (ui->RBeg->text() != "" && ui->Circlenum->text() != "" && ui->RStep->text() != "")
    {
        alg = 2;
    }
    else
    {
        QMessageBox::critical(NULL, "ERROR", "Выбрано больше либо меньше трех пунктов меню");
    }
    if (ui->ButtonBA->isChecked())
    {
        //analyze(xc, yc, beg, end, step, circlenum, , graphics);
    }
    else if (ui->ButtonBR->isChecked())
    {
        analyze(xc, yc, beg, end, step, circlenum, Bresenham, graphics, alg);
    }
    else if (ui->ButtonMP->isChecked())
    {
        analyze(xc, yc, beg, end, step, circlenum, midpoint, graphics, alg);
    }
    else if (ui->ButtonPA->isChecked())
    {
        analyze(xc, yc, beg, end, step, circlenum, parametric, graphics, alg);
    }
    else if (ui->ButtonCA->isChecked())
    {
        analyze(xc, yc, beg, end, step, circlenum, canonic, graphics, alg);
    }
    else
    {
        QMessageBox::critical(NULL, "ERROR", "Не выбран алгоритм");
    }

}

void calc_time()
{
    radius.clear();
    time_c.clear();
    time_p.clear();
    time_b.clear();
    time_m.clear();
    double x = 250;
    double y = 250;
    double r = 0;
    radius.append(r);
    time_c.append(0);
    time_p.append(0);
    time_b.append(0);
    time_m.append(0);
    time_t start, end;
    double time_work;
    for (int i = 100; i <= 1000; i += 100)
    {
        radius.append(r + i);

        //tmp_graphics.scene->clear();
        start = clock();
        for (int j = 0; j < 3; j++)
        {
            canonic(x, y, r + i, graphics);
        }
        end = clock();
        time_work = ((double)(end - start) / CLOCKS_PER_SEC);
        time_work /= 3;
        time_c.append(time_work);

       // tmp_graphics.scene->clear();
        start = clock();
        for (int j = 0; j < 3; j++)
        {
            parametric(x, y, r + i, graphics);
        }
        end = clock();
        time_work = ((double)(end - start) / CLOCKS_PER_SEC);
        time_work /= 3;
        time_p.append(time_work);

        //tmp_graphics.scene->clear();
        start = clock();
        for (int j = 0; j < 3; j++)
        {
            Bresenham(x, y, r + i, graphics);
        }
        end = clock();
        time_work = ((double)(end - start) / CLOCKS_PER_SEC);
        time_work /= 3;
        time_b.append(time_work);

        //tmp_graphics.scene->clear();
        start = clock();
        for (int j = 0; j < 3; j++)
        {
            midpoint(x, y, r + i, graphics);
        }
        end = clock();
        time_work = ((double)(end - start) / CLOCKS_PER_SEC);
        time_work /= 3;
        time_m.append(time_work);
    }
    double tmp_time = time_p.last();
    max_time = time_c.last();
    if (tmp_time > max_time)
        max_time = tmp_time;
    tmp_time = time_b.last();
    if (tmp_time > max_time)
        max_time = tmp_time;
    tmp_time = time_m.last();
    if (tmp_time > max_time)
        max_time = tmp_time;

}

void MainWindow::on_AnalyzeEffButton_clicked()
{
    calc_time();
    dialog = new Dialog(this);
    QCustomPlot *customPlot = new QCustomPlot();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(customPlot);
    dialog->setLayout(layout);
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setName("Каноническое ур.");

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::green));
    customPlot->graph(1)->setName("Параметрическое ур.");

    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setName("Алгоритм Брезенхема");

    customPlot->addGraph();
    customPlot->graph(3)->setPen(QPen(Qt::yellow));
    customPlot->graph(3)->setName("Алгоритм средней точки");

    customPlot->graph(0)->setData(radius, time_c);
    customPlot->graph(1)->setData(radius, time_p);
    customPlot->graph(2)->setData(radius, time_b);
    customPlot->graph(3)->setData(radius, time_m);

    customPlot->xAxis->setLabel("Радиус");
    customPlot->yAxis->setLabel("Время работы, сек");
    customPlot->xAxis->setRange(0, 1000);
    customPlot->yAxis->setRange(0, max_time);

    customPlot->legend->setVisible(true);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,150)));
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    //thirdDialog->resize(420, 300);
    dialog->show();
}

void MainWindow::on_EllSpectre_clicked()
{

}
