#include <math.h>
#include "bresfloat.h"
#include "graphics.h"


void BresInt(double xstart, double ystart, double xend, double yend, graphics_t &graphics)
{
    int deltax = xend - xstart;
    int deltay = yend - ystart;
    int sx = sign(deltax);
    int sy = sign(deltay);
    deltax = abs(deltax);
    deltay = abs(deltay);
    int exch;
    if (deltay >= deltax)
    {
        int tmp = deltax;
        deltax = deltay;
        deltay = tmp;
        exch = 1;
    }
    else
        exch = 0;
    int err = 2 * deltay - deltax;
    int x = xstart;
    int y = ystart;
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
            err -= 2 * deltax;
        }
        if (exch == 1)
        {
            y += sy;
        }
        else
        {
            x += sx;
        }
        err = err + 2 * deltay;
    }
}
