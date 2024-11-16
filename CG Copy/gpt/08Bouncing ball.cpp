#include <GL/glut.h>
#include <cmath>

// Ball properties
float ballX = 0.0f; // Ball position in the X-axis
float ballY = -0.8f; // Ball position in the Y-axis
float ballRadius = 0.1f; // Ball radius
float velocityY = 0.02f; // Vertical velocity of the ball
float gravity = -0.001f; // Gravity to apply to the ball's motion
float squashFactor = 1.0f; // Factor for "squash and stretch"
bool goingUp = false; // Direction flag for motion

void drawCircle(float x, float y, float radius, float squashFactor) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180;
        float dx = radius * squashFactor * cos(theta);
        float dy = radius / squashFactor * sin(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Render function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Ball color

    // Draw the ball with squash/stretch effect
    drawCircle(ballX, ballY, ballRadius, squashFactor);

    glFlush();
}

// Timer function for animation
void update(int value) {
    // Update the vertical position
    ballY += velocityY;
    velocityY += gravity;

    // Handle bounce when the ball hits the ground
    if (ballY - ballRadius <= -1.0f) {
        ballY = -1.0f + ballRadius;
        velocityY = -velocityY * 0.8f; // Reverse velocity with damping
        goingUp = true; // Ball is going up after the bounce
    }

    // Squash and stretch effect
    if (goingUp) {
        squashFactor = 1.0f - (fabs(velocityY) * 10.0f); // Stretch when going up
        if (squashFactor < 0.8f) squashFactor = 0.8f;
    } else {
        squashFactor = 1.0f + (fabs(velocityY) * 10.0f); // Squash when hitting the ground
        if (squashFactor > 1.2f) squashFactor = 1.2f;
    }

    // Ease-out effect as the ball slows down
    if (fabs(velocityY) < 0.001f && ballY - ballRadius == -1.0f) {
        goingUp = false;
        velocityY = 0.02f; // Restart bounce
    }

    // Redisplay the scene
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Call the update function every 16 ms
}

// OpenGL initialization
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set 2D coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Ball Animation");

    init();

    glutDisplayFunc(display); // Display function
    glutTimerFunc(16, update, 0); // Start the animation timer

    glutMainLoop();
    return 0;
}

