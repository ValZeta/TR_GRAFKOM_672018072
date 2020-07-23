#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "LoadImageBMP.h"

int w = 1024, h = 1024;
static float ypoz = 0, zpoz = 0, xpoz = 0, a = 0, b = 0, c = -10;
static float xScale = 1, yScale = 1, zScale = 1;

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;

bool toUp = true;
float y_pos = -5.0f;
float deltay = 0.012f;
bool anim = true;

GLuint _textureID;
GLuint _textureID1;
GLuint _textureID2;
GLuint _textureID3;
GLuint _textureID4;
GLuint _textureID5;

GLUquadric* qobj;

void banyu() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-500.0f, y_pos, 500.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-500.0f, y_pos, -500.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(500.0f, y_pos, -500.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(500.0f, y_pos, 500.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    //glutSwapBuffers();
}

void kapal_kecil() {
    //kanan
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(5.0f, -5.0f, 30.f);
    glVertex3f(-5.f, -5.f, 30.f);
    glVertex3f(-7.f, -2.f, 30.f);
    glVertex3f(7.f, -2.f, 30.f);
    glEnd();
    //kiri
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(5.0f, -5.0f, 25.f);
    glVertex3f(-5.f, -5.f, 25.f);
    glVertex3f(-7.f, -2.f, 25.f);
    glVertex3f(7.f, -2.f, 25.f);
    glEnd();
    //bawah
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(5.0f, -5.f, 30.f);
    glVertex3f(-5.f, -5.f, 30.f);
    glVertex3f(-5.f, -5.f, 25.f);
    glVertex3f(5.f, -5.f, 25.f);
    glEnd();
    //depan
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(5.0f, -5.0f, 30.f);
    glVertex3f(5.f, -5.f, 25.f);
    glVertex3f(7.f, -2.f, 25.f);
    glVertex3f(7.f, -2.f, 30.f);
    glEnd();
    //belakang
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-5.0f, -5.0f, 30.f);
    glVertex3f(-5.f, -5.f, 25.f);
    glVertex3f(-7.f, -2.f, 25.f);
    glVertex3f(-7.f, -2.f, 30.f);
    glEnd();
    //atas
    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(7.0f, -2.0f, 30.f);
    glVertex3f(-7.f, -2.f, 30.f);
    glVertex3f(-7.f, -2.f, 25.f);
    glVertex3f(7.f, -2.f, 25.f);
    glEnd();
    //tiang
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 1, 1);
    glTranslatef(0, 2, 27.5);
    glScalef(4, 100, 4);
    glutSolidCube(0.1);
    glPopMatrix();
    //bendera
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 1, 1);
    glTranslatef(1.9, 2, 27.5);
    glScalef(5, 5, 0.4);
    glutSolidTetrahedron();
    glPopMatrix();
    //bendera kecil
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0, 0);
    glTranslatef(-1.2, 5, 27.5);
    glScalef(-3, 2, 0.4);
    glutSolidTetrahedron();
    glPopMatrix();
}

void ban_kanan_belakang() {
    for (float i = 0; i < 75; i += 3) {
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(1, 0, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-13 + i, 22, -12.5);
        glScalef(1, 1, 1);
        glutSolidTorus(0.5, 1, 10, 10);
        glPopMatrix();
    }
}

void ban_kiri_belakang() {
    for (float i = 0; i < 75; i += 3) {
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(1, 0, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-13 + i, 22, 12.5);
        glScalef(1, 1, 1);
        glutSolidTorus(0.5, 1, 10, 10);
        glPopMatrix();
    }
}

