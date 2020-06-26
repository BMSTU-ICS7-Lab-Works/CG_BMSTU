#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <algorithm>
#include <math.h>
#include "list.h"

int worked = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    closed(false),
    fillColor(defaultFillColor),
    n_edges(0),start_point(0)
{
    ui->setupUi(this);

    pixmap = QPixmap(ui->drawLabel->width(), ui->drawLabel->height());
    image = QImage(ui->drawLabel->width(), ui->drawLabel->height(), QImage::Format_RGB32);
    ui->drawLabel->setPixmapPointer(pixmap);

    clearImage();
    colorLabel();

    Q_ASSERT(defaultBoundColor != defaultFillColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    const int x = event->x() - ui->drawLabel->x();
    const int y = event->y() - ui->drawLabel->y();
    if (x < 0 || y < 0 || x >= pixmap.width() || y >= pixmap.height())
        return;

    DrawType drawType = DrawType::none;
    switch (QApplication::keyboardModifiers()) {
    case Qt::ShiftModifier:
        drawType = DrawType::horizontal;
        break;
    case Qt::ControlModifier:
        drawType = DrawType::vertical;
        break;
    case Qt::ShiftModifier | Qt::ControlModifier:
        drawType = DrawType::diagonal;
        break;
    default:
        break;
    }

    addPoint(QPoint(x, y), drawType);
}

void MainWindow::on_addPointPushButton_clicked()
{
    const int x = ui->xSpinBox->text().toInt();
    const int y = ui->ySpinBox->text().toInt();
    addPoint(QPoint(x, y), DrawType::none);
}

void MainWindow::on_closePushButton_clicked()
{
    if (closed) {
        QMessageBox::critical(this, "Error", "Already closed");
        return;
    }

    if (n_edges < 2) {
        QMessageBox::critical(this, "Error", "Need at least 2 edges");
        return;
    }

    addEdge(QLine(points[points.size() - 1], points[start_point]));
    closed = true;
    n_edges = 0;
}

int sgn(int val)
{
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

void MainWindow::on_fillPushButton_clicked()
{
    if (!closed) {
        QMessageBox::critical(this, "Error", "Figure is not closed");
        return;
    }
    displayImage();

    QList<int> bufx;

    QPainter painter(&pixmap);
    painter.setPen(fillColor);

    for (int i = 719; i >= 0; i--)
    {
        struct list *node = intersections[i];
        if (node != NULL)
        {
            while(node != NULL)
            {
                if (node->dy > 0)
                {
                    if (i - 1 >= 0)
                    {
                        if (intersections[i - 1] == NULL)
                        {
                            intersections[i - 1] = init(node->x + node->dx, node->dx, node->dy - 1);
                        }
                        else
                        {
                            addelem(intersections[i - 1], node->x + node->dx, node->dx, node->dy - 1);
                        }
                    }
                    bufx.append(node->x);
                }
                else
                {
                    //delete_edge_from_cap(intersection[i]);
                }
                node = node->ptr;
            }
            std::sort(bufx.begin(), bufx.end());
            int y = i;
            for (int j = 0; j < bufx.size(); j += 2)
                for (int x = (int)round(bufx[j]); x < ceil(bufx[j + 1]); x++)
                {
                    painter.drawPoint(x, y);
                }
            if (ui->delayCheckBox->isChecked())
            {
                displayImage();
                delay(ui->delaySpinBox->value());
            }
            bufx.clear();
        }

    }
    displayImage();
}

void MainWindow::on_clearPushButton_clicked()
{
    clearImage();
    closed = false;
    points.clear();
    edges.clear();
    if (worked == 1)
    {
        for (int i = 0; i < 720; i++)
        {
            if (intersections[i])
                free(intersections[i]);
        }
    }
    worked = 0;
    start_point = 0;
    for (int i = 0 ; i < 720; i++)
    {
        intersections[i] = NULL;
    }
    //intersections.clear();
    fillColor = defaultFillColor;
    colorLabel();
    n_edges = 0;
    ui->tableWidget->clearContents();
    ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());
}

void MainWindow::on_setColorPushButton_clicked()
{
    fillColor = QColorDialog::getColor(fillColor, this, "Pick a color", QColorDialog::DontUseNativeDialog);
    if (fillColor == defaultBoundColor)
        fillColor = defaultFillColor;
    colorLabel();
}

void MainWindow::addPoint(const QPoint &point, DrawType drawType)
{
    const int n = points.size();
    points.push_back(point);
    ui->tableWidget->insertRow(n);

    if (n && !closed)
        switch (drawType) {
        case DrawType::horizontal:
            points[n].setY(points[n - 1].y());
            break;
        case DrawType::vertical:
            points[n].setX(points[n - 1].x());
            break;
        case DrawType::diagonal: {
            const int dx = points[n].x() - points[n - 1].x();
            const int dy = points[n].y() - points[n - 1].y();
            if (dx * dy >= 0) {
                const int d = (dx + dy) / 2;
                points[n].setX(points[n - 1].x() + d);
                points[n].setY(points[n - 1].y() + d);
            }
            else {
                const int d = (dx - dy) / 2;
                points[n].setX(points[n - 1].x() + d);
                points[n].setY(points[n - 1].y() - d);
            }
        }
        case DrawType::none:
        default:
            break;
        }

    ui->tableWidget->setItem(n, 0, new QTableWidgetItem(QString::number(points[n].x())));
    ui->tableWidget->setItem(n, 1, new QTableWidgetItem(QString::number(points[n].y())));
    if (closed)
    {
        start_point = n;
        closed = false;
    }
    else if (n) {
        addEdge(QLine(points[closed ? 0 : n - 1], points[n]));
        closed = false;
    }
}

void MainWindow::addEdge(const QLine &edge)
{
    edges.push_back(edge);

    ++n_edges;
    /*
    for (int i = 0; i < n_edges; i++)
    {
        qDebug() << "edge px = " << edges[i].p1().x() << " py = " << edges[i].p1().y();
        qDebug() << "edge2 px = " << edges[i].p2().x() << " py2 = " << edges[i].p2().y();
    }
*/
    add_to_ygroup(edge);

    displayImage();
}

void MainWindow::add_to_ygroup(const QLine &edge)
{

    const int deltaX = edge.p2().x() - edge.p1().x();
    const int deltaY = edge.p2().y() - edge.p1().y();

    QPainter painter(&pixmap);
    painter.setPen(defaultBoundColor);

    const bool horizontal = edge.p1().y() == edge.p2().y();
    if (horizontal && edge.p1().x() == edge.p1().y())
    {
        painter.drawPoint(edge.p1());
        return;
    }
    int ymax;
    float x;
    float dx;
    if (edge.p2().y() > edge.p1().y())
    {
        ymax = edge.p2().y();
        x = edge.p2().x();
    }
    else
    {
        ymax = edge.p1().y();
        x = edge.p1().x();
    }
    dx = (float) deltaX / deltaY;
    dx *= -1;

    painter.drawLine(edge.p1().x(), edge.p1().y(), edge.p2().x(), edge.p2().y());
    if (!horizontal)
    {
        if (intersections[ymax] == NULL)
        {
            intersections[ymax] = init(x, dx, abs(deltaY));
        }
        else
        {
            addelem(intersections[ymax], x, dx, abs(deltaY));
        }
    }
}

void MainWindow::delay(int times)
{
    for (int i = 0; i < times; ++i) {
        repaint();
        resize(width(), height());
    }
}

void MainWindow::clearImage()
{
    pixmap.fill();
    displayImage();
}

void MainWindow::displayImage()
{
    ui->drawLabel->update();
    image = pixmap.toImage();
}

void MainWindow::colorLabel()
{
    QPalette palette = ui->colorLabel->palette();
    palette.setColor(ui->colorLabel->backgroundRole(), fillColor);
    ui->colorLabel->setAutoFillBackground(true);
    ui->colorLabel->setPalette(palette);
}
