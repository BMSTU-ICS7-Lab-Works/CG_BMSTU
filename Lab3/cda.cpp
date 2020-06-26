#include <QDebug>
#include <math.h>
#include "graphics.h"

void cda(double xstart, double ystart, double xend, double yend, graphics_t &graphics)
{
    double px = fabs(xstart - xend);
    double py = fabs(ystart - yend);
    double steep;
    if ((px < EPS) && (py < EPS))
    {
        graphics.scene->addLine(round(xstart), round(ystart), round(xstart), round(ystart), graphics.pen);
        return;
    }
    if (px > py)
    {
        steep = px;
    }
    else
    {
        steep = py;
    }
    double sx = (xend - xstart) / steep;
    double sy = (yend - ystart) / steep;
    double x = xstart;
    double y = ystart;
    qDebug() << "xstart = " << xstart << "ystart = " << ystart;
    for (int i = 0; i <= steep; i++)
    {
        graphics.scene->addLine(x, y, x, y, graphics.pen);
        x += sx;
        y += sy;
    }
}

int cda_steps(double xstart, double ystart, double xend, double yend)
{
    double px = xend - xstart;
    double py = yend - ystart;
    double steep;
    int exch;
    if (fabs(px) >= fabs(py))
    {
        steep = fabs(px);
        exch = 0;
    }
    else
    {
        steep = fabs(py);
        exch = 1;
    }
    double sx = px / steep;
    double sy = py / steep;
    double x = xstart;
    double y = ystart;
    int cury = y;
    int curx = x;
    int curstep = 0;
    int maxstep = 0;
    for (int i = 0; i <= steep; i++)
    {
        //graphics.scene->addLine(x, y, x, y, graphics.pen);
        if (exch == 1)
        {
            if ((int)x != curx)
            {
                curstep = 1;
                curx = (int)x;
            }
            else
            {
                curstep += 1;
                if (curstep > maxstep)
                    maxstep = curstep;
            }
        }
        else
        {
            if ((int)y != cury)
            {
                curstep = 1;
                cury = (int)y;
            }
            else
            {
                curstep += 1;
                if (curstep > maxstep)
                    maxstep = curstep;
            }
        }
        x += sx;
        y += sy;

    }
    qDebug() << "maxstep = " << maxstep;
    return maxstep;
}
