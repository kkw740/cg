#include <iostream>
#include <GL/glut.h>
#include <list>

using namespace std;

// Global variables
int xmin = 0, ymin = 0, xmax = 0, ymax = 0, enter = 1, sz;
float** pts; // Stores polygon vertices
list<points*> in; // Stores input vertices

// Class for points
class points {
    int x, y;
public:
    points(int x, int y) : x(x), y(y) {}
    int getx() { return x; }
    int gety() { return y; }
};

// OpenGL initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

// Draw polygon
void drawPolygon() {
    glBegin(GL_LINE_LOOP);
    pts = new float*[in.size()];
    for (int i = 0; i < in.size(); i++) {
        pts[i] = new float[2];
    }
    sz = in.size();
    while (!in.empty()) {
        points* temp = in.front();
        pts[in.size() - 1][0] = temp->getx();
        pts[in.size() - 1][1] = temp->gety();
        glVertex2i(temp->getx(), temp->gety());
        in.pop_front();
    }
    glEnd();
    glFlush();
}

// Redraw polygon and clipping rectangle
void redraw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sz; i++) {
        glVertex2i(pts[i][0], pts[i][1]);
    }
    glEnd();
    glFlush();

    // Draw clipping rectangle
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();
    glFlush();
}

// Check if a point is inside a clip boundary
int inside(int x, int y, int clip_edge) {
    switch (clip_edge) {
        case 1: return x < xmax; break; // Right edge
        case 2: return y > ymax; break; // Bottom edge
        case 3: return x > xmin; break; // Left edge
        case 4: return y < ymin; break; // Top edge
        default: return 0; break;
    }
}

// Calculate intersection of a line segment with a clip edge
points* intersect(points* S, points* P, int clip_edge) {
    float m = (P->getx() - S->getx()) == 0 ? 0 : (float)(P->gety() - S->gety()) / (P->getx() - S->getx());
    float c = (float)(S->gety()) - (m * S->getx());

    if (clip_edge == 1) { int x = xmax; int y = (m * x) + c; return new points(x, y); }
    if (clip_edge == 2) { int y = ymax; int x = (m == 0) ? P->getx() : (y - c) / m; return new points(x, y); }
    if (clip_edge == 3) { int x = xmin; int y = (m * x) + c; return new points(x, y); }
    if (clip_edge == 4) { int y = ymin; int x = (m == 0) ? P->getx() : (y - c) / m; return new points(x, y); }
}

// Perform Sutherland-Hodgeman Polygon Clipping for one edge
float** SHPC(float** inva, list<points*> out, int clip_edge) {
    points* s = new points(inva[sz - 1][0], inva[sz - 1][1]);
    for (int j = 0; j < sz; j++) {
        points* p = new points(inva[j][0], inva[j][1]);

        if (inside(p->getx(), p->gety(), clip_edge)) {
            if (inside(s->getx(), s->gety(), clip_edge)) {
                out.push_front(new points(p->getx(), p->gety()));
            } else {
                out.push_front(intersect(s, p, clip_edge));
                out.push_front(p);
            }
        } else if (inside(s->getx(), s->gety(), clip_edge)) {
            out.push_front(intersect(s, p, clip_edge));
        }
        s = p;
    }

    // Update polygon vertices
    float** inner = new float*[out.size()];
    for (int i = 0; i < out.size(); i++) {
        inner[i] = new float[2];
    }
    sz = out.size();
    while (!out.empty()) {
        points* temp = out.front();
        inner[out.size() - 1][0] = temp->getx();
        inner[out.size() - 1][1] = temp->gety();
        out.pop_front();
    }
    return inner;
}

// Keyboard events
void key(unsigned char key_t, int x, int y) {
    if (key_t == 'd') {
        enter = -1;    // Stop adding vertices
        drawPolygon();
    }
    if (key_t == 'c') {
        pts = SHPC(pts, {}, 1); // Right edge
        pts = SHPC(pts, {}, 2); // Bottom edge
        pts = SHPC(pts, {}, 3); // Left edge
        pts = SHPC(pts, {}, 4); // Top edge
        redraw();
    }
}

// Mouse click to add points
void mouse(int btn, int state, int x, int y) {
    y = 480 - y; // Adjust y-coordinate
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && enter) {
        in.push_front(new points(x, y));
    }
}

// Dragging to create the clipping rectangle
void drag_start(GLint x, GLint y) {
    y = 480 - y;
    if (enter == -1) {
        xmin = x;
        ymin = y;
    }
    redraw();
}

void drag_end(GLint x, GLint y) {
    y = 480 - y;
    if (enter == -1) {
        xmax = x;
        ymax = y;
        redraw();
    }
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Polygon Clipping");
    glutDisplayFunc([]() { glClear(GL_COLOR_BUFFER_BIT); glFlush(); }); // Initial blank canvas
    glutMouseFunc(mouse);
    glutMotionFunc(drag_start);
    glutPassiveMotionFunc(drag_end);
    glutKeyboardFunc(key);
    init();
    glutMainLoop();
    return 0;
}

