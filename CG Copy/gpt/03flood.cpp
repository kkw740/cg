#include<windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
#define PI 3.14

vector<int> x, y;
int vertex, radius = 50;
int centreX = 200, centreY = 200;

struct Color {
    GLfloat red, green, blue;
};
Color boundColor = {1.0, 0.0, 0.0}, backgroundColor = {0.0, 0.0, 0.0}, insideColor = {1.0, 1.0, 1.0};

void generatePolygonPoints() {
    for (int i = 1; i <= vertex; i++) {
        x.push_back(centreX + radius * cos(((i - 1) * 2.0 * PI) / vertex));
        y.push_back(centreY + radius * sin(((i - 1) * 2.0 * PI) / vertex));
    }
}

void drawPolygon() {
    for (int i = 0; i < vertex - 1; i++) {
        glBegin(GL_LINES);
        glVertex2i(x[i], y[i]);
        glVertex2i(x[i + 1], y[i + 1]);
        glEnd();
    }
    glBegin(GL_LINES);
    glVertex2i(x[vertex - 1], y[vertex - 1]);
    glVertex2i(x[0], y[0]);
    glEnd();
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

void FloodFill(int currX, int currY) {
    Color currColor = getColorPixel(currX, currY);
    if (currColor.red != backgroundColor.red || currColor.green != backgroundColor.green || currColor.blue != backgroundColor.blue)
        return;

    fillColorPixel(currX, currY);
    FloodFill(currX + 1, currY);
    FloodFill(currX, currY + 1);
    FloodFill(currX - 1, currY);
    FloodFill(currX, currY - 1);
}

void disp() {
    glColor3f(boundColor.red, boundColor.green, boundColor.blue);
    drawPolygon();
    FloodFill(centreX, centreY);
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter the number of vertices of the regular polygon: ";
    cin >> vertex;
    generatePolygonPoints();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(centreX * 2, centreY * 2);
    glutInitWindowPosition(800, 50);
    glutCreateWindow("Flood Fill Algorithm");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, centreX * 2, 0, centreY * 2);
    glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}

