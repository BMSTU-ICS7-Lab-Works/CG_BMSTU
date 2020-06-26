#include "math.h"
#include "graphics.h"
#include "plot.h"
#include "QDebug"

void canonic(double xc, double yc, double r, graphics_t &graphics)
{
    int x = 0, y;
    for (x = 0; x <= r / sqrt(2); x++)
    {
        y = sqrt(r * r - x * x);
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);

        plot(xc + y, yc + x, graphics);
        plot(xc - y, yc - x, graphics);
        plot(xc + y, yc - x, graphics);
        plot(xc - y, yc + x, graphics);
    }
}

void canonic_ellipse(double xc, double yc, int ra, int rb, graphics_t &graphics)
{
    int rba = (int)round(ra * ra / sqrt(ra * ra + rb * rb));
    int x = 0, y = 0;
    double m = (double) rb / ra;
    for (x = 0; x <= rba; x++)
    {
        y = (int)round(sqrt(ra * ra - x * x) * m);
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);
    }
    rba = (int)round(rb * rb / sqrt(ra * ra + rb * rb));
    m = 1 / m;
    for (y = 0; y <= rba; y++)
    {
        x = (int)round(sqrt(rb * rb - y * y) * m);
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);
    }
}
