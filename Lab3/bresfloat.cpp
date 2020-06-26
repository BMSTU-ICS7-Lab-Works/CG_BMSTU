#include <math.h>
#include "graphics.h"

int sign(int x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

void BresFloat(double xstart, double ystart, double xend, double yend, graphics_t &graphics)
{
    double deltax = xend - xstart;
    double deltay = yend - ystart;
    if ((deltax < EPS) && (deltay < EPS))
    {
        graphics.scene->addLine(round(xstart), round(ystart), round(xstart), round(ystart), graphics.pen);
        return;
    }
    int sx = sign(deltax);
    int sy = sign(deltay);
    deltax = fabs(deltax);
    deltay = fabs(deltay);
    int exch;
    double deltaerr = deltay / deltax;
    if (deltaerr > 1)
    {
        double tmp = deltax;
        deltax = deltay;
        deltay = tmp;
        deltaerr = 1 / deltaerr;
        exch = 1;
    }
    else
        exch = 0;
    double err = deltaerr - 0.5;
    double x = xstart;
    double y = ystart;
    for (int i = 0; i <= deltax; i++)
    {
        graphics.scene->addLine(x, y, x, y, graphics.pen);
        if (err >= 0)
        {
            if (exch == 1)
            {
                x += sx;
            }
            else
                y += sy;
            err -= 1;
        }
        if (exch == 1)
            y += sy;
        else
            x += sx;
        err += deltaerr;
    }
}
