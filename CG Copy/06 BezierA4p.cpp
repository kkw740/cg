#include<windows.h>
#include <GL/glut.h>
#include <iostream>
#include<cmath>

// Define control points (change as needed)
GLfloat controlPoints[4][2] = {
    {100.0, 100.0},  // Control Point 1
    {250.0, 400.0},  // Control Point 2
    {400.0, 100.0},  // Control Point
      {500.0,200.0} // Control Point 4

};

// Function to draw a point
void drawPoint(GLfloat x, GLfloat y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// Function to draw the Bézier curve
void drawBezierCurve() {
    glColor3f(1.0, 0.0, 0.0); // Set color to red


    for (int i = 0; i < 4; ++i) {
        drawPoint(controlPoints[i][0], controlPoints[i][1]);
    }


    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= 100; ++i) {
        GLfloat t = GLfloat(i) / 100.0;
 GLfloat x = pow(1 - t, 3) * controlPoints[0][0] +
                    3 * pow(1 - t, 2) * t * controlPoints[1][0] +
                    3 * (1 - t) * pow(t, 2) * controlPoints[2][0] +
                    pow(t, 3) * controlPoints[3][0];
        GLfloat y = pow(1 - t, 3) * controlPoints[0][1] +
                    3 * pow(1 - t, 2) * t * controlPoints[1][1] +
                    3 * (1 - t) * pow(t, 2) * controlPoints[2][1] +
                    pow(t, 3) * controlPoints[3][1];
        glVertex2f(x, y);
    }

    glEnd();
    glFlush();
}

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bézier Curve");

    glutDisplayFunc(drawBezierCurve);
    glutReshapeFunc(reshape);



    glutMainLoop();
    return 0;
}