void kursi_kanan() {
    float z = 11;
    for (float x = 0; x > -10; x -= 1.5) {
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glTranslatef(-5.6 + x, 17.4, -2.5 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glTranslatef(-5.6 + x, 17.4, -1.4 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glTranslatef(-4.5 + x, 17.4, -2.5 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glTranslatef(-4.5 + x, 17.4, -1.4 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        //papan
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.5, 0.3, 0);
        glTranslatef(-5 + x, 17.8, -2 + z);
        glScalef(13.3, 1, 13.3);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.5, 0.3, 0);
        glTranslatef(-5 + x, 18.4, -1.4 + z);
        glScalef(13.3, 13.3, 0.6);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
    }
}

void kursi_kiri() {
    float z = 11;
    for (float x = 10; x < 20; x += 1.5) {
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glRotatef(180, 0, 1, 0);
        glTranslatef(-5.6 + x, 17.4, -2.5 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glRotatef(180, 0, 1, 0);
        glTranslatef(-5.6 + x, 17.4, -1.4 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glRotatef(180, 0, 1, 0);
        glTranslatef(-4.5 + x, 17.4, -2.5 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.2, 0.1, 0);
        glRotatef(180, 0, 1, 0);
        glTranslatef(-4.5 + x, 17.4, -1.4 + z);
        glScalef(1, 8.3, 1);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        //papan
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.5, 0.3, 0);
        glRotatef(180, 0, 1, 0);
        glTranslatef(-5 + x, 17.8, -2 + z);
        glScalef(13.3, 1, 13.3);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.5, 0.3, 0);
        glRotatef(180, 0, 1, 0);
        glTranslatef(-5 + x, 18.4, -1.4 + z);
        glScalef(13.3, 13.3, 0.6);
        glutSolidCube(0.1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
    }
}

void cerobong() {
    glColor3f(0.5, 0.5, 0.5);
    qobj = gluNewQuadric();
    glRotatef(90, 1, 0, 0);
    glTranslatef(-25, 0, -25);
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, 2.0, 2.0, 10.0, 45, 50);
}
void bulan() {
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(0, 60, -50);
    glScalef(1, 1, 1);
    glutSolidSphere(5, 30, 20);
    glPopMatrix();
}

void atasan() {
    glColor3f(1.0f, 1.0f, 1.0f);
    //kanan_samping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-39.0f, 5.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.0f, 15.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 15.0f, 11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(35.0f, 5.0f, 11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kiri_belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-39.0f, 5.0f, -11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.0f, 15.0f, -11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 15.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(35.0f, 5.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-39.0f, 5.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-35.0f, 15.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-35.0f, 15.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-39.0f, 5.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(35.0f, 5.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(20.0f, 15.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 15.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(35.0f, 5.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //atas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.0f, 15.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(25.0f, 15.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(25.0f, 15.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-35.0f, 15.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void tingkat2() {
    glColor3f(1.0f, 1.0f, 1.0f);
    //kanan_samping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.0f, 15.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-34.0f, 17.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 17.0f, 11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(25.0f, 15.0f, 11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kiri_belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.0f, 15.0f, -11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-34.0f, 17.0f, -11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 17.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(25.0f, 15.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-35.0f, 15.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-34.0f, 17.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-34.0f, 17.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-35.0f, 15.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(25.0f, 15.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(20.0f, 17.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 17.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(25.0f, 15.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //atas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-34.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(20.0f, 17.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20.0f, 17.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-34.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void tingkat3_depan() {
    glColor3f(1.0f, 1.0f, 1.0f);
    //kanan_samping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20.0f, 17.0f, 11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kiri_belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 17.0f, -11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(20.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(18.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //atas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, 19.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(18.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 19.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void tingkat3_belakang() {
    glColor3f(1.0f, 1.0f, 1.0f);
    //kanan_samping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-32.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-32.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-20.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-18.0f, 17.0f, 11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kiri_belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-32.0f, 17.0f, -11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-32.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-20.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-18.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-32.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-32.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-32.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-32.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-18.0f, 17.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-20.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-20.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-18.0f, 17.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //atas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-32.0f, 19.0f, 11.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-20.0f, 19.0f, 11.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-20.0f, 19.0f, -11.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-32.0f, 19.0f, -11.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void jendela() {
    //jendela tingkat1//
    //kanan
    glColor3f(0.3f, 0.3f, 0.3f);
    for (float x = 0; x <= 54; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-35.0f + x, 14.0f, 11.1f);
        glVertex3f(-35.0f + x, 13.0f, 11.1f);
        glVertex3f(-34.0f + x, 13.0f, 11.1f);
        glVertex3f(-34.0f + x, 14.0f, 11.1f);
        glEnd();
    }
    for (float x = 0; x <= 57; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-35.0f + x, 12.5f, 11.1f);
        glVertex3f(-35.0f + x, 11.5f, 11.1f);
        glVertex3f(-34.0f + x, 11.5f, 11.1f);
        glVertex3f(-34.0f + x, 12.5f, 11.1f);
        glEnd();
    }
    for (float x = 0; x <= 61; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.5f + x, 11.0f, 11.1f);
        glVertex3f(-36.5f + x, 10.0f, 11.1f);
        glVertex3f(-35.5f + x, 10.0f, 11.1f);
        glVertex3f(-35.5f + x, 11.0f, 11.1f);
        glEnd();
    }
    for (float x = 0; x <= 64; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.5f + x, 9.5f, 11.1f);
        glVertex3f(-36.5f + x, 8.5f, 11.1f);
        glVertex3f(-35.5f + x, 8.5f, 11.1f);
        glVertex3f(-35.5f + x, 9.5f, 11.1f);
        glEnd();
    }
    for (float x = 0; x <= 67; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.5f + x, 8.0f, 11.1f);
        glVertex3f(-36.5f + x, 7.0f, 11.1f);
        glVertex3f(-35.5f + x, 7.0f, 11.1f);
        glVertex3f(-35.5f + x, 8.0f, 11.1f);
        glEnd();
    }
    for (float x = 0; x <= 69; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-38.0f + x, 6.5f, 11.1f);
        glVertex3f(-38.0f + x, 5.5f, 11.1f);
        glVertex3f(-37.0f + x, 5.5f, 11.1f);
        glVertex3f(-37.0f + x, 6.5f, 11.1f);
        glEnd();
    }
    //kiri
    for (float x = 0; x <= 54; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-35.0f + x, 14.0f, -11.1f);
        glVertex3f(-35.0f + x, 13.0f, -11.1f);
        glVertex3f(-34.0f + x, 13.0f, -11.1f);
        glVertex3f(-34.0f + x, 14.0f, -11.1f);
        glEnd();
    }
    for (float x = 0; x <= 57; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-35.0f + x, 12.5f, -11.1f);
        glVertex3f(-35.0f + x, 11.5f, -11.1f);
        glVertex3f(-34.0f + x, 11.5f, -11.1f);
        glVertex3f(-34.0f + x, 12.5f, -11.1f);
        glEnd();
    }
    for (float x = 0; x <= 61; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.5f + x, 11.0f, -11.1f);
        glVertex3f(-36.5f + x, 10.0f, -11.1f);
        glVertex3f(-35.5f + x, 10.0f, -11.1f);
        glVertex3f(-35.5f + x, 11.0f, -11.1f);
        glEnd();
    }
    for (float x = 0; x <= 64; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.5f + x, 9.5f, -11.1f);
        glVertex3f(-36.5f + x, 8.5f, -11.1f);
        glVertex3f(-35.5f + x, 8.5f, -11.1f);
        glVertex3f(-35.5f + x, 9.5f, -11.1f);
        glEnd();
    }
    for (float x = 0; x <= 67; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.5f + x, 8.0f, -11.1f);
        glVertex3f(-36.5f + x, 7.0f, -11.1f);
        glVertex3f(-35.5f + x, 7.0f, -11.1f);
        glVertex3f(-35.5f + x, 8.0f, -11.1f);
        glEnd();
    }
    for (float x = 0; x <= 69; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-38.0f + x, 6.5f, -11.1f);
        glVertex3f(-38.0f + x, 5.5f, -11.1f);
        glVertex3f(-37.0f + x, 5.5f, -11.1f);
        glVertex3f(-37.0f + x, 6.5f, -11.1f);
        glEnd();
    }
    //depan
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(21.6f, 14.0f, a);
        glVertex3f(23.2f, 13.0f, a);
        glVertex3f(23.2f, 13.0f, a - 1);
        glVertex3f(21.6f, 14.0f, a - 1);
        glEnd();
    }
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(24.8f, 12.0f, a);
        glVertex3f(26.3f, 11.0f, a);
        glVertex3f(26.3f, 11.0f, a - 1);
        glVertex3f(24.8f, 12.0f, a - 1);
        glEnd();
    }
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(27.8f, 10.0f, a);
        glVertex3f(29.4f, 9.0f, a);
        glVertex3f(29.4f, 9.0f, a - 1);
        glVertex3f(27.8f, 10.0f, a - 1);
        glEnd();
    }

    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(30.8f, 8.0f, a);
        glVertex3f(32.4f, 7.0f, a);
        glVertex3f(32.4f, 7.0f, a - 1);
        glVertex3f(30.8f, 8.0f, a - 1);
        glEnd();
    }
    //belakang
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-35.9f, 13.0f, a);
        glVertex3f(-35.5f, 14.0f, a);
        glVertex3f(-35.5f, 14.0f, a - 1);
        glVertex3f(-35.9f, 13.0f, a - 1);
        glEnd();
    }
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-36.7f, 11.0f, a);
        glVertex3f(-36.2f, 12.0f, a);
        glVertex3f(-36.2f, 12.0f, a - 1);
        glVertex3f(-36.7f, 11.0f, a - 1);
        glEnd();
    }
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-37.5f, 9.0f, a);
        glVertex3f(-37.0f, 10.0f, a);
        glVertex3f(-37.0f, 10.0f, a - 1);
        glVertex3f(-37.5f, 9.0f, a - 1);
        glEnd();
    }
    for (float a = 10.5; a >= -10; a -= 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-38.3f, 7.0f, a);
        glVertex3f(-37.8f, 8.0f, a);
        glVertex3f(-37.8f, 8.0f, a - 1);
        glVertex3f(-38.3f, 7.0f, a - 1);
        glEnd();
    }
    //jendela tingkat 2
    //jendela depan
    glBegin(GL_QUADS);
    glVertex3f(24.2f, 15.5f, 10.0f);
    glVertex3f(21.2f, 16.7f, 10.0f);
    glVertex3f(21.2f, 16.7f, -10.0f);
    glVertex3f(24.2f, 15.5f, -10.0f);
    glEnd();
    //jendela belakang
    glBegin(GL_QUADS);
    glVertex3f(-35.0f, 15.3f, 10.0f);
    glVertex3f(-34.2f, 16.7f, 10.0f);
    glVertex3f(-34.2f, 16.7f, -10.0f);
    glVertex3f(-35.0f, 15.3f, -10.0f);
    glEnd();
    //kanan
    for (float x = 0; x <= 54; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-34.0f + x, 15.3f, 11.1f);
        glVertex3f(-34.0f + x, 16.7f, 11.1f);
        glVertex3f(-33.0f + x, 16.7f, 11.1f);
        glVertex3f(-33.0f + x, 15.3f, 11.1f);
        glEnd();
    }
    //kiri
    for (float x = 0; x <= 54; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(-34.0f + x, 15.3f, -11.1f);
        glVertex3f(-34.0f + x, 16.7f, -11.1f);
        glVertex3f(-33.0f + x, 16.7f, -11.1f);
        glVertex3f(-33.0f + x, 15.3f, -11.1f);
        glEnd();
    }
    //tingkat 3 depan //
    //depan
    glBegin(GL_QUADS);
    glVertex3f(19.8f, 17.4f, 10.0f);
    glVertex3f(18.6f, 18.6f, 10.0f);
    glVertex3f(18.6f, 18.6f, -10.0f);
    glVertex3f(19.8f, 17.4f, -10.0f);
    glEnd();
    //kanan
    for (float x = 0; x <= 16; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(1.5f + x, 17.3f, 11.1f);
        glVertex3f(1.5f + x, 18.7f, 11.1f);
        glVertex3f(2.5f + x, 18.7f, 11.1f);
        glVertex3f(2.5f + x, 17.3f, 11.1f);
        glEnd();
    }
    //kiri
    for (float x = 0; x <= 16; x += 1.5) {
        glBegin(GL_POLYGON);
        glVertex3f(1.5f + x, 17.3f, -11.1f);
        glVertex3f(1.5f + x, 18.7f, -11.1f);
        glVertex3f(2.5f + x, 18.7f, -11.1f);
        glVertex3f(2.5f + x, 17.3f, -11.1f);
        glEnd();
    }
    //jendela tingkat 3
    //jendela kanan
    glBegin(GL_QUADS);
    glVertex3f(-31.0f, 17.4f, 11.1f);
    glVertex3f(-31.0f, 18.6f, 11.1f);
    glVertex3f(-20.5f, 18.6f, 11.1f);
    glVertex3f(-19.0f, 17.4f, 11.1f);
    glEnd();
    //jendela kiri
    glBegin(GL_QUADS);
    glVertex3f(-31.0f, 17.4f, -11.1f);
    glVertex3f(-31.0f, 18.6f, -11.1f);
    glVertex3f(-20.5f, 18.6f, -11.1f);
    glVertex3f(-19.0f, 17.4f, -11.1f);
    glEnd();
    //jendela belakang
    glBegin(GL_QUADS);
    glVertex3f(-32.1f, 17.4f, 10.0f);
    glVertex3f(-32.1f, 18.6f, 10.0f);
    glVertex3f(-32.1f, 18.6f, -10.0f);
    glVertex3f(-32.1f, 17.4f, -10.0f);
    glEnd();
}

