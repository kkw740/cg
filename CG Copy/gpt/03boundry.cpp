#include<windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
#define PI 3.14

vector<int> x, y; // Stores polygon vertices
int vertex;       // Number of vertices
int radius = 50;  // Radius of the polygon
int centreX = 200, centreY = 200; // Center of the polygon

struct Color {
    GLfloat red, green, blue;
};
Color boundColor = {1.0, 0.0, 0.0};    // Red boundary
Color backgroundColor = {0.0, 0.0, 0.0}; // Black background
Color insideColor = {1.0, 1.0, 1.0};   // White fill

void generatePolygonPoints() {
    for (int i = 1; i <= vertex; i++) {
        int currx = (int)(centreX + radius * cos(((i - 1) * 2.0 * PI) / vertex));
        int curry = (int)(centreY + radius * sin(((i - 1) * 2.0 * PI) / vertex));
        x.push_back(currx);
        y.push_back(curry);
    }
}

void lineDraw(int a1, int b1, int a2, int b2) {
    glBegin(GL_LINES);
    glVertex2i(a1, b1);
    glVertex2i(a2, b2);
    glEnd();
}

void drawPolygon() {
    for (int i = 0; i < vertex - 1; i++)
        lineDraw(x[i], y[i], x[i + 1], y[i + 1]);
    lineDraw(x[vertex - 1], y[vertex - 1], x[0], y[0]);
}

Color getColorPixel(GLint pointX, GLint pointY) {
    Color pointColor;
    glReadPixels(pointX, pointY, 1, 1, GL_RGB, GL_FLOAT, &pointColor);
    return pointColor;
}

void fillColorPixel(GLint pointX, GLint pointY) {
    glColor3f(insideColor.red, insideColor.green, insideColor.blue);
    glBegin(GL_POINTS);
    glVertex2i(pointX, pointY);
    glEnd();
    glFlush();
}

bool colorNotFilled(Color currColor) {
    return ((currColor.red != boundColor.red || currColor.green != boundColor.green || currColor.blue != boundColor.blue) &&
            (currColor.red != insideColor.red || currColor.green != insideColor.green || currColor.blue != insideColor.blue));
}

bool colorEqual(Color currentColor) {
    return (currentColor.red == boundColor.red && currentColor.green == boundColor.green && currentColor.blue == boundColor.blue);
}

void BoundFillRecursionBased(int currX, int currY) {
    if (colorEqual(getColorPixel(currX, currY))) return;

    if (colorNotFilled(getColorPixel(currX, currY))) {
        fillColorPixel(currX, currY);
        BoundFillRecursionBased(currX + 1, currY);
        BoundFillRecursionBased(currX - 1, currY);
        BoundFillRecursionBased(currX, currY + 1);
        BoundFillRecursionBased(currX, currY - 1);
    }
}

void disp() {
    glColor3f(boundColor.red, boundColor.green, boundColor.blue);
    drawPolygon();
    BoundFillRecursionBased(centreX, centreY);
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter the number of vertices of the regular polygon: ";
    cin >> vertex;

    generatePolygonPoints();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(centreX * 2, centreY * 2);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Boundary Fill Algorithm");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, centreX * 2, 0, centreY * 2);
    glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}

