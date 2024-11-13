#include <GL/glut.h>
#include <iostream>
#include <cmath>

struct Point {
    int x, y;
};

// Define the clipping window boundaries
int xmin = 100, ymin = 100, xmax = 400, ymax = 400;

// Define the two endpoints of the line
Point p1, p2;

// Liang-Barsky Line Clipping Algorithm
void liangBarskyClip(Point& p1, Point& p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float t0 = 0.0, t1 = 1.0;
    float p, q, r;

    // Left clipping boundary
    p = -dx;
    q = p1.x - xmin;
    r = q / p;
    if (p < 0) {
        if (q < 0) return; // Reject the line
        if (r > t1) return; // Reject the line
        if (r > t0) t0 = r; // Clip the line
    } else if (p > 0) {
        if (q > 0) return; // Reject the line
        if (r < t0) return; // Reject the line
        if (r < t1) t1 = r; // Clip the line
    }

    // Right clipping boundary
    p = dx;
    q = xmax - p1.x;
    r = q / p;
    if (p < 0) {
        if (q > 0) return; // Reject the line
        if (r > t1) return; // Reject the line
        if (r > t0) t0 = r; // Clip the line
    } else if (p > 0) {
        if (q < 0) return; // Reject the line
        if (r < t0) return; // Reject the line
        if (r < t1) t1 = r; // Clip the line
    }

    // Bottom clipping boundary
    p = -dy;
    q = p1.y - ymin;
    r = q / p;
    if (p < 0) {
        if (q < 0) return; // Reject the line
        if (r > t1) return; // Reject the line
        if (r > t0) t0 = r; // Clip the line
    } else if (p > 0) {
        if (q > 0) return; // Reject the line
        if (r < t0) return; // Reject the line
        if (r < t1) t1 = r; // Clip the line
    }

    // Top clipping boundary
    p = dy;
    q = ymax - p1.y;
    r = q / p;
    if (p < 0) {
        if (q > 0) return; // Reject the line
        if (r > t1) return; // Reject the line
        if (r > t0) t0 = r; // Clip the line
    } else if (p > 0) {
        if (q < 0) return; // Reject the line
        if (r < t0) return; // Reject the line
        if (r < t1) t1 = r; // Clip the line
    }

    // Compute the new clipped points
    p1.x = p1.x + t0 * dx;
    p1.y = p1.y + t0 * dy;
    p2.x = p1.x + t1 * dx;
    p2.y = p1.y + t1 * dy;

    std::cout << "Clipped line: (" << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ")\n";
}

void plotLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();
    glFlush();
}

void drawRectangle() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(0.0, 0.0, 0.0);  // Black for rectangle
    drawRectangle();

    // Draw the original line in blue
    glColor3f(0.0, 0.0, 1.0);  // Blue for original line
    plotLine(p1, p2);

    // Apply Liang-Barsky line clipping
    liangBarskyClip(p1, p2);

    // Draw the clipped line in red
    glColor3f(1.0, 0.0, 0.0);  // Red for clipped line
    plotLine(p1, p2);

    glFlush();
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set 2D orthogonal projection
}

int main(int argc, char** argv) {
    std::cout << "Enter the coordinates of the first endpoint of the line (x1, y1): ";
    std::cin >> p1.x >> p1.y;
    std::cout << "Enter the coordinates of the second endpoint of the line (x2, y2): ";
    std::cin >> p2.x >> p2.y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang-Barsky Line Clipping");

    initOpenGL();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


// g++ liang_barsky_clipping.cpp -o liang_barsky_clipping -lGL -lGLU -lglut
// ./liang_barsky_clipping
