#include <GL/glut.h>  // Include the GLUT header file

// Function to initialize OpenGL
void initOpenGL() {
    // Set the clear color to green
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // RGBA values for green background
}

// Function to handle rendering
void display() {
    // Clear the window with the current clear color (green)
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers to display the content (since we are using double buffering)
    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Double buffering and RGB color model
    glutInitWindowSize(500, 500);  // Set the window size
    glutInitWindowPosition(100, 100);  // Set the window position on screen
    glutCreateWindow("OpenGL Green Background");  // Create the window with a title

    // Initialize OpenGL
    initOpenGL();

    // Set the display function (this will be called to render the scene)
    glutDisplayFunc(display);

    // Start the main loop of GLUT
    glutMainLoop();

    return 0;
}

// g++ green_window.cpp -o green_window -lGL -lGLU -lglut
// ./green_window
