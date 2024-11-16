#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
// Object vertices
GLfloat originalVertices[][2] = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
int numVertices = 4;
// Scaling factors
GLfloat sx = 2.0, sy = 2.0;
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
void ApplyScaling(GLfloat transformedVertices[][2], const GLfloat originalVertices[][2], GLfloat sx, GLfloat sy) {
    for (int i = 0; i < numVertices; ++i) {
        transformedVertices[i][0] = originalVertices[i][0] * sx;
        transformedVertices[i][1] = originalVertices[i][1] * sy;
    }
}
void afterScaling() {
    glColor3ub(200, 0, 0);
    // Temporary array to hold scaled vertices
    GLfloat scaledVertices[numVertices][2];
    // Apply scaling to a copy of original vertices
    ApplyScaling(scaledVertices, originalVertices, sx, sy);
    // Draw the scaled polygon
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i) {
        glVertex2fv(scaledVertices[i]);
    }
    glEnd();
}
void beforeScaling() {
    glColor3ub(0, 0, 200);
    // Draw the original polygon
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i) {
        glVertex2fv(originalVertices[i]);
    }
    glEnd();
}
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    afterScaling();
beforeScaling();
    glFlush();
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Scaling");
    MyInit();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
