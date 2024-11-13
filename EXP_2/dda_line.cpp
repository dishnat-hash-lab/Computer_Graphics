#include <GL/glut.h>  
#include <iostream>
#include <cmath>

float x1, yy1, x2, yy2;  

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  
    glColor3f(1.0, 1.0, 1.0);  
    glPointSize(2.0); 

    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  
    glMatrixMode(GL_MODELVIEW);  
}

void drawLineEquation() {
    glBegin(GL_LINES);
    glVertex2f(x1, yy1);
    glVertex2f(x2, yy2);
    glEnd();
}

void drawDDA() {
    float dx = x2 - x1;
    float dy = yy2 - yy1;
    int steps = std::max(std::abs(dx), std::abs(dy));  // Determine the number of steps needed
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = yy1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT); 

    
    glColor3f(1.0, 0.0, 0.0);  
    drawLineEquation();

    glColor3f(0.0, 1.0, 0.0);  
    drawDDA();

    glutSwapBuffers();  
}


int main(int argc, char** argv) {
   
    std::cout << "Enter coordinates for the first point (x1 y1): ";
    std::cin >> x1 >> yy1;
    std::cout << "Enter coordinates for the second point (x2 y2): ";
    std::cin >> x2 >> yy2;

    x1 = (x1 - 400) / 400.0;
    yy1 = (yy1 - 300) / 300.0;
    x2 = (x2 - 400) / 400.0;
    yy2 = (yy2 - 300) / 300.0;

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
    glutInitWindowSize(500, 500);  
    glutCreateWindow("Draw Lines with OpenGL"); 
    init();  
    glutDisplayFunc(display);  

    glutMainLoop();  
    return 0;
}


// g++ dda_line.cpp -o dda_line -lGL -lGLU -lglut
// ./dda_line
