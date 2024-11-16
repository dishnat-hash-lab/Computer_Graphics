#include <GL/glut.h> 
#include <iostream> 
#include <vector> 
using namespace std; 
struct Point { 
    float x, y; 
};
struct ClipWindow { 
    float xmin, ymin, xmax, ymax; 
}; 
vector<Point> polygon; 
vector<Point> clippedPolygon; 
ClipWindow window; 
bool isInside(Point p, int edge, ClipWindow window) { 
    switch (edge) { 
        case 0: return p.x >= window.xmin; // Left edge 
        case 1: return p.x <= window.xmax; // Right edge 
        case 2: return p.y >= window.ymin; // Bottom edge 
        case 3: return p.y <= window.ymax; // Top edge 
    } 
    return false; 
} 
Point getIntersection(Point s, Point p, int edge, ClipWindow window) { 
    Point i; 
    float m; 
    if (p.x != s.x) m = (p.y - s.y) / (p.x - s.x); // Slope of the edge 
    switch (edge) { 
        case 0: // Left 
            i.x = window.xmin; 
            i.y = s.y + m * (window.xmin - s.x); 
            break; 
        case 1: // Right 
            i.x = window.xmax; 
            i.y = s.y + m * (window.xmax - s.x); 
            break; 
        case 2: // Bottom 
            i.y = window.ymin; 
            i.x = s.x + (window.ymin - s.y) / m; 
            break; 
        case 3: // Top 
            i.y = window.ymax; 
            i.x = s.x + (window.ymax - s.y) / m; 
            break; 
    } 
    return i; 
} 
vector<Point> sutherlandHodgmanClipping(vector<Point> polygon, 
ClipWindow window) { 
    vector<Point> outputList = polygon; 
Point s, p, i; 
    for (int edge = 0; edge < 4; edge++) { 
        vector<Point> inputList = outputList; 
        outputList.clear(); 
        if (inputList.empty()) return outputList; 
        s = inputList[inputList.size() - 1];  
        for (int j = 0; j < inputList.size(); j++) { 
            p = inputList[j]; 
            if (isInside(p, edge, window)) { 
                if (!isInside(s, edge, window)) { 
                    i = getIntersection(s, p, edge, window); 
                    outputList.push_back(i); 
                } 
                outputList.push_back(p); 
            } else if (isInside(s, edge, window)) { 
                i = getIntersection(s, p, edge, window); 
                outputList.push_back(i); 
            } 
            s = p; 
        } 
    } 
 
    return outputList; 
} 
void drawPolygon(const vector<Point>& polygon) { 
    glBegin(GL_LINE_LOOP); 
    for (int i = 0; i < polygon.size(); i++) { 
        glVertex2f(polygon[i].x, polygon[i].y); 
    } 
    glEnd(); 
} 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(1.0f, 0.0f, 0.0f); 
    drawPolygon(polygon); 
    glColor3f(0.0f, 0.0f, 1.0f); 
    glBegin(GL_LINE_LOOP); 
        glVertex2f(window.xmin, window.ymin); 
        glVertex2f(window.xmax, window.ymin); 
        glVertex2f(window.xmax, window.ymax); 
        glVertex2f(window.xmin, window.ymax); 
    glEnd(); 
    glColor3f(0.0f, 1.0f, 0.0f); 
    drawPolygon(clippedPolygon); 
 
    glFlush(); 
} 
 
// Initialize OpenGL settings 
void init() { 
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glColor3f(1.0f, 0.0f, 0.0f); 
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Define the orthographic projection 
} 
int main(int argc, char** argv) { 
    int n; 
    cout << "Enter the number of vertices of the polygon: "; 
    cin >> n; 
    cout << "Enter the coordinates of the polygon (x, y):\n"; 
    for (int i = 0; i < n; i++) { 
        Point p; 
        cout << "Vertex " << i + 1 << ": "; 
        cin >> p.x >> p.y; 
        polygon.push_back(p); 
    } 
    cout << "Enter the clipping window (xmin, ymin, xmax, ymax):\n"; 
    cin >> window.xmin >> window.ymin >> window.xmax >> window.ymax; 
    clippedPolygon = sutherlandHodgmanClipping(polygon, window); 
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(500, 500); 
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping"); 
    init();  
    glutDisplayFunc(display); 
    glutMainLoop(); 
 
    return 0; 
}

// g++ sutherland_hodgman_clipping.cpp -o sutherland_hodgman_clipping -lGL -lGLU -lglut
// ./sutherland_hodgman_clipping
