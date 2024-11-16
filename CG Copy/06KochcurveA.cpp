#include <GL/glut.h>
#include <cmath>
#include<iostream>
using namespace std;


float x11, y11,x22,y22;
int iterations;
// Function to draw a Koch curve segment
void drawKochCurve(float x1, float y1, float x2, float y2, int iterations) {
    if (iterations == 0) {
        // Base case: draw a straight line
        glBegin(GL_LINE);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    } else {
        // Calculate new points dividing the line into three segments
        float dx = (x2 - x1) / 3.0;
        float dy = (y2 - y1) / 3.0;

        float xA = x1 + dx;
        float yA = y1 + dy;

        float xB = x1 + 2.0 * dx;
        float yB = y1 + 2.0 * dy;

        // Calculate the position of the peak of the Koch curve
        float angle = M_PI / 3.0; // 60 degrees in radians
        float xC = xA + dx * cos(angle) - dy * sin(angle);
        float yC = yA + dx * sin(angle) + dy * cos(angle);

        // Recursively draw the four segments of the Koch curve
        drawKochCurve(x1, y1, xA, yA, iterations - 1);
        drawKochCurve(xA, yA, xC, yC, iterations - 1);
        drawKochCurve(xC, yC, xB, yB, iterations - 1);
        drawKochCurve(xB, yB, x2, y2, iterations - 1);
    }
}

// Function to display the Koch curve
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Set line color to red

    // Define the endpoints of the Koch curve
   // float x1 = -0.5;
    //float y1 = -0.3;
    //float x2 = 0.5;
    //float y2 = -0.3;

    //int iterations = 4; // Number of iterations (adjust for desired resolution)
    drawKochCurve(x11, y11, x22, y22, iterations);

    glFlush();
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the coordinate system
}

int main(int argc, char** argv) {
    cout<<"enter the points"<<endl;
    cout<<" x1 : ";
    cin>>x11;
     cout<<" y1 : ";
    cin>>y11;
     cout<<" x2 : ";
    cin>>x22;
     cout<<" y2 : ";
    cin>>y22;
     cout<<" iterations : ";
    cin>>iterations;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800); // Set the window size
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("Koch Curve");

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Set the display function

    glutMainLoop(); // Enter the OpenGL main loop

    return 0;
}
enter the points
 x1 : -0.8
 y1 : -0.4
 x2 : 0.8
 y2 : -0.4
 iterations : 4
