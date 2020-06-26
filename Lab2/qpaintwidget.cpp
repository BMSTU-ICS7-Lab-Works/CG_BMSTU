#include "qpaintwidget.h"

#include <QPainter>
#include <QRectF>
#include <QDebug>

extern double masx[21];
extern double masy[21];
const long int N = 100000;

extern double masbody[N][2];
extern double massmile[N][2];
extern double mashead[N][2];
extern double masleye[N][2];
extern double masreye[N][2];

extern double dotpos[2];
extern double xmove;
extern double ymove;
extern int rotateangle;

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
}

void QPaintWidget::paintEvent(QPaintEvent *) {
    QPainter p(this); // Создаём новый объект рисовальщика
    p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
    p.translate(width() / 2, height() / 2);
    p.drawRect(dotpos[0], dotpos[1], 4, 4);
    p.setPen(QPen(Qt::blue,1,Qt::SolidLine)); // Настройки рисования

    //legs draw
    p.drawLine(masx[0], masy[0], masx[1], masy[1]);
    p.drawLine(masx[1], masy[1], masx[2], masy[2]);
    p.drawLine(masx[3], masy[3], masx[4], masy[4]);
    p.drawLine(masx[4], masy[4], masx[5], masy[5]);
    //right arm draw
    p.drawLine(masx[6], masy[6], masx[7], masy[7]);
    p.drawLine(masx[7], masy[7], masx[8], masy[8]);
    p.drawLine(masx[8], masy[8], masx[6], masy[6]);
    //left arm draw
    p.drawLine(masx[9], masy[9], masx[10], masy[10]);
    p.drawLine(masx[10], masy[10], masx[11], masy[11]);
    p.drawLine(masx[11], masy[11], masx[9], masy[9]);
    //left brow draw
    p.drawLine(masx[12], masy[12], masx[13], masy[13]);
    p.drawLine(masx[13], masy[13], masx[14], masy[14]);
    //right brow draw
    p.drawLine(masx[15], masy[15], masx[16], masy[16]);
    p.drawLine(masx[16], masy[16], masx[17], masy[17]);
    for (int i = 0; i < N; i ++)
    {

        p.drawPoint(masbody[i][0], masbody[i][1]);
        p.drawPoint(mashead[i][0], mashead[i][1]);
        p.drawPoint(massmile[i][0], massmile[i][1]);
        p.drawPoint(masleye[i][0], masleye[i][1]);
        p.drawPoint(masreye[i][0], masreye[i][1]);
    }
}
