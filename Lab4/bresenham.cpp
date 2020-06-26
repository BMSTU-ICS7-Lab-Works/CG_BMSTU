#include "math.h"
#include "graphics.h"
#include "plot.h"
#include "QDebug"

void DiagStep(int &x, int &y, int &d)
{
    x++;
    y--;
    d += 2 * (x - y + 1);
}

void HorizStep(int &x, int &d)
{
    x++;
    d += 2 * x + 1;
}

void VertStep(int &y, int &d)
{
    y --;
    d += -2 * y + 1;
}

void Bresenham(double xc, double yc, double r, graphics_t &graphics)
{
    int x = 0, y = r;
    int d = 2 * (1 - r);
    int d1, d2;
    for (x = 0; x <= r / sqrt(2);)
    {
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);

        plot(xc + y, yc + x, graphics);
        plot(xc - y, yc - x, graphics);
        plot(xc + y, yc - x, graphics);
        plot(xc - y, yc + x, graphics);

        if (d == 0)
        {
            DiagStep(x, y, d);
        }
        else if (d < 0)
        {
            d1 = 2 * d + 2 * y - 1;
            if (d1 > 0)
                DiagStep(x, y, d);
            else
                HorizStep(x, d);
        }
        else
        {
            d2 = 2 * d - 2 * x - 1;
            if (d2 < 0)
                DiagStep(x, y, d);
            else
                VertStep(y, d);
        }
    }
}

void DiagStep_Ell(int &x, int &y, int &d, int ra, int aa, int rb, int bb)
{
    x++;
    y--;
    d += bb * x + rb * rb + ra * ra - aa * y;
}

void HorizStep_Ell(int &x, int &d, int rb, int bb)
{
    x++;
    d += bb * x + rb * rb;
}

void VertStep_Ell(int &y, int &d, int ra, int aa)
{
    y--;
    d += ra * ra - aa * y;
}

void Bresenham_Ellipse(int xc, int yc, int ra, int rb, graphics_t &graphics)
{
    int aa = 2 * ra * ra;
    int bb = 2 * rb * rb;
    int x = 0, y = rb;

    int d = ra * ra + rb * rb - aa * y;
    int d1, d2;

    while (y >= 0)
    {
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);
        if (d == 0)
        {
            DiagStep_Ell(x, y, d, ra, aa, rb, bb);
        }
        else if (d < 0)
        {
            d1 = 2 * d  + y * aa - ra * ra;
            if (d1 > 0)
                DiagStep_Ell(x, y, d, ra, aa, rb, bb);
            else
                HorizStep_Ell(x, d, rb, bb);
        }
        else
        {
            d2 = 2 * d - bb * x - rb * rb;
            if (d2 < 0)
                DiagStep_Ell(x, y, d, ra, aa, rb, bb);
            else
                VertStep_Ell(y, d, ra, aa);
        }
    }
}
