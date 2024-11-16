#include <GL/glut.h>
#include <iostream>

using namespace std;

int x_1, y_1, x2, y2;

void init() {
    // Set background color to white and clear the color buffer
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the projection to 2D
    gluOrtho2D(0, 500, 0, 500);
}

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenhamLine() {
    int dx = abs(x2 - x_1);
    int dy = abs(y2 - y_1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy;
    int twoDyDx = 2 * (dy - dx);
    int x, y;

    // Determine the initial points
    if (x_1 > x2) {
        x = x2;
        y = y2;
        x2 = x_1;
        y_1 = y;
    } else {
        x = x_1;
        y = y_1;
    }

    // Set the line color to red
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color

    plot(x, y); // Plot the first point

    // Bresenham's Algorithm
    while (x < x2) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyDx;
        }
        plot(x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    bresenhamLine();
    glFlush();
}

int main(int argc, char** argv) {
    // Input coordinates from user
    cout << "Enter the value of x1, y1: ";
    cin >> x_1 >> y_1;
    cout << "Enter the value of x2, y2: ";
    cin >> x2 >> y2;

    // Initialize GLUT and set up the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Line Drawing");

    // Call initialization functions
    init();

    // Set the display function
    glutDisplayFunc(display);

    // Start the main loop
    glutMainLoop();

    return 0;
}


//g++ bresenham_line.cpp -o bresenham_line -lGL -lGLU -lglut
//./bresenham_line
