/* 
 * File:   Lapiz.cpp
 * Author: furia
 * 
 * Created on 11 de octubre de 2013, 10:29
 */

#include "Lapiz.h"
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>

#define PI 3.14159265
/*
Lapiz& Lapiz::operator=(const Lapiz &l1) {
    return *(new Lapiz(l1.pos[0], l1.pos[1], l1.theta));
}*/

Lapiz::Lapiz() {
    this->pos[0] = 0;
    this->pos[1] = 0;
    this->theta = 0;
    init();
}

/**
 *  Constructor del lapiz.
 * @param x coordenada x donde empieza
 * @param y coordenada y donde empieza
 * @param theta angulo con el que empieza
 */
Lapiz::Lapiz(GLfloat x, GLfloat y, GLfloat theta) {
    this->pos[0] = x;
    this->pos[1] = y;
    this->theta = theta;
    init();
}

Lapiz::~Lapiz() {
}

void Lapiz::init() {
    glBegin(GL_POINT);
    glVertex2fv(pos);
    glEnd();
    glFlush();
}

/**
 * Avanza el lápiz una distancia dada
 * @param dist que se quiere que avance
 */
void Lapiz::avanza(GLfloat dist) {
    /* Almacenamos la vieja posición para poder dibujar la línea de un punto a otro */
    GLfloat vPos[2];
    vPos[0] = this->pos[0];
    vPos[1] = this->pos[1];
    /* Calculamos la nueva posición */
    GLfloat difX, difY;
    /* Transformamos el ángulo a radianes */
    GLfloat a = this->theta / 180.0 * PI;
    difX = cos((double) a) * dist;
    difY = sin((double) a) * dist;
    /* Nueva posición */
    this->pos[0] += difX;
    this->pos[1] += difY;
    /* Dibujamos la línea de la posición anterior a la actual*/
    std::cout << "Dibujando línea de (" << vPos[0] << "," << vPos[1] << ") a (" << pos[0] << "," << pos[1] << ")." << std::endl;
    glBegin(GL_LINES);
    glVertex2fv(vPos);
    glVertex2fv(pos);
    glEnd();
    glFlush();
}

void Lapiz::gira(GLfloat thetaGiro) {
    this->theta += thetaGiro;
    std::cout << "El angulo del lápiz ha cambiado a : " << this->theta << std::endl;
}

void Lapiz::ir(GLfloat x, GLfloat y) {
    /* Calculo la distancia entre los dos puntos por el teorema de Euclides */
    GLfloat dist = sqrt((int) pow((x - this->pos[0]), 2) + pow((y - this->pos[1]), 2));
    /* Calculo el ángulo con el que tiene que encarar el lapiz para llegar al punto objetivo */
    GLfloat a = 1 / sin((y - this->pos[1]) / dist); // En radianes
    this->theta = a * 180.0 / PI; // Pasamos a angulos y cambiamos nuestro angulo
    /* Dibujo la linea con la funcion avanza*/
    this->avanza(dist);
}
