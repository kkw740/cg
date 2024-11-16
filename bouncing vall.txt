#include<GL/freeglut.h>
#include<cmath>

int x = 250, y = 250;
int flag = 0;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
}

void update(int value) {
    if (y >= 470 || y <= 30) {
        flag = !flag;
    }
    if (flag) {
        y += 5;
    } else {
        y -= 5;
    }
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void drawball() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (float angle = 0; angle < 360; angle += 1) {
        float xc = x + cos(angle * M_PI / 180.0) * 30;
        float yc = y + sin(angle * M_PI / 180.0) * 30;
        glVertex2f(xc, yc);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bouncing Ball");
    init();
    glutDisplayFunc(drawball);
    glutTimerFunc(30, update, 0);
    glutMainLoop();
    return 0;
}
