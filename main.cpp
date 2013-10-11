#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/freeglut.h> // make -lglut
//#include <GL/glut.h>
#include "Lapiz.h"
#include <iostream>

using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH = 500, HEIGHT = 250;

// Scene visible area size
GLdouble xLeft = 0.0, xRight = 500.0, yBot = 0.0, yTop = 250.0;

// Scene variables
GLdouble xTriangle = 100.0, yTriangle = 100.0;
GLdouble triangleWidth = 100.0, triangleHeight = 50.0;

// Lápiz
Lapiz lapiz;

void intitGL() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    glPointSize(4.0);
    glLineWidth(2.0);

    // Viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Scene rendering
    glBegin(GL_TRIANGLES);
    glVertex2d(xTriangle, yTriangle);
    glVertex2d(xTriangle + triangleWidth, yTriangle);
    glVertex2d(xTriangle + triangleWidth, yTriangle + triangleHeight);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void resize(int newWidth, int newHeight) {
    //Resize Viewport
    WIDTH = newWidth;
    HEIGHT = newHeight;
    GLdouble RatioViewPort = (float) WIDTH / (float) HEIGHT;
    glViewport(0, 0, WIDTH, HEIGHT);

    //Resize Scene Visible Area 
    //Se actualiza el área visible de la escena
    //para que su ratio coincida con ratioViewPort
    GLdouble SVAWidth = xRight - xLeft;
    GLdouble SVAHeight = yTop - yBot;
    GLdouble SVARatio = SVAWidth / SVAHeight;
    if (SVARatio >= RatioViewPort) {
        // Increase SVAHeight
        GLdouble newHeight = SVAWidth / RatioViewPort;
        GLdouble yMiddle = (yBot + yTop) / 2.0;
        yTop = yMiddle + newHeight / 2.0;
        yBot = yMiddle - newHeight / 2.0;
    } else {
        //Increase SVAWidth
        GLdouble newWidth = SVAHeight*RatioViewPort;
        GLdouble xMiddle = (xLeft + xRight) / 2.0;
        xRight = xMiddle + newWidth / 2.0;
        xLeft = xMiddle - newWidth / 2.0;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void key(unsigned char key, int x, int y) {

    bool need_redisplay = true;

    switch (key) {
        case 27: /* Escape key */
            //continue_in_main_loop = false; // (**)
            glutLeaveMainLoop(); //Freeglut's sentence for stopping glut's main loop (*)
            break;

        case 'd':
            xTriangle += 10.0;
            break;
        case 'a':
            xTriangle -= 10.0;
            break;
        case 'w':
            yTriangle += 10.0;
            break;
        case 's':
            yTriangle -= 10.0;
            break;
        case '+':
            triangleHeight *= 1.1;
            triangleWidth *= 1.1;
            break;
        case '-':
            // Zoom out 0.9
            triangleHeight *= 0.9;
            triangleWidth *= 0.9;
            break;
        default:
            need_redisplay = false;
            break;
    }//switch

    if (need_redisplay)
        glutPostRedisplay();
}

void keySpecial(int key, int x, int y) {
    bool need_redisplay = true;
    /* Para explorar la escena */
    switch (key) {
        case GLUT_KEY_UP:
            yBot += HEIGHT * 0.1;
            yTop += HEIGHT * 0.1;
            break;
        case GLUT_KEY_DOWN:
            yBot -= HEIGHT * 0.1;
            yTop -= HEIGHT * 0.1;
            break;
        case GLUT_KEY_RIGHT:
            xLeft += WIDTH * 0.1;
            xRight += WIDTH * 0.1;
            break;
        case GLUT_KEY_LEFT:
            xLeft -= WIDTH * 0.1;
            xRight -= WIDTH * 0.1;
            break;

        default:
            need_redisplay = false;
            break;
    }//switch

    if (need_redisplay) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(xLeft, xRight, yBot, yTop);
        glutPostRedisplay();

    }
}

/*void glutMainLoop(){

}*/

int main(int argc, char *argv[]) {
    cout << "Starting console..." << endl;

    int my_window; //my window's identifier

    //Initialization
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(140, 140);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInit(&argc, argv);

    //Window construction
    my_window = glutCreateWindow("Freeglut 2D-project");

    //Callback registration
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutSpecialFunc(keySpecial);
    glutDisplayFunc(display);

    //OpenGL basic setting
    intitGL();
    

    // Freeglut's main loop can be stopped executing (**)
    //while ( continue_in_main_loop )
    //  glutMainLoopEvent();

    // Classic glut's main loop can be stopped after X-closing the window,
    // using the following freeglut's setting (*)
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    // Classic glut's main loop can be stopped in freeglut using (*)
    glutMainLoop();

    // We would never reach this point using classic glut
    system("PAUSE");

    return 0;
}