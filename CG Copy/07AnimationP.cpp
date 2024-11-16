#include <iostream>
#include <graphics.h>

int main() {
    int gd = DETECT, gm, x = 320, y = 200, direction = 1;

    initgraph(&gd, &gm, "");

    while (!kbhit()) {
        setcolor(4);
        line(0, 400, 679, 400);

        y += direction * 2;

        if (y >= 385 || y <= 15) {
            direction *= -1;
        }

        setcolor(15);
        fillellipse(x, y, 15, 15);
        delay(15);
        setcolor(0);
        setfillstyle(SOLID_FILL, 10);
        fillellipse(x, y, 15, 15);
        cleardevice();
    }

    closegraph();
    return 0;
}
