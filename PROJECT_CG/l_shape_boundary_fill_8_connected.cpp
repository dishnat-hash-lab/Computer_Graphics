#include <GL/glut.h>
#include <iostream>

struct Color {
    float r, g, b;
};

void Init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

Color getPixelColor(int x, int y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(int x, int y, Color color) {
    glColor3f(color.r, color.g, color.b);
    draw_pixel(x, y);
    glFlush();
}

void boundaryFill(int x, int y, Color fillColor, Color boundaryColor) {
    Color currentColor = getPixelColor(x, y);

    // Check if the current pixel is neither the boundary color nor the fill color
    if ((currentColor.r != boundaryColor.r || currentColor.g != boundaryColor.g || currentColor.b != boundaryColor.b) &&
        (currentColor.r != fillColor.r || currentColor.g != fillColor.g || currentColor.b != fillColor.b)) {
        
        setPixelColor(x, y, fillColor);

        // 8-connected recursive calls
        boundaryFill(x + 1, y, fillColor, boundaryColor);   // Right
        boundaryFill(x - 1, y, fillColor, boundaryColor);   // Left
        boundaryFill(x, y + 1, fillColor, boundaryColor);   // Up
        boundaryFill(x, y - 1, fillColor, boundaryColor);   // Down
        boundaryFill(x + 1, y + 1, fillColor, boundaryColor); // Top-right
        boundaryFill(x - 1, y + 1, fillColor, boundaryColor); // Top-left
        boundaryFill(x + 1, y - 1, fillColor, boundaryColor); // Bottom-right
        boundaryFill(x - 1, y - 1, fillColor, boundaryColor); // Bottom-left
    }
}

void draw_line(int x1, int x2, int y1, int y2) {
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (x2 < x1) incx = -1;
    incy = 1;
    if (y2 < y1) incy = -1;
    x = x1; y = y1;
    if (dx > dy) {
        draw_pixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            } else
                e += inc2;
            x += incx;
            draw_pixel(x, y);
        }

    } else {
        draw_pixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            } else
                e += inc2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void createLShape() {
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the boundary for the "L" shape
    glColor3f(1.0, 0.0, 0.0); // Red boundary color
    // Draw the vertical part of the "L" shape
    draw_line(100, 100, 100, 400);
    draw_line(100, 150, 400, 400);
    draw_line(150, 150, 150, 400);
    draw_line(100, 150, 100, 100);

    // Draw the horizontal part of the "L" shape
    draw_line(150, 400, 100, 100);
    draw_line(400, 400, 100, 150);
    draw_line(150, 400, 150, 150);

    // Define boundary and fill colors
    Color boundaryColor = {1.0, 0.0, 0.0}; // Red boundary
    Color fillColor = {0.0, 0.0, 1.0};     // Blue fill color

    // Start boundary fill inside the "L" shape
    boundaryFill(120, 120, fillColor, boundaryColor);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Boundary Fill 8-Connected L Shape");
    glutDisplayFunc(createLShape);
    Init();
    glutMainLoop();
}
