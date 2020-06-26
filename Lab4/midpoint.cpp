#include "math.h"
#include "graphics.h"
#include "plot.h"
#include "QDebug"

void midpoint(double xc, double yc, double r, graphics_t &graphics)
{
    int x = 0;
    int y = r;
    int p = 5/4 - r;
    while (x <= y)
    {
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);

        plot(xc + y, yc + x, graphics);
        plot(xc - y, yc - x, graphics);
        plot(xc + y, yc - x, graphics);
        plot(xc - y, yc + x, graphics);
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void midpoint_ellipse(double xc, double yc, int ra, int rb, graphics_t &graphics)
{
    int rba = (int)round(ra * ra / sqrt(ra * ra + rb * rb));
    int x = 0, y = rb;
    int df = 0;
    int f = (int)(rb * rb - ra * ra * y + 0.25 * ra * ra + 0.5);

    int aa = 2 * ra * ra;
    int bb = 2 * rb * rb;

    int delta = - aa * y;
    for (x = 0; x <= rba; x++)
    {
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);

        if (f >= 0)
        {
            y -= 1;
            delta += aa;
            f += delta;
        }
        df += bb;
        f += df + rb * rb;
    }
    delta = bb * x;
    f += (int)(-rb * rb * (x + 0.75) - ra * ra * (y - 0.75));
    df = -aa * y;
    for (; y >= 0; y--)
    {
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);

        if (f < 0)
        {
            x += 1;
            delta += bb;
            f += delta;
        }
        df += aa;
        f += df + ra * ra;
    }
}