void kolam_renang() {
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(-10.0f, 17.0f, 0.0f);
    glScalef(100, 5, 80);
    glutSolidCube(0.1);
    glPopMatrix();
}

void pagar() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    //kanan
    glVertex3d(-40.0f, 6.0f, 12.0f);
    glVertex3d(40.0f, 6.0f, 12.0f);

    for (float a = -39; a <= 39; a += 1) {
        glVertex3d(a, 6.0f, 12.0f);
        glVertex3d(a, 5.0f, 12.0f);
    }
    //kanan depan
    glVertex3d(40.0f, 6.0f, 12.0f);
    glVertex3d(60.0f, 6.0f, 0.0f);
    float xa = 40;
    for (float a = 12; a >= 0; a -= 1) {
        glVertex3d(xa, 6.0f, a);
        glVertex3d(xa, 5.0f, a);
        xa += 1.65;
    }

    //kiri depan
    glVertex3d(40.0f, 6.0f, -12.0f);
    glVertex3d(60.0f, 6.0f, 0.0f);
    float xb = 40;
    for (float a = -12; a <= 0; a += 1) {
        glVertex3d(xb, 6.0f, a);
        glVertex3d(xb, 5.0f, a);
        xb += 1.65;
    }
    //kiri
    glVertex3d(-40.0f, 6.0f, -12.0f);
    glVertex3d(40.0f, 6.0f, -12.0f);

    for (float a = -39; a <= 39; a += 1) {
        glVertex3d(a, 6.0f, -12.0f);
        glVertex3d(a, 5.0f, -12.0f);
    }
    //belakang
    glVertex3d(-40.0f, 6.0f, 12.0f);
    glVertex3d(-40.0f, 6.0f, -12.0f);

    for (float a = -12; a <= 12; a += 1) {
        glVertex3d(-40.0f, 6.0f, a);
        glVertex3d(-40.0f, 5.0f, a);
    }

    glEnd();
}

