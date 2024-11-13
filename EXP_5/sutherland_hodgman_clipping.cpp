#include <GL/glut.h>
#include <iostream>
#include <vector>

struct Point {
    float x, y;
};

std::vector<Point> polygon;  // The polygon vertices
std::vector<Point> clippedPolygon;  // Clipped polygon vertices

// Define clipping window boundaries
float xmin = 100, ymin = 100, xmax = 400, ymax = 400;

// Function to plot a point on the screen
void plotPoint(Point p) {
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}

// Function to draw a polygon
void drawPolygon(const std::vector<Point>& poly) {
    glBegin(GL_POLYGON);
    for (const auto& p : poly) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    glFlush();
}

// Function to draw the clipping rectangle
void drawClippingWindow() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    glFlush();
}

// Compute intersection point between the line segment (p1, p2) and the edge
Point computeIntersection(Point p1, Point p2, float xEdge, float yEdge, bool horizontal) {
    Point intersection;
    if (horizontal) {  // Clipping with a horizontal edge (top/bottom)
        intersection.x = p1.x + (p2.x - p1.x) * (yEdge - p1.y) / (p2.y - p1.y);
        intersection.y = yEdge;
    } else {  // Clipping with a vertical edge (left/right)
        intersection.y = p1.y + (p2.y - p1.y) * (xEdge - p1.x) / (p2.x - p1.x);
        intersection.x = xEdge;
    }
    return intersection;
}

// Sutherland-Hodgman polygon clipping algorithm
std::vector<Point> sutherlandHodgmanClip(const std::vector<Point>& polygon, float xmin, float ymin, float xmax, float ymax) {
    std::vector<Point> clippedPolygon = polygon;

    // Clipping against the left edge
    std::vector<Point> tempPolygon;
    for (size_t i = 0; i < clippedPolygon.size(); ++i) {
        Point p1 = clippedPolygon[i];
        Point p2 = clippedPolygon[(i + 1) % clippedPolygon.size()];  // Wrap around to the first point

        if (p2.x >= xmin) {  // If p2 is inside the window
            if (p1.x >= xmin) {
                tempPolygon.push_back(p2);  // Add p2 if it's inside
            } else {
                tempPolygon.push_back(computeIntersection(p1, p2, xmin, 0, false));  // Add intersection point
                tempPolygon.push_back(p2);
            }
        } else if (p1.x >= xmin) {
            tempPolygon.push_back(computeIntersection(p1, p2, xmin, 0, false));  // Add intersection point
        }
    }
    clippedPolygon = tempPolygon;

    // Clipping against the right edge
    tempPolygon.clear();
    for (size_t i = 0; i < clippedPolygon.size(); ++i) {
        Point p1 = clippedPolygon[i];
        Point p2 = clippedPolygon[(i + 1) % clippedPolygon.size()];

        if (p2.x <= xmax) {  // If p2 is inside the window
            if (p1.x <= xmax) {
                tempPolygon.push_back(p2);  // Add p2 if it's inside
            } else {
                tempPolygon.push_back(computeIntersection(p1, p2, xmax, 0, false));  // Add intersection point
                tempPolygon.push_back(p2);
            }
        } else if (p1.x <= xmax) {
            tempPolygon.push_back(computeIntersection(p1, p2, xmax, 0, false));  // Add intersection point
        }
    }
    clippedPolygon = tempPolygon;

    // Clipping against the bottom edge
    tempPolygon.clear();
    for (size_t i = 0; i < clippedPolygon.size(); ++i) {
        Point p1 = clippedPolygon[i];
        Point p2 = clippedPolygon[(i + 1) % clippedPolygon.size()];

        if (p2.y >= ymin) {  // If p2 is inside the window
            if (p1.y >= ymin) {
                tempPolygon.push_back(p2);  // Add p2 if it's inside
            } else {
                tempPolygon.push_back(computeIntersection(p1, p2, ymin, 0, true));  // Add intersection point
                tempPolygon.push_back(p2);
            }
        } else if (p1.y >= ymin) {
            tempPolygon.push_back(computeIntersection(p1, p2, ymin, 0, true));  // Add intersection point
        }
    }
    clippedPolygon = tempPolygon;

    // Clipping against the top edge
    tempPolygon.clear();
    for (size_t i = 0; i < clippedPolygon.size(); ++i) {
        Point p1 = clippedPolygon[i];
        Point p2 = clippedPolygon[(i + 1) % clippedPolygon.size()];

        if (p2.y <= ymax) {  // If p2 is inside the window
            if (p1.y <= ymax) {
                tempPolygon.push_back(p2);  // Add p2 if it's inside
            } else {
                tempPolygon.push_back(computeIntersection(p1, p2, ymax, 0, true));  // Add intersection point
                tempPolygon.push_back(p2);
            }
        } else if (p1.y <= ymax) {
            tempPolygon.push_back(computeIntersection(p1, p2, ymax, 0, true));  // Add intersection point
        }
    }
    clippedPolygon = tempPolygon;

    return clippedPolygon;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(0.0, 0.0, 0.0);  // Black for clipping window
    drawClippingWindow();

    // Draw the original polygon in blue
    glColor3f(0.0, 0.0, 1.0);  // Blue for original polygon
    drawPolygon(polygon);

    // Apply the Sutherland-Hodgman polygon clipping
    clippedPolygon = sutherlandHodgmanClip(polygon, xmin, ymin, xmax, ymax);

    // Draw the clipped polygon in red
    glColor3f(1.0, 0.0, 0.0);  // Red for clipped polygon
    drawPolygon(clippedPolygon);

    glFlush();
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set 2D orthogonal projection
}

int main(int argc, char** argv) {
    // Input the polygon points
    int n;
    std::cout << "Enter number of points in polygon: ";
    std::cin >> n;
    polygon.clear();
    std::cout << "Enter the polygon points (x, y): \n";
    for (int i = 0; i < n; ++i) {
        Point p;
        std::cin >> p.x >> p.y;
        polygon.push_back(p);
    }

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");

    initOpenGL();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
// g++ sutherland_hodgman_clipping.cpp -o sutherland_hodgman_clipping -lGL -lGLU -lglut
// ./sutherland_hodgman_clipping
