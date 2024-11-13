#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
using namespace std;

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

struct Color getPixelColor(int x, int y) {
    struct Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(int x, int y, struct Color color) {
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void flood(int x, int y, struct Color old_col, struct Color new_col) {
    struct Color color = getPixelColor(x, y);

    // Check if current pixel is old color and not the new color
    if ((color.r == new_col.r && color.g == new_col.g && color.b == new_col.b) ||
        (color.r != old_col.r || color.g != old_col.g || color.b != old_col.b))
        return;

    // Set the pixel to the new color
    setPixelColor(x, y, new_col);

    // Recursively call flood fill for 4-connected pixels
    flood(x + 1, y, old_col, new_col); // Right
    flood(x - 1, y, old_col, new_col); // Left
    flood(x, y + 1, old_col, new_col); // Up
    flood(x, y - 1, old_col, new_col); // Down
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

void createLShape(void) {
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the vertical part of the "L" shape
    draw_line(100, 100, 100, 400);
    draw_line(100, 150, 400, 400);
    draw_line(150, 150, 150, 400);
    draw_line(100, 150, 100, 100);

    // Draw the horizontal part of the "L" shape
    draw_line(150, 400, 100, 100);
    draw_line(400, 400, 100, 150);
    draw_line(150, 400, 150, 150);

    // Set up colors for flood fill
    struct Color old_col = {1.0, 1.0, 1.0};  // White background
    struct Color new_col = {0.0, 0.0, 0.0};  // Black fill color

    // Start flood fill inside the "L" shape
    flood(120, 120, old_col, new_col);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flood Fill L Shape");
    glutDisplayFunc(createLShape);
    Init();
    glutMainLoop();
}