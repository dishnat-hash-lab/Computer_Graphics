#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>

#define NUM_POINTS 5  // Number of control points

// Define control points for the cubic spline (X and Y coordinates)
std::vector<float> X = {-0.8f, -0.4f, 0.0f, 0.4f, 0.8f};
std::vector<float> Y = {0.5f, -0.5f, 1.0f, -1.0f, 0.5f};

// Spline coefficients (a, b, c, d for each segment)
std::vector<float> a, b, c, d;

// Function to compute cubic spline coefficients
void computeCubicSpline() {
    int n = X.size() - 1;

    // Temporary vectors for spline calculation
    std::vector<float> h(n), alpha(n), l(n + 1), mu(n), z(n + 1);

    // Step 1: Calculate the h and alpha arrays
    for (int i = 0; i < n; i++) {
        h[i] = X[i + 1] - X[i];
        if (h[i] == 0) {
            std::cerr << "Error: Two consecutive x-values are identical!" << std::endl;
            exit(1);
        }
        alpha[i] = (3.0f / h[i]) * (Y[i + 1] - Y[i]) - (3.0f / h[i - 1]) * (Y[i] - Y[i - 1]);
    }

    // Step 2: Set up the l, mu, and z arrays
    l[0] = 1.0f;
    mu[0] = 0.0f;
    z[0] = 0.0f;

    for (int i = 1; i < n; i++) {
        l[i] = 2.0f * (X[i + 1] - X[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0f;
    z[n] = 0.0f;
    c[n] = 0.0f;

    // Step 3: Solve for c, b, and d coefficients
    for (int j = n - 1; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (Y[j + 1] - Y[j]) / h[j] - h[j] * (c[j + 1] + 2.0f * c[j]) / 3.0f;
        d[j] = (c[j + 1] - c[j]) / (3.0f * h[j]);
        a[j] = Y[j];
    }
}

// Function to calculate the cubic spline value at a specific x
float splineValue(int i, float x) {
    float dx = x - X[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}

// Function to display the cubic spline
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Step 1: Draw the spline curve by sampling at multiple points
    glColor3f(0.0f, 0.0f, 0.0f);  // Set color for the spline (black)
    glBegin(GL_LINE_STRIP);
    for (float x = X[0]; x <= X[NUM_POINTS - 1]; x += 0.01f) {
        // Find the appropriate spline segment for this x value
        int i = 0;
        while (i < X.size() - 1 && x > X[i + 1]) {
            i++;
        }
        float y = splineValue(i, x);
        glVertex2f(x, y);
    }
    glEnd();

    // Step 2: Draw the control points
    glPointSize(10.0f);  // Set point size for control points
    glBegin(GL_POINTS);
    for (int i = 0; i < X.size(); i++) {
        glVertex2f(X[i], Y[i]);
    }
    glEnd();

    // Step 3: Draw the control polygon (lines connecting control points)
    glColor3f(0.8f, 0.8f, 0.8f);  // Set control polygon color to light gray
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < X.size(); i++) {
        glVertex2f(X[i], Y[i]);
    }
    glEnd();

    glFlush();
}

// OpenGL initialization
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glColor3f(0.0f, 0.0f, 0.0f);           // Set drawing color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f); // Set up orthogonal projection
}

int main(int argc, char** argv) {
    // Compute cubic spline coefficients
    computeCubicSpline();

    // Initialize GLUT and OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cubic Spline Interpolation");
    init();
    
    // Register display callback function
    glutDisplayFunc(display);

    // Enter the GLUT event processing loop
    glutMainLoop();

    return 0;
}

// g++ cubic_spline.cpp -o cubic_spline -lGL -lGLU -lglut
// ./cubic_spline
