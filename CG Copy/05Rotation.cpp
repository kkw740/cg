#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

// Object vertices
GLfloat originalVertices[][2] = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
int numVertices = 4;

// Rotation angle in degrees
GLfloat theta = 30;

// Arbitrary point for rotation
GLfloat pivotX = 0;
GLfloat pivotY = 0;

void MyInit() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-10, 10, -10, 10);
}

void drawAxes() {
    glColor3ub(100, 100, 100);
    glBegin(GL_LINES);
    glVertex2d(-10, 0);
    glVertex2d(10, 0);
    glVertex2d(0, -10);
    glVertex2d(0, 10);
    glEnd();
}

void ApplyRotation() {
    GLfloat thetaRad = theta * M_PI / 180.0;
    for (int i = 0; i < numVertices; ++i) {
        GLfloat x = originalVertices[i][0] - pivotX;
        GLfloat y = originalVertices[i][1] - pivotY;
        GLfloat newX = x * cos(thetaRad) - y * sin(thetaRad) + pivotX;
        GLfloat newY = x * sin(thetaRad) + y * cos(thetaRad) + pivotY;
        originalVertices[i][0] = newX;
        originalVertices[i][1] = newY;
    }
}

void afterRotation() {
    glColor3ub(200, 0, 0);

    // Apply rotation
    ApplyRotation();

    // Draw the rotated rectangle
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i) {
        glVertex2fv(originalVertices[i]);
    }
    glEnd();
}

void beforeRotation() {
    glColor3ub(0, 0, 200);

    // Draw the original rectangle
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i) {
        glVertex2fv(originalVertices[i]);
    }
    glEnd();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();
    beforeRotation();
    afterRotation();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Rotation About Arbitrary Point");
    MyInit();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

