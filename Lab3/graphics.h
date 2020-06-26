#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsScene>
#include <QPen>
#include <QColor>

#define EPS 0.000000001

typedef struct graphics
{
    QGraphicsScene *scene;
    QPen pen;
    QColor bg;
} graphics_t;

#endif // GRAPHICS_H

