#include <GL/glut.h>
#include <iostream>

// Line parameters
float m = 1.0f;  // Slope
float c = 0.0f;  // Y-intercept

// Function to initialize OpenGL settings
void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Set background color (black)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set up 2D orthographic projection
}

// Function to display the line
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    glColor3f(1.0f, 0.0f, 0.0f);  // Set the line color (red)

    glBegin(GL_LINES);

    // Draw the line between two points calculated by the line equation y = mx + c
    float x1 = -1.0f;
    float y1 = m * x1 + c;
    
    float x2 = 1.0f;
    float y2 = m * x2 + c;
    
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();

    glutSwapBuffers();  // Swap buffers to display the rendered image
}

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // Set the viewport to the new window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set up 2D orthographic projection
}

// Main function to set up GLUT and OpenGL
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Use double buffering and RGB color mode
    glutInitWindowSize(500, 500);  // Set initial window size
    glutCreateWindow("Line Drawing: y = mx + c");

    // Initialize OpenGL settings
    initOpenGL();

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Start the main GLUT loop
    glutMainLoop();

    return 0;
}


//compile
// g++ 2a.cpp -o 2a -lGL -lGLU -lglut
//run 
//./2a