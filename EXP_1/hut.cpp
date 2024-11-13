#include <GL/glut.h>
void init() {
    glClearColor(0.0, 1.0, 0.0, 1.0);  
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);  
}

void drawHut() {
    glColor3f(0.7, 0.4, 0.1);  
    glBegin(GL_POLYGON);
    glVertex2f(-5.0, -5.0);
    glVertex2f(5.0, -5.0);
    glVertex2f(5.0, 0.0);
    glVertex2f(-5.0, 0.0);
    glEnd();

    glColor3f(0.9, 0.1, 0.1);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-6.0, 0.0);
    glVertex2f(0.0, 5.0);
    glVertex2f(6.0, 0.0);
    glEnd();

    glColor3f(0.5, 0.3, 0.2);  
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -5.0);
    glVertex2f(1.0, -5.0);
    glVertex2f(1.0, -2.0);
    glVertex2f(-1.0, -2.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  
    drawHut();  
    glFlush();  
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(500, 500);  
    glutInitWindowPosition(100, 100);  
    glutCreateWindow("ANANYA SAINI-Hut Drawing");  
    init();  
    glutDisplayFunc(display);  
    glutMainLoop();  
    return 0;
}

// g++ hut.cpp -o hut -lGL -lGLU -lglut
//./hut