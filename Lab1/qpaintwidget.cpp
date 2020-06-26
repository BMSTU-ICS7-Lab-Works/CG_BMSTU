#include "qpaintwidget.h"
#include <math.h>

#include <QPainter>
#include <QRectF>
#include <QDebug>

extern double xr1res, yr1res;
extern double xr2res, yr2res;

extern double xkas1res, ykas1res;

extern double xkas2res, ykas2res;

extern double rad1res, rad2res;
extern double xmin, xmax, ymin, ymax;

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
}

void QPaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this); // Создаём новый объект рисовальщика
    p.setPen(QPen(Qt::red, (xmax - xmin) / 150,Qt::SolidLine)); // Настройки рисования
    p.setWindow(xmin - 50, ymin - 50, xmax - xmin + 100, ymax - ymin + 100);

    p.drawEllipse(xr1res - rad1res, yr1res - rad1res, 2 * rad1res, 2 * rad1res);
    p.drawEllipse(xr2res - rad2res, yr2res - rad2res, 2 * rad2res, 2 * rad2res);

    p.drawLine(xr1res, yr1res, xr2res, yr2res);
    p.drawLine(xkas1res, ykas1res, xkas2res, ykas2res);
    p.drawLine(xkas1res, ykas1res, xr1res, yr1res);
    p.drawLine(xkas2res, ykas2res, xr2res, yr2res);

    if (rad1res)
    {
        //p.pixelSize(33);
        p.drawText((int)xr1res + 5, (int)yr1res - 5,
                   "("+QString::number(floor(xr1res * 100 ) / 100)+"; "+QString::number(floor(yr1res * 100 ) / 100)+")");
        p.drawText((int)xr2res + 5, (int)yr2res - 5,
                   "("+QString::number(floor(xr2res * 100 ) / 100)+"; "+QString::number(floor(yr2res * 100 ) / 100)+")");
        p.drawText((int)xkas1res + 5, (int)ykas1res - 5,
                   "("+QString::number(floor(xkas1res * 100 ) / 100)+"; "+QString::number(floor(ykas1res * 100 ) / 100)+")");
        p.drawText((int)xkas2res + 5, (int)ykas2res - 5,
                   "("+QString::number(floor(xkas2res * 100 ) / 100)+"; "+QString::number(floor(ykas2res * 100 ) / 100)+")");
    }
}
