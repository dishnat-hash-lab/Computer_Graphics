#include <GL/glut.h>
#include <cmath>
#include <iostream>

int centerX = 250, centerY = 250; // Center of the ellipse
int a = 150, b = 100; // Semi-major axis (a) and semi-minor axis (b)

// Function to plot the symmetric points of the ellipse
void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerX + x, centerY + y); // 1st quadrant
    glVertex2i(centerX - x, centerY + y); // 2nd quadrant
    glVertex2i(centerX + x, centerY - y); // 3rd quadrant
    glVertex2i(centerX - x, centerY - y); // 4th quadrant
    glEnd();
    glFlush();
}

// Midpoint Ellipse Drawing Algorithm
void midpointEllipse() {
    int x = 0, y = b;
    int a2 = a * a, b2 = b * b;
    int twoa2 = 2 * a2, twob2 = 2 * b2;
    int p1 = b2 - a2 * b + 0.25 * a2;
    
    // Set the drawing color to red (full red, no green, no blue)
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color

    // Region 1: From (0, b) to (a, 0)
    while (twoa2 * y > twob2 * x) {
        plot(x, y); // Plot the symmetric points

        if (p1 < 0) {
            p1 += twob2 * x + b2;
        } else {
            y--;
            p1 += twob2 * x - twoa2 * y + b2;
        }
        x++;
    }

    int p2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    
    // Region 2: From (a, 0) to (0, b)
    while (y >= 0) {
        plot(x, y); // Plot the symmetric points

        if (p2 > 0) {
            p2 += a2 * (-y + 1) + a2;
        } else {
            x++;
            p2 += twob2 * x - twoa2 * y + a2;
        }
        y--;
    }
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set the 2D orthogonal view
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    midpointEllipse(); // Call the function to draw the ellipse
    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "Enter the semi-major axis (a): ";
    std::cin >> a; // Get the semi-major axis from the user
    std::cout << "Enter the semi-minor axis (b): ";
    std::cin >> b; // Get the semi-minor axis from the user

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single buffer and RGB color mode
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Midpoint Ellipse Drawing");

    initOpenGL(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display callback function

    glutMainLoop(); // Enter the GLUT event loop

    return 0;
}

// g++ midpoint_ellipse.cpp -o midpoint_ellipse -lGL -lGLU -lglut
// ./midpoint_ellipse

