#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGraphicsScene>
#include <QPen>
#include <QColor>

typedef struct graphics
{
    QGraphicsScene *scene;
    QPen pen;
    QColor bg;
} graphics_t;


#endif // GRAPHICS_H
