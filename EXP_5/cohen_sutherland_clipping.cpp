#include <GL/glut.h>
#include <iostream>
#include <cmath>

struct Point {
    int x, y;
};

// Define clipping window boundaries
int xmin = 100, ymin = 100, xmax = 400, ymax = 400;

// Define the two endpoints of the line
Point p1, p2;

// Outcode for each point
int computeOutcode(Point p) {
    int outcode = 0;

    if (p.x < xmin) outcode |= 1;  // Left
    if (p.x > xmax) outcode |= 2;  // Right
    if (p.y < ymin) outcode |= 4;  // Bottom
    if (p.y > ymax) outcode |= 8;  // Top

    return outcode;
}

// Cohen-Sutherland Line Clipping Algorithm
void cohenSutherlandClip(Point& p1, Point& p2) {
    int outcode1 = computeOutcode(p1);
    int outcode2 = computeOutcode(p2);
    bool accept = false;

    while (true) {
        if ((outcode1 == 0) && (outcode2 == 0)) {
            // Both points are inside the window
            accept = true;
            break;
        } else if ((outcode1 & outcode2) != 0) {
            // Both points share an outside zone
            break;  // Reject the line
        } else {
            // One of the points is outside the window
            int outcodeOut = (outcode1 != 0) ? outcode1 : outcode2;
            int x, y;

            // Clip the line to the window
            if (outcodeOut & 8) {  // Top
                x = p1.x + (p2.x - p1.x) * (ymax - p1.y) / (p2.y - p1.y);
                y = ymax;
            } else if (outcodeOut & 4) {  // Bottom
                x = p1.x + (p2.x - p1.x) * (ymin - p1.y) / (p2.y - p1.y);
                y = ymin;
            } else if (outcodeOut & 2) {  // Right
                y = p1.y + (p2.y - p1.y) * (xmax - p1.x) / (p2.x - p1.x);
                x = xmax;
            } else if (outcodeOut & 1) {  // Left
                y = p1.y + (p2.y - p1.y) * (xmin - p1.x) / (p2.x - p1.x);
                x = xmin;
            }

            // Update the outside point to the new clipped point
            if (outcodeOut == outcode1) {
                p1.x = x;
                p1.y = y;
                outcode1 = computeOutcode(p1);
            } else {
                p2.x = x;
                p2.y = y;
                outcode2 = computeOutcode(p2);
            }
        }
    }

    // If accepted, update the points
    if (accept) {
        std::cout << "Clipped line: (" << p1.x << ", " << p1.y << ") to ("
                  << p2.x << ", " << p2.y << ")\n";
    } else {
        std::cout << "Line rejected\n";
    }
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

    // Apply Cohen-Sutherland line clipping
    cohenSutherlandClip(p1, p2);

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
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    initOpenGL();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

// g++ cohen_sutherland_clipping.cpp -o cohen_sutherland_clipping -lGL -lGLU -lglut
// ./cohen_sutherland_clipping