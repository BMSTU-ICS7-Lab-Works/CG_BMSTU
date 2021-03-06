#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QtDebug>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pixmap = QPixmap(ui->drawLabel->width(), ui->drawLabel->height());
    ui->drawLabel->setPixmapPointer(pixmap);

    on_clearAllPushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPolygonVertexPushButton_clicked()
{
    const int x = ui->xPolygonSpinBox->value();
    const int y = ui->yPolygonSpinBox->value();

    addFigureVertex(polygonVertices, polygonClosed, QPoint(x, y));
}

void MainWindow::on_addClipperVertexPushButton_clicked()
{
    const int x = ui->xClipperSpinBox->value();
    const int y = ui->yClipperSpinBox->value();

    addFigureVertex(clipperVertices, clipperClosed, QPoint(x, y));
}

void MainWindow::on_setPolygonColorPushButton_clicked()
{
    setColor(polygonColor, "Pick a polygon's color", ui->polygonColorLabel);
}

void MainWindow::on_setClipperColorPushButton_clicked()
{
    setColor(clipperColor, "Pick a clipper's color", ui->clipperColorLabel);
}

void MainWindow::on_setClippedLineColorPushButton_clicked()
{
    setColor(clippedLineColor, "Pick a clipped line's color", ui->clippedLineColorLabel);
}

void MainWindow::on_closePolygonPushButton_clicked()
{
    closeFigure(polygonVertices.size(), polygonClosed);
}

void MainWindow::on_closeClipperPushButton_clicked()
{
    closeFigure(clipperVertices.size(), clipperClosed);
}

QVector<QLine> verticesToEdges(const QVector<QPoint>& vertices)
{
    QVector<QLine> edges;

    for (int i = 1; i < vertices.size(); ++i)
        edges.push_back(QLine(vertices[i - 1], vertices[i]));
    edges.push_back(QLine(vertices.back(), vertices.front()));

    return edges;
}

void MainWindow::on_clipPushButton_clicked()
{
    if (!polygonClosed) {
        QMessageBox::critical(this, "Error", "Polygon must be closed");
        return;
    }

    if (!clipperClosed) {
        QMessageBox::critical(this, "Error", "Clipper must be closed");
        return;
    }

    int direction = checkClipper();
    if (!direction) {
        QMessageBox::critical(this, "Error", "???????????????????? ???????????? ???????? ????????????????");
        return;
    }

    QPainter painter(&pixmap);
    painter.setPen(QPen(clippedLineColor, 3));
    auto clipped = Hodgman(direction);

    for (int i = 1; i < clipped.size(); ++i)
        painter.drawLine(clipped[i - 1], clipped[i]);

    if (clipped.size() > 1)
        painter.drawLine(clipped.back(), clipped.front());

    ui->drawLabel->update();
}

void MainWindow::on_deletePolygonPushButton_clicked()
{
    deleteFigure(polygonVertices, polygonClosed);
}

void MainWindow::on_deleteClipperPushButton_clicked()
{
    deleteFigure(clipperVertices, clipperClosed);
}

void MainWindow::on_clearAllPushButton_clicked()
{
    on_deletePolygonPushButton_clicked();
    on_deleteClipperPushButton_clicked();

    setPolygonColor(Qt::red);
    setClipperColor(Qt::black);
    setClippedLineColor(Qt::blue);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x() - ui->drawLabel->x();
    int y = event->y() - ui->drawLabel->y();

    if (x < 0 || x >= ui->drawLabel->width() || y < 0 || y >= ui->drawLabel->height())
        return;

    switch (event->button()) {
    case Qt::LeftButton:
        if (!polygonVertices.empty()) {
            const int x1 = ui->xPolygonSpinBox->value();
            const int y1 = ui->yPolygonSpinBox->value();
            receiveKeyboardModifiers(x, y, x1, y1);
        }
        ui->xPolygonSpinBox->setValue(x);
        ui->yPolygonSpinBox->setValue(y);
        on_addPolygonVertexPushButton_clicked();
        break;
    case Qt::RightButton:
        if (!clipperVertices.empty()) {
            const int x1 = ui->xClipperSpinBox->value();
            const int y1 = ui->yClipperSpinBox->value();
            receiveKeyboardModifiers(x, y, x1, y1);
        }
        ui->xClipperSpinBox->setValue(x);
        ui->yClipperSpinBox->setValue(y);
        on_addClipperVertexPushButton_clicked();
        break;
    default:
        break;
    }
}

