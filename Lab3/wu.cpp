#include <math.h>
#include "graphics.h"


void draw_point(int steep, double x, double y, graphics_t &graphics)
{
    if (steep)
        graphics.scene->addLine(y, x, y, x, graphics.pen);
    else
        graphics.scene->addLine(x, y, x, y, graphics.pen);
}

void Wu(double xstart, double ystart, double xend, double yend, graphics_t &graphics)
{
    int steep;
    if (fabs(yend - ystart) > fabs(xend - xstart))
        steep = 1;
    if (steep)
    {
        double temp = xstart;
        xstart = ystart;
        ystart = temp;
        temp = xend;
        xend = yend;
        yend = temp;
    }
    if (xstart > xend)
    {
        double temp = xstart;
        xstart = xend;
        xend = temp;
       temp = ystart;
        ystart = yend;
        yend = temp;
    }
    int x0 = round(xstart);
    int y0 = round(ystart);
    int x1 = round(xend);
    int y1 = round(yend);

    double deltax = xend - xstart;
    double deltay = yend - ystart;

    draw_point(steep, x0, y0, graphics);
    draw_point(steep, x1, y1, graphics);

    double grad = deltay / deltax;
    double y = y0 + grad;

    QColor lncolor = graphics.pen.color();

    for (int x = x0 + 1; x <= x1 - 1; x++)
    {
        lncolor.setAlphaF(1 - (y - (int)y));
        graphics.pen.setColor(lncolor);
        draw_point(steep, x, (int)y, graphics);

        lncolor.setAlphaF(y - (int)y);
        graphics.pen.setColor(lncolor);
        draw_point(steep, x, (int)y + 1, graphics);

        y += grad;
    }
}
