#include "math.h"
#include "graphics.h"
#include "QDebug"

void plot(double x, double y,  graphics_t &graphics)
{
    graphics.scene->addLine(x, y, x, y, graphics.pen);
}