void geladak() {
    //kanan_belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-45.0f, -5.0f, 12.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0f, 5.0f, 12.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(40.0f, 5.0f, 12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20.0f, -5.0f, 12.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kiri_belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-45.0f, -5.0f, -12.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0f, 5.0f, -12.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(40.0f, 5.0f, -12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20.0f, -5.0f, -12.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //belakang
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-45.0f, -5.0f, 12.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0f, 5.0f, 12.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-40.0f, 5.0f, -12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-45.0f, -5.0f, -12.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kanan_depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(40.0f, 5.0f, 12.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(20.0f, -5.0f, 12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -5.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(60.0f, 5.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //kiri_depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(40.0f, 5.0f, -12.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(20.0f, -5.0f, -12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50.0f, -5.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(60.0f, 5.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //atas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.9f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-40.0f, 5.0f, 12.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(40.0f, 5.0f, 12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(40.0f, 5.0f, -12.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-40.0f, 5.0f, -12.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(40.0f, 5.0f, 12.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(40.0f, 5.0f, -12.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(60.0f, 5.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //bawah
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.9f, 0.9f);
    glVertex3f(-45.0f, -5.0f, 12.0f);
    glVertex3f(20.0f, -5.0f, 12.0f);
    glVertex3f(20.0f, -5.0f, -12.0f);
    glVertex3f(-45.0f, -5.0f, -12.0f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(20.0f, -5.0f, 12.0f);
    glVertex3f(20.0f, -5.0f, -12.0f);
    glVertex3f(50.0f, -5.0f, 0.0f);
    glEnd();
}

void idle() {
    if (!mouseDown)
    {
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y) {
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glutPostRedisplay();
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        xScale += 0.1;
        yScale += 0.1;
        zScale += 0.1;
        break;
    case 's':
        xScale -= 0.1;
        yScale -= 0.1;
        zScale -= 0.1;
        break;
    case 'x': // X axis
        xpoz = xpoz + 5;
        if (xpoz > 360) xpoz = 0;
        glutPostRedisplay();
        break;
    case 'y': // Y axis
        ypoz = ypoz + 5;
        if (ypoz > 360) ypoz = 0;
        glutPostRedisplay();
        break;
    case 'z': // Z axis
        zpoz = zpoz + 1;
        if (zpoz > 360) zpoz = 0;
        glutPostRedisplay();
        break;
    case 'q': // Zoom in
        c = c + 1;
        glutPostRedisplay();
        break;
    case 'e': // Zoom out
        c = c - 1;
        glutPostRedisplay();
        break;
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        b = b + 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        b = b - 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        a = a - 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        a = a + 1;
        glutPostRedisplay();
        break;
    }
}

void init() {
    float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specularLight[] = { 0.1f, 0.1f, 0.1f, 2.0f };
    float lampPosition[] = { 0.0f, 1.0f, 0.0f, 1.0f };

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    _textureID = loadBMP_custom("C:/Users/Valen/source/repos/TR_GRAFKOM_672018072/TR_GRAFKOM_672018072/texture.bmp");
    _textureID1 = loadBMP_custom("C:/Users/Valen/source/repos/TR_GRAFKOM_672018072/TR_GRAFKOM_672018072/texture1.bmp");
    _textureID2 = loadBMP_custom("C:/Users/Valen/source/repos/TR_GRAFKOM_672018072/TR_GRAFKOM_672018072/texture2.bmp");
    _textureID3 = loadBMP_custom("C:/Users/Valen/source/repos/TR_GRAFKOM_672018072/TR_GRAFKOM_672018072/texture3.bmp");
    _textureID4 = loadBMP_custom("C:/Users/Valen/source/repos/TR_GRAFKOM_672018072/TR_GRAFKOM_672018072/texture4.bmp");
    _textureID5 = loadBMP_custom("C:/Users/Valen/source/repos/TR_GRAFKOM_672018072/TR_GRAFKOM_672018072/texture5.bmp");
    glClearDepth(1.0f);
    glClearDepth(1.0f);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lampPosition);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    return;
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(a, b, c);
    glScalef(xScale, yScale, zScale);
    glRotatef(xpoz, 1, 0, 0);
    glRotatef(ypoz, 0, 1, 0);
    glRotatef(zpoz, 0, 0, 1);

    glScalef(xScale, yScale, zScale);

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    float d1[] = { 0.2, 0.5, 0.8, 1.0 };
    float d2[] = { 0.3, 0.5, 0.6, 1.0 };
    float d3[] = { 0.4, 0.2, 0.2, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d3);

    banyu();
    geladak();
    atasan();
    tingkat2();
    tingkat3_depan();
    tingkat3_belakang();
    jendela();
    kolam_renang();
    pagar();
    kursi_kanan();
    kursi_kiri();
    kapal_kecil();
    bulan();
    cerobong();
    ban_kanan_belakang();
    ban_kiri_belakang();
    glutSwapBuffers();
}

void resize(int w1, int h1) {
    glViewport(0, 0, w1, h1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w1 / (float)h1, 1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    if (anim) {
        if (y_pos < -4.57f && toUp) {
            y_pos += deltay;
        }
        else {
            toUp = false;
        }
        if (y_pos > -5.0f && !toUp) {
            y_pos -= deltay;
        }
        else {
            toUp = true;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w, h);
    glutCreateWindow("TR_GRAFKOM_672018072_672018224_672018239");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(renderScene);
    glutSwapBuffers();
    glutTimerFunc(1, timer, 0);

    init();
    glutMainLoop();
}