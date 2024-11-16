75% of storage used … If you run out, you can't create, edit and upload files.
#include <GL/glut.h>
#include <iostream>

// Define control points (change as needed)
GLfloat controlPoints[3][2] = {
    {100.0, 100.0},  // Control Point 1
    {250.0, 400.0},  // Control Point 2
    {400.0, 100.0}   // Control Point 3
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

    // Draw control points
    glColor3f(0.0, 0.0, 1.0); // Set color to blue for control points
    for (int i = 0; i < 3; ++i) {
        drawPoint(controlPoints[i][0], controlPoints[i][1]);
    }

    // Draw the Bézier curve
    glColor3f(1.0, 0.0, 0.0); // Set color back to red for curve
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= 100; ++i) {
        GLfloat t = GLfloat(i) / 100.0;
        GLfloat x = (1 - t) * (1 - t) * controlPoints[0][0] + 2 * (1 - t) * t * controlPoints[1][0] + t * t * controlPoints[2][0];
        GLfloat y = (1 - t) * (1 - t) * controlPoints[0][1] + 2 * (1 - t) * t * controlPoints[1][1] + t * t * controlPoints[2][1];
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

    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white

    glutMainLoop();
    return 0;
}
