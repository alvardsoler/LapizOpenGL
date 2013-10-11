/* 
 * File:   Lapiz.h
 * Author: furia
 *
 * Created on 11 de octubre de 2013, 10:29
 */

#ifndef LAPIZ_H
#define	LAPIZ_H
#include <GL/freeglut.h>

class Lapiz {
public:
    Lapiz();
    Lapiz(GLfloat x, GLfloat y, GLfloat theta);
    virtual ~Lapiz();
  /*  Lapiz& operator=(const Lapiz &l1);*/
    /* Métodos de movimiento */
    void avanza(GLfloat dist);
    void gira(GLfloat thetaGiro);
    void ir(GLfloat x, GLfloat y);
    void init();
private:
    GLfloat pos[2];
    GLfloat theta;

};

#endif	/* LAPIZ_H */

