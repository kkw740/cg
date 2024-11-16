#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

#define WHITE 15

void drawCircle(int xc, int yc, int x, int y) {
    putpixel(xc + x, yc + y, WHITE);
    putpixel(xc - x, yc + y, WHITE);
    putpixel(xc + x, yc - y, WHITE);
    putpixel(xc - x, yc - y, WHITE);
    putpixel(xc + y, yc + x, WHITE);
    putpixel(xc - y, yc + x, WHITE);
    putpixel(xc + y, yc - x, WHITE);
    putpixel(xc - y, yc - x, WHITE);
}

void circleBres(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - 2 * r;
    while (y >= x) {
        drawCircle(xc, yc, x, y);
        x++;
        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else
            d += 4 * x + 6;
        drawCircle(xc, yc, x, y);
    }
}

void bezierCurve(int x[], int y[]) {
    int i;
    double xu, yu, u;
    for (u = 0.0; u <= 1.0; u += 0.0001) {
        xu = pow(1 - u, 3) * x[0] + 3 * u * pow(1 - u, 2) * x[1] + 3 * pow(u, 2) * (1 - u) * x[2] + pow(u, 3) * x[3];
        yu = pow(1 - u, 3) * y[0] + 3 * u * pow(1 - u, 2) * y[1] + 3 * pow(u, 2) * (1 - u) * y[2] + pow(u, 3) * y[3];
        putpixel((int)xu, (int)yu, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int i, x[4], y[4];

    for (i = 0; i < 4; i++) {
        printf("Enter x%d, y%d: ", i, i);
        scanf("%d%d", &x[i], &y[i]);
        circleBres(x[i], y[i], 8);
        if (i > 0)
            line(x[i - 1], y[i - 1], x[i], y[i]);
    }

    bezierCurve(x, y);

    while (!kbhit()) {
        delay(100);
    }

    closegraph();
    return 0;
}

