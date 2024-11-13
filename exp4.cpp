#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Point {
    int x, y;
};

// Define the polygon as a vector of Points
std::vector<Point> polygon;
int numVertices;

// Helper function to check if a point is inside the polygon (for the scanline algorithm)
bool inside(int x, int y, std::vector<Point>& polygon) {
    int i, j, n = polygon.size();
    bool oddNodes = false;
    for (i = 0, j = n - 1; i < n; j = i++) {
        if ((polygon[i].y < y && polygon[j].y >= y || polygon[j].y < y && polygon[i].y >= y) && 
            (polygon[i].x <= x || polygon[j].x <= x)) {
            if (polygon[i].x + (y - polygon[i].y) / (float)(polygon[j].y - polygon[i].y) * (polygon[j].x - polygon[i].x) < x) {
                oddNodes = !oddNodes;
            }
        }
    }
    return oddNodes;
}

void plotPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Function to fill the polygon using Scan Line Algorithm
void scanLineFill() {
    int yMin = INT_MAX, yMax = INT_MIN;

    // Find the bounding box of the polygon (min and max Y values)
    for (int i = 0; i < numVertices; i++) {
        if (polygon[i].y < yMin) yMin = polygon[i].y;
        if (polygon[i].y > yMax) yMax = polygon[i].y;
    }

    // Scan each scanline from yMin to yMax
    for (int y = yMin; y <= yMax; y++) {
        std::vector<int> intersections;
        
        // Find all the x-coordinates where the scanline intersects the polygon edges
        for (int i = 0; i < numVertices; i++) {
            int x1 = polygon[i].x, y1 = polygon[i].y;
            int x2 = polygon[(i + 1) % numVertices].x, y2 = polygon[(i + 1) % numVertices].y;

            // Check if the scanline crosses this edge
            if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
                // Find the x-coordinate of the intersection
                int xIntersect = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                intersections.push_back(xIntersect);
            }
        }

        // Sort the intersections in increasing order
        std::sort(intersections.begin(), intersections.end());

        // Fill the pixels between each pair of intersections
        for (int i = 0; i < intersections.size(); i += 2) {
            int xStart = intersections[i];
            int xEnd = intersections[i + 1];
            for (int x = xStart; x <= xEnd; x++) {
                plotPixel(x, y);  // Fill pixel
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the color to black
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Draw the polygon edges
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(polygon[i].x, polygon[i].y);
    }
    glEnd();
    
    // Fill the polygon using the scanline algorithm
    scanLineFill();
    
    glFlush();
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set the 2D orthogonal view
}

int main(int argc, char** argv) {
    std::cout << "Enter number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the coordinates of the vertices:\n";
    for (int i = 0; i < numVertices; i++) {
        Point p;
        std::cin >> p.x >> p.y;
        polygon.push_back(p);
    }

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single buffer and RGB color mode
    glutInitWindowSize(500, 500); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Scan Line Polygon Filling");

    initOpenGL(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display callback function

    glutMainLoop(); // Enter the GLUT event loop

    return 0;
}


// g++ exp4.cpp -o exp4 -lGL -lGLU -lglut
// ./exp4