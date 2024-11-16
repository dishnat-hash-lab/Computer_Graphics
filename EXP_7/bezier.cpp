#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Define the control points for the cubic Bezier curve
float P0[] = {-0.6f, -0.5f};
float P1[] = {-0.2f, 0.8f};
float P2[] = {0.2f, -0.8f};
float P3[] = {0.6f, 0.5f};

// Number of points to sample for drawing the curve
#define NUM_POINTS 100

// Function to calculate the cubic Bezier curve point at parameter t
void bezier(float t, float* point) {
    float u = 1.0f - t;
    float u2 = u * u;
    float u3 = u2 * u;
    float t2 = t * t;
    float t3 = t2 * t;

    // Bézier curve formula
    point[0] = u3 * P0[0] + 3 * u2 * t * P1[0] + 3 * u * t2 * P2[0] + t3 * P3[0];
    point[1] = u3 * P0[1] + 3 * u2 * t * P1[1] + 3 * u * t2 * P2[1] + t3 * P3[1];
}

// Function to display the curve and control points
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the Bezier curve
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_POINTS; i++) {
        float t = static_cast<float>(i) / NUM_POINTS;
        float point[2];
        bezier(t, point);
        glVertex2f(point[0], point[1]);
    }
    glEnd();

    // Draw control points (small circles)
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(P0[0], P0[1]);
    glVertex2f(P1[0], P1[1]);
    glVertex2f(P2[0], P2[1]);
    glVertex2f(P3[0], P3[1]);
    glEnd();

    // Draw control polygon (lines between control points)
    glBegin(GL_LINE_STRIP);
    glVertex2f(P0[0], P0[1]);
    glVertex2f(P1[0], P1[1]);
    glVertex2f(P2[0], P2[1]);
    glVertex2f(P3[0], P3[1]);
    glEnd();

    glFlush();
}

// Set up OpenGL and GLUT
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glColor3f(0.0f, 0.0f, 0.0f);           // Set drawing color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f); // Set up orthogonal projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cubic Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
// g++ bezier.cpp -o bezier -lGL -lGLU -lglut
// ./bezier
