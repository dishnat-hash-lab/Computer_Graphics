#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

// Vertex structure to store points
struct Vertex {
    float x, y;
};

// Global variables for transformations
Vertex points[3] = {
    { 0.0f, 0.5f },    // Top vertex
    { -0.5f, -0.5f },  // Bottom-left vertex
    { 0.5f, -0.5f }    // Bottom-right vertex
};
float angle = 0.0;
float scaleX = 1.0, scaleY = 1.0;
float transX = 0.0, transY = 0.0;
float shearX = 0.0, shearY = 0.0;
float reflectX = 1.0, reflectY = 1.0;
float m = 1.0, c = 0.0;

// Function to draw a triangle based on current transformations
void drawTriangle() {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 3; ++i) {
        float x = points[i].x * scaleX * reflectX + shearX * points[i].y + transX;
        float y = points[i].y * scaleY * reflectY + shearY * points[i].x + transY;
        float newX = x * cos(angle) - y * sin(angle);
        float newY = x * sin(angle) + y * cos(angle);
        glVertex2f(newX, newY);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red color
    drawTriangle();
    glFlush();
}

// Keyboard interaction for transformations
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': transY += 0.1f; break;       // Translate up
    case 's': transY -= 0.1f; break;       // Translate down
    case 'a': transX -= 0.1f; break;       // Translate left
    case 'd': transX += 0.1f; break;       // Translate right
    case 'q': angle += 0.1f; break;        // Rotate counter-clockwise
    case 'e': angle -= 0.1f; break;        // Rotate clockwise
    case 'i': scaleY += 0.1f; break;       // Scale up in Y
    case 'k': scaleY -= 0.1f; break;       // Scale down in Y
    case 'j': scaleX -= 0.1f; break;       // Scale down in X
    case 'l': scaleX += 0.1f; break;       // Scale up in X
    case 'r': reflectX *= -1; break;       // Reflect about Y-axis
    case 't': reflectY *= -1; break;       // Reflect about X-axis
    case 'x': shearX += 0.1f; break;       // Shear in X direction
    case 'y': shearY += 0.1f; break;       // Shear in Y direction
    }
    glutPostRedisplay();
}

// Setup initial properties
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(1.0, 0.0, 0.0);         // Red triangle
    glPointSize(4.0);
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations with Triangle");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


// g++ exp6.cpp -o exp6 -lGL -lGLU -lglut 
// ./exp6

// Translation: Controlled by w, a, s, d keys.
// Rotation: Controlled by q and e keys.
// Scaling: Controlled by i, k, j, l keys for respective x and y axis.
// Reflection: Controlled by r (about y-axis) and t (about x-axis).
// Shear: Controlled by x and y keys for x-direction and y-direction shearing respectively.