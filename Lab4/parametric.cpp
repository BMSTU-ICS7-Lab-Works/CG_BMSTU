#include "math.h"
#include "graphics.h"
#include "plot.h"
#include "QDebug"

void parametric(double xc, double yc, double r, graphics_t &graphics)
{
    double x, y;
    double dt = 1.0 / r;
    int n = round(M_PI / 4 / dt);
    for (double i = 0; i <= n; i ++)
    {
        double t = i * dt;
        x = r * cos(t);
        y = r * sin(t);
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

void parametric_ellipse(double xc, double yc, int ra, int rb, graphics_t &graphics)
{
    double x, y, t;
    double tmp;
    if (ra > rb)
        tmp = ra;
    else
        tmp = rb;
    double dt = 1.0 / tmp;
    double n = round(M_PI / dt);
    for (int i = 1; i <= n; i++)
    {
        t = i * dt;
        x = ra * cos(t);
        y = rb * sin(t);
        plot(xc + x, yc + y, graphics);
        plot(xc - x, yc - y, graphics);
        plot(xc + x, yc - y, graphics);
        plot(xc - x, yc + y, graphics);
    }
}
