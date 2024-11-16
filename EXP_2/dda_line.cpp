#include <GL/glut.h>
#include <iostream>
#include <cmath>

float x1, yy1, x2, yy2;  

// Function to plot a pixel on the screen
void putPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);  // Plot the pixel at the given (x, y) location
    glEnd();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set the background color to white
    glColor3f(0.0, 0.0, 0.0);  // Set the drawing color to black (for points)
    glPointSize(2.0);  // Set the size of points

    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);  // Set the window coordinates (0 to 500)
    glMatrixMode(GL_MODELVIEW);  
}

// Function to draw the line using DDA algorithm
void drawDDA() {
    float dx = x2 - x1;
    float dy = yy2 - yy1;
    int steps = std::max(std::abs(dx), std::abs(dy));  // Calculate the number of steps required
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = yy1;

    for (int i = 0; i <= steps; i++) {
        putPixel(round(x), round(y));  // Plot the current point
        x += xIncrement;
        y += yIncrement;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    
    // Draw the line using DDA algorithm
    glColor3f(1.0, 0.0, 0.0);  // Red color for the DDA line
    drawDDA();

    glutSwapBuffers();  // Swap the buffers to display the result
}

int main(int argc, char** argv) {
    std::cout << "Enter coordinates for the first point (x1 y1): ";
    std::cin >> x1 >> yy1;
    std::cout << "Enter coordinates for the second point (x2 y2): ";
    std::cin >> x2 >> yy2;

    // Adjust the input coordinates to OpenGL window space (0 to 500)
    x1 = (x1 / 500.0) * 500.0;
    yy1 = (yy1 / 500.0) * 500.0;
    x2 = (x2 / 500.0) * 500.0;
    yy2 = (yy2 / 500.0) * 500.0;

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
    glutInitWindowSize(500, 500);  
    glutCreateWindow("DDA Line Drawing Algorithm");  // Create a window with the title
    init();  // Initialize OpenGL settings
    glutDisplayFunc(display);  // Set the display function to render the scene

    glutMainLoop();  // Enter the GLUT main event loop
    return 0;
}



// g++ dda_line.cpp -o dda_line -lGL -lGLU -lglut
// ./dda_line
