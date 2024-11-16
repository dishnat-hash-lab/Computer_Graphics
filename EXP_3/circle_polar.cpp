#include <GL/glut.h>
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846;
float radius = 100.0f;  // Radius of the circle
int centerX = 250, centerY = 250;  // Center of the circle

void plotPixel(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawCircle() {
    glColor3f(1.0f, 0.0f, 0.0f);  // Set circle color to red

    for (float theta = 0.0f; theta <= 2 * PI; theta += 0.01f) {
        float x = centerX + radius * cos(theta);  // Convert polar to Cartesian x = r * cos(theta)
        float y = centerY + radius * sin(theta);  // y = r * sin(theta)
        plotPixel(x, y);
    }
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 0, 500);  // Set the 2D orthogonal view
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    drawCircle();  // Call the function to draw the circle
    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;  // User input for the radius

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Use single buffer and RGB color mode
    glutInitWindowSize(200, 200);  // Set window size
    glutInitWindowPosition(100, 100);  // Set window position
    glutCreateWindow("Circle using Polar Equations");

    initOpenGL();  // Initialize OpenGL settings

    glutDisplayFunc(display);  // Register the display callback function

    glutMainLoop();  // Enter the GLUT event loop

    return 0;
}


//g++ circle_polar.cpp -o circle_polar -lGL -lGLU -lglut
// ./circle_polar