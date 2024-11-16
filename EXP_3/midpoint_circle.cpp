#include <GL/glut.h>
#include <cmath>
#include <iostream>

int centerX = 250, centerY = 250; // Center of the circle
int radius = 100; // Radius of the circle

// Function to plot the symmetric points of the circle
void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerX + x, centerY + y); // Plot the point in all octants
    glVertex2i(centerX - x, centerY + y);
    glVertex2i(centerX + x, centerY - y);
    glVertex2i(centerX - x, centerY - y);
    glVertex2i(centerX + y, centerY + x);
    glVertex2i(centerX - y, centerY + x);
    glVertex2i(centerX + y, centerY - x);
    glVertex2i(centerX - y, centerY - x);
    glEnd();
    glFlush();
}

// Midpoint Circle Drawing Algorithm
void midpointCircle() {
    int x = radius, y = 0;
    int p = 1 - radius; // Initial decision parameter

    // Set the drawing color to red (full red, no green, no blue)
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color

    // Draw the initial points
    plot(x, y);

    // Plot the circle using the midpoint algorithm
    while (x > y) {
        y++;
        
        // Update the decision parameter based on the error term
        if (p <= 0) {
            p = p + 2 * y + 1;
        } else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }

        plot(x, y); // Plot the points for the current (x, y)
    }
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 0, 500); // Set the 2D orthogonal view
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    midpointCircle(); // Call the function to draw the circle
    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius; // Get the radius from the user

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single buffer and RGB color mode
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Midpoint Circle Drawing");

    initOpenGL(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display callback function

    glutMainLoop(); // Enter the GLUT event loop

    return 0;
}


// g++ midpoint_circle.cpp -o midpoint_circle -lGL -lGLU -lglut
// ./midpoint_circle