void MainWindow::receiveKeyboardModifiers(int &x, int &y, int x1, int y1)
{
    switch (QApplication::keyboardModifiers()) {
    case Qt::ShiftModifier: {
        y = y1;
        break;
    }
    case Qt::ControlModifier: {
        x = x1;
        break;
    }
    case Qt::ShiftModifier | Qt::ControlModifier: {
        const int dx = x - x1;
        const int dy = y - y1;
        if (dx * dy >= 0) {
            const int d = (dx + dy) / 2;
            x = x1 + d;
            y = y1 + d;
        }
        else {
            const int d = (dx - dy) / 2;
            x = x1 + d;
            y = y1 - d;
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::displayImage()
{
    pixmap.fill();

    QPainter painter(&pixmap);

    painter.setPen(clipperColor);
    for (int i = 1; i < clipperVertices.size(); ++i)
        painter.drawLine(clipperVertices[i - 1], clipperVertices[i]);
    if (clipperClosed)
        painter.drawLine(clipperVertices.back(), clipperVertices.front());

    painter.setPen(polygonColor);
    for (int i = 1; i < polygonVertices.size(); ++i)
        painter.drawLine(polygonVertices[i - 1], polygonVertices[i]);
    if (polygonClosed)
        painter.drawLine(polygonVertices.back(), polygonVertices.front());

    ui->drawLabel->update();
}

void MainWindow::setColor(QColor &color, const QString &msg, QLabel *label)
{
    color = QColorDialog::getColor(clipperColor, this, msg, QColorDialog::DontUseNativeDialog);
    colorLabel(color, label);
    displayImage();
}

void MainWindow::setPolygonColor(QColor color)
{
    polygonColor = color;
    colorLabel(polygonColor, ui->polygonColorLabel);
}

void MainWindow::setClipperColor(QColor color)
{
    clipperColor = color;
    colorLabel(clipperColor, ui->clipperColorLabel);
}

void MainWindow::setClippedLineColor(QColor color)
{
    clippedLineColor = color;
    colorLabel(clippedLineColor, ui->clippedLineColorLabel);
}

void MainWindow::colorLabel(QColor color, QLabel *label) {
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), color);
    label->setAutoFillBackground(true);
    label->setPalette(palette);
}

void MainWindow::addFigureVertex(QVector<QPoint> &figure_vertices, bool &figure_closed, const QPoint &vertex)
{
    if (figure_closed)
        deleteFigure(figure_vertices, figure_closed);

    figure_vertices.push_back(vertex);
    displayImage();
}

void MainWindow::closeFigure(int figure_vertices_size, bool &figure_closed)
{
    if (figure_closed) {
        QMessageBox::critical(this, "Error", "Already closed");
        return;
    }

    if (figure_vertices_size <= 2) {
        QMessageBox::critical(this, "Error", "Need at least 2 edges");
        return;
    }

    figure_closed = true;
    displayImage();
}

void MainWindow::deleteFigure(QVector<QPoint> &figure_vertices, bool &figure_closed)
{
    figure_vertices.clear();
    figure_closed = false;
    displayImage();
}

int sign(int x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

int product(const QPoint &a, const QPoint &b)
{
    return a.x() * b.y() - a.y() * b.x();
}

int direction(const QPoint &prev, const QPoint &curr, const QPoint &next)
{
    return sign(product(curr - prev, next - curr));
}

int MainWindow::checkClipper()
{
    int f = 1;

    QPoint prev_vertex = clipperVertices.back();
    QPoint curr_vertex = clipperVertices[0];
    QPoint next_vertex = clipperVertices[1];

    int prev_direction = direction(prev_vertex, curr_vertex, next_vertex);
    int curr_direction = 0;

    for (int i = 1; i < clipperVertices.size() && f; ++i) {
        prev_vertex = curr_vertex;
        curr_vertex = next_vertex;
        next_vertex = clipperVertices[(i + 1) % clipperVertices.size()];

        curr_direction = direction(prev_vertex, curr_vertex, next_vertex);

        if (curr_direction != prev_direction)
            f = 0;

        prev_direction = curr_direction;
    }

    return f * curr_direction;
}



int isVisible(QPoint &p, QPoint &p1, QPoint &p2)
{
    return sign(product(p - p1, p2 - p1));
}

bool checkIntersection(QPoint &sp, QPoint &ep, QPoint &p0, QPoint &p1)
{
    return isVisible(sp, p0, p1) * isVisible(ep, p0, p1) <= 0;
}

QPoint intersection(QPoint &p1, QPoint &p2, QPoint &cp1, QPoint &cp2) {
    int det = product(p2 - p1, cp1 - cp2);
    double t = (double)(product(cp1 - p1, cp1 - cp2)) / det;
    return p1 + (p2 - p1) * t;
}

QVector<QPoint> MainWindow::Hodgman(int direction)
{
    polygon = polygonVertices;
    clipper = clipperVertices;
    clipper.push_back(clipper.front());

    QPoint first, start, end;

    for (int i = 0; i < clipper.size() - 1; i++)
    {
        for (int j = 0; j < polygon.size(); j++)
        {
            end = polygon[j];
            if (j == 0)
                first = end;
            else if (checkIntersection(start, end, clipper[i], clipper[i + 1]))
                res.push_back(intersection(start, end, clipper[i], clipper[i + 1]));

            start = end;
            int vision = sign(product(start - clipper[i], clipper[i + 1] - clipper[i]));
            if (vision * direction < 0)
                res.push_back(start);
        }

        if (res.empty() == 0)
        {
            if (checkIntersection(start, first, clipper[i], clipper[i + 1]))
                res.push_back(intersection(start, first, clipper[i], clipper[i + 1]));
        }
        qDebug() << res << "\n";
        polygon = res;
        res.clear();
    }
    return polygon;
}

