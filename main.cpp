#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include <iostream>
#include <vector>
#include <array>
#include <unistd.h>
#include<windows.h>
#include<mmsystem.h>
#include "BmpLoader.h"

GLUquadric *quad;
using namespace std;

double Txval=0, Tyval=0, Tzval=0, flag1 = 0, flag2=0, flag3=0;
double ex =10, ey=5, ez=280, ux = 0, uy = 1, uz = 0, zx=2, zy=2, zz=1, lx=10, ly=5, lz=0;
double pp = 0, qq = 0, rr = 0;
double windowHeight=960, windowWidth=510;
GLfloat alpha = 0.0, theta = 1, beta= 0.0, axis_x=0.0, axis_y=0.0, axis_z = 0.0;
GLboolean bRotate = false, uRotate = false, zRotate = false;
bool p_state = true, y_state = true, r_state = true;

GLfloat an_y = 90, an_x = 270.0, an_z = 90;

GLfloat orbiterAlpha = -45.0, orbiterTheta = 0.0, testTheta = -45.0, pirateBoatTheta = 0.0, cmOrbiterAlpha = 0.0, cmOrbiterTheta = 0.0, skyDropPos = 0.0 ;
GLboolean fanSwitch = false, door1 = false, orbiterFlag = false, testFlag = true, pirateBoatFlag = false, pirateBoatCheck = false, cmOrbiterFlag = false, skyDropFlag = false, upFlag = true, downFlag1 = true, downFlag2 = false, downFlag3 = false, show = false, day = true, switchOne = false, switchTwo = false, switchThree = false, switchFour = false;
unsigned int ID;
unsigned int ID2[40];

float gari_nore =0.0;
int gari_switch =0;

GLfloat yf = 0, xf = 0;
GLboolean yflag = false, xflag = false;
int mclickb1 = 0, mclickb2 = 0, mclickb3 = 0, mclickb4 = 0, mclickb5 = 0, mclickb6 = 0;
int light0_on = 0, light1_on = 1, light2_on = 1 , light1_c = 0 , light2_c = 0 ;
GLfloat lamp_x[] = {-70, 200};
GLfloat lamp_z[] = {-30, -55};



static GLfloat colors[4][6] =
        {
                {1,0,0, 0.5,0,0}, //red
                {0,1,0, 0,0.5,0}, //green
                {0,0,1, 0,0,0.5}, //blue
                {1,1,0, 0.5,0.5,0} //yellow
        };

static GLfloat v_cube[8][3] =
        {
                {0.0, 0.0, 0.0}, //0
                {0.0, 0.0, 3.0}, //1
                {3.0, 0.0, 3.0}, //2
                {3.0, 0.0, 0.0}, //3
                {0.0, 3.0, 0.0}, //4
                {0.0, 3.0, 3.0}, //5
                {3.0, 3.0, 3.0}, //6
                {3.0, 3.0, 0.0}  //7
        };

static GLubyte quadIndices[6][4] =
        {
                {0, 1, 2, 3}, //bottom
                {4, 5, 6, 7}, //top
                {5, 1, 2, 6}, //front
                {3, 7, 4, 0}, // back
                {2, 3, 7, 6}, //right
                {0, 4, 5,1}  //left
        };


void LoadTexture2(const char*filename,GLint num)
{
    TK_RGBImageRec             *texture1;

    texture1 = tkRGBImageLoad(filename);

    glPixelStorei(GL_UNPACK_ALIGNMENT,   1   );

    glTexImage2D(GL_TEXTURE_2D,         //target
            0,                             //level
            GL_RGB,                     //internalFormat
            texture1->sizeX,             //w
            texture1->sizeY,            //h
            0,                             //border
            GL_RGB, GL_UNSIGNED_BYTE,     //format,type
            texture1->data);            //data

    // Create Texture
    glGenTextures(1, &ID2[num]);
    glBindTexture(GL_TEXTURE_2D, ID2[num]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    //glGenerateMipmap(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 texture1->sizeX, texture1->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

}

void materialProperty()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void matCurve(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambfactor = 1.0, GLfloat specfactor = 1.0, GLfloat shine=50)
{
    glColor3f(1,1,1);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { difX*ambfactor, difY*ambfactor, difZ*ambfactor, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

static void getNormal3p
        (GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere (1.0, 16, 16);
}

void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTorus(innerRadius, outerRadius, nsides, rings);

    //glutSolidTorus(0.5, 10.0, 16, 12);
}

void drawCylinder(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, 1.5, 1.5, 19, 32, 32);

}

static GLfloat v_box[8][3] =
        {
                {0.0, 0.0, 0.0}, //0
                {3.0, 0.0, 0.0}, //1
                {0.0, 0.0, 3.0}, //2
                {3.0, 0.0, 3.0}, //3
                {0.0, 3.0, 0.0}, //4
                {3.0, 3.0, 0.0}, //5
                {0.0, 3.0, 3.0}, //6
                {3.0, 3.0, 3.0}, //7

        };

static GLubyte BoxquadIndices[6][4] =
        {
                {0,2,3,1},
                {0,2,6,4},
                {2,3,7,6},
                {1,3,7,5},
                {1,5,4,0},
                {6,7,5,4}
        };

void drawBox()
{
    materialProperty();
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_box[BoxquadIndices[i][0]][0], v_box[BoxquadIndices[i][0]][1], v_box[BoxquadIndices[i][0]][2],
                    v_box[BoxquadIndices[i][1]][0], v_box[BoxquadIndices[i][1]][1], v_box[BoxquadIndices[i][1]][2],
                    v_box[BoxquadIndices[i][2]][0], v_box[BoxquadIndices[i][2]][1], v_box[BoxquadIndices[i][2]][2]);

        glVertex3fv(&v_box[BoxquadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_box[BoxquadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_box[BoxquadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_box[BoxquadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}


//Drawing pyramid *************************
static GLfloat v_pyramid[5][3] =
        {
                {0.0, 0.0, 0.0},
                {0.0, 0.0, 2.0},
                {2.0, 0.0, 2.0},
                {2.0, 0.0, 0.0},
                {1.0, 4.0, 1.0}
        };

static GLubyte p_Indices[4][3] =
        {
                {4, 1, 2},
                {4, 2, 3},
                {4, 3, 0},
                {4, 0, 1}
        };

static GLubyte PquadIndices[1][4] =
        {
                {0, 3, 2, 1}
        };

void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

static GLfloat v_trapezoid[8][3] =
        {
                {0.0, 0.0, 0.0}, //0
                {0.0, 0.0, 3.0}, //1
                {3.0, 0.0, 3.0}, //2
                {3.0, 0.0, 0.0}, //3
                {0.5, 3.0, 0.5}, //4
                {0.5, 3.0, 2.5}, //5
                {2.5, 3.0, 2.5}, //6
                {2.5, 3.0, 0.5}  //7
        };

static GLubyte TquadIndices[6][4] =
        {
                {0, 1, 2, 3}, //bottom
                {4, 5, 6, 7}, //top
                {5, 1, 2, 6}, //front
                {3, 7, 4, 0}, // back
                {2, 3, 7, 6}, //right
                {0, 4, 5, 1}  //left
        };

void drawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_trapezoid[TquadIndices[i][0]][0], v_trapezoid[TquadIndices[i][0]][1], v_trapezoid[TquadIndices[i][0]][2],
                    v_trapezoid[TquadIndices[i][1]][0], v_trapezoid[TquadIndices[i][1]][1], v_trapezoid[TquadIndices[i][1]][2],
                    v_trapezoid[TquadIndices[i][2]][0], v_trapezoid[TquadIndices[i][2]][1], v_trapezoid[TquadIndices[i][2]][2]);

        glVertex3fv(&v_trapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}


void sky(float x, float y, float z, float width, float height, float length)
{
    materialProperty();
    glDisable(GL_DEPTH_TEST);
    x = x - width  / 2;
    y = y - height / 2;
    z = z - length / 2;


    //front
    glEnable(GL_TEXTURE_2D);
    if(day == true)
    {
        glBindTexture(GL_TEXTURE_2D,ID2[8]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D,ID2[28]);
    }
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y, z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z+length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z);
    glEnd();

    //up;
    if(day == true)
    {
        glBindTexture(GL_TEXTURE_2D,ID2[27]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D,ID2[28]);
    }
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y+height, z+length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z);
    glEnd();

    //back

    if(day == true)
    {
        glBindTexture(GL_TEXTURE_2D,ID2[9]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D,ID2[28]);
    }
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y+height,z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z+length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z+length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z);
    glEnd();

    //right
    if(day == true)
    {
        glBindTexture(GL_TEXTURE_2D,ID2[10]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D,ID2[28]);
    } //10
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    //left

    if(day == true)
    {
        glBindTexture(GL_TEXTURE_2D,ID2[11]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D,ID2[28]);
    } //11
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,          y,        z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,          y+height, z+length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,        z+length);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

/*
void ground()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, ID2[2]);

    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(150,-20,150);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(150,-20,-150);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(-100,-20,-100);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-100,-20,100);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}*/

void ground2()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, ID2[34]); //2

    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(10,-19.8,10);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10,-19.8,-10);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-10,-19.8,-10);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-10,-19.8,10);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void ferrisWheelSeat()
{
    //seat
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glScalef(0.5, 0.2, 1.5);
    drawCube1(0.404, 0.861, 0.361, 0.403,0.1805,0.1805);
    glPopMatrix();

    //seat belt rod
    glPushMatrix();
    glTranslatef(1.3, 0.7, 0);
    glScalef(0.02, 0.02, 1.5);
    drawCube1(0,0,0, 0,0,0.0);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID2[15]);

    //back
    glPushMatrix();
    glScalef(0.2, 0.5, 1.5);
    drawBox();
    glPopMatrix();

    //seat right side
    glPushMatrix();
    glScalef(0.5, 0.5, 0.02);
    drawBox();
    glPopMatrix();

    //seat left side
    glPushMatrix();
    glTranslatef(0, 0, 4.445);
    glScalef(0.5, 0.5, 0.02);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void makecylinder(float height,float Base)
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	//glColor3f(r, g, b);
	glPushMatrix();
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluCylinder(qobj, Base, Base - (0.2 * Base), height, 20, 20);
	glPopMatrix();
}



void rings()
{
    for(float i = -3.5; i >= -17.5; i -= 1)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(0.2, 0.2, 0.2);
        drawTorus(1,0,0, 0.5,0,0,  1.5,7.5,32,64);
        glPopMatrix();
    }

    for(float i = -3; i >= -17; i -= 1)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(90, 1, 0, 0);
        glScalef(0.2, 0.2, 0.2);
        drawTorus(1,1,1, 0.5,0.5,0.5,  1.5,7.5,32,64);
        glPopMatrix();
    }

}

void orbiter()
{

    glPushMatrix();
    glScalef(2, 1, 2);
    ground2();
    glPopMatrix();
    /* //the base
     glPushMatrix();
     glTranslatef(0, -19.5, 0);
     glScalef(10,0.5,10);
     glTranslatef(-1.5, -1.5, -1.5);
     //drawBox();
     drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
     glPopMatrix(); */

    //the 1st torus at the bottom

    rings();

    glPushMatrix();
    glTranslatef(0, -18, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(1,1,1, 0.5,0.5,0.5,  2,8,32,64);
    glPopMatrix();

    //the 2nd torus at the bottom
    glPushMatrix();
    glTranslatef(0, -18.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(1,0,0, 0.5,0,0,  2,10,32,64);
    glPopMatrix();

    /*  //the cylinder stand
      glPushMatrix();
      glTranslatef(0, -3, 0);
      glRotatef(90, 1, 0, 0);
      drawCylinder(0, 1, 0, 0, 0.5, 0);
      glPopMatrix(); */

    //the sphere
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2.5, 2.5, 2.5);
    drawSphere(1,0,0 ,0.5,0,0);
    glPopMatrix();

    //fence in the front
    for(float j = -10; j <= 16; j+=2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, 17);
        glScalef(0.1,2.5,0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

//        glPushMatrix();
//        glTranslatef(j, -16.1, 17);
//        glScalef(.4, .4, .4);
//        drawSphere(0.855,0.439, 0.839, 0.4275, 0.2195, 0.4195);
//        glPopMatrix();
    }

    //the horizontal lines of the front fence
    glPushMatrix();
    glTranslatef(2.5, -17, 17);
    glScalef(9,0.05,0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -18, 17);
    glScalef(9,0.05,0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -19, 17);
    glScalef(9,0.05,0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //gate
    glPushMatrix();
    glTranslatef(-15.5, -20, 17);
    glRotatef(-alpha, 0, 1, 0);
    for(float j = 0; j <= 4; j+=2)
    {
        glPushMatrix();
        glTranslatef(j, 0, 0);
        glScalef(0.1,1.5,0.1);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

//        glPushMatrix();
//        glTranslatef(j, 4.4, 0.2);
//        glScalef(.4, .4, .4);
//        drawSphere(0.855,0.439, 0.839, 0.4275, 0.2195, 0.4195);
//        glPopMatrix();
    }

    for(float j = 1; j <=3; j+=1)
    {
        glPushMatrix();
        glTranslatef(0, j, 0);
        glScalef(1.5,0.05,0.1);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
    }
    glPopMatrix();


    //fence in the back

    for(float j = -14; j <= 16; j+=2)
    {
        glPushMatrix();
        glTranslatef(j, -19.5, -17);
        glScalef(0.1,2.5,0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

//        glPushMatrix();
//        glTranslatef(j, -16.1, -17);
//        glScalef(.4, .4, .4);
//        drawSphere(0.855,0.439, 0.839, 0.4275, 0.2195, 0.4195);
//        glPopMatrix();
    }

    ///the horizontal lines of the back fence
    glPushMatrix();
    glTranslatef(0, -17, -17);
    glScalef(10.5,0.05,0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -18, -17);
    glScalef(10.5,0.05,0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -19, -17);
    glScalef(10.5,0.05,0.1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //fence in the right
    for(float j = -17 ; j <= 15; j+=2)
    {
        glPushMatrix();
        glTranslatef(16, -19.5, j);
        glScalef(0.1,2.5,0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

//        glPushMatrix();
//        glTranslatef(16, -16.1, j);
//        glScalef(.4, .4, .4);
//        drawSphere(0.855,0.439, 0.839, 0.4275, 0.2195, 0.4195);
//        glPopMatrix();
    }

    //the horizontal lines
    glPushMatrix();
    glTranslatef(16, -17, 0);
    glScalef(.1,0.05,11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -18, 0);
    glScalef(.1,0.05,11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -19, 0);
    glScalef(.1,0.05,11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //fence in the left
    for(float j = -17 ; j <= 17; j+=2)
    {
        glPushMatrix();
        glTranslatef(-16, -19.5, j);
        glScalef(0.1,2.5,0.1);
        glTranslatef(-1.5, -1.5, -1.5);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();

//        glPushMatrix();
//        glTranslatef(-16, -16.1, j);
//        glScalef(.4, .4, .4);
//        drawSphere(0.855,0.439, 0.839, 0.4275, 0.2195, 0.4195);
//        glPopMatrix();
    }

    //
    glPushMatrix();
    glTranslatef(-16, -17, 0);
    glScalef(.1,0.05,11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16, -18, 0);
    glScalef(.1,0.05,11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16, -19, 0);
    glScalef(.1,0.05,11.5);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //translating the rotating part down
    glPushMatrix();
    glTranslatef(0, -5, 0);

    //rotating part
    glPushMatrix();
    glRotatef(orbiterTheta, 0, 1, 0);
    //seat
    for(int i = 0; i <=360; i+=45)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glRotatef(orbiterAlpha, 0, 0, 1);
        glRotatef(0, 0,1, 0);
        glTranslatef(15, 0, -2);
        glRotatef(-0, 0,1, 0);
        glRotatef(-orbiterAlpha, 0, 0, 1);
        ferrisWheelSeat();
        glPopMatrix();

        glPushMatrix();
        glRotatef(orbiterAlpha, 0, 0, 1);
        glScalef(5.1, 0.2, 0.2);
        drawCube1(0, 0, 1, 0,0,0.5);
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();

    glPopMatrix();

}


void boatBody()
{
    glPushMatrix();
    glTranslatef(-1.3, 0, 0);
    glScalef(3.7, 0.1, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 1.5, 1.5);
    glScalef(5.5, 1, 0.1);
    glRotatef(180, 0, 0, 1);
    glTranslatef(-1.25, -1.5, -1.25);
    drawTrapezoid(0.412, 0.412, 0.412,  0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1.5, -1.5);
    glScalef(5.5, 1, 0.1);
    glRotatef(180, 0, 0, 1);
    glTranslatef(-1.25, -1.5, -1.25);
    drawTrapezoid(0.412, 0.412, 0.412,  0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.5, 1.5, 0);
    glRotatef(-42, 0, 0, 1);
    glScalef(0.1, 1.3, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.1, 1.5, 0);
    glRotatef(42, 0, 0, 1);
    glScalef(0.1, 1.3, 1);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
    glPopMatrix();

    for(float i=-6; i<=2; i+=2)
    {
        glPushMatrix();
        glTranslatef(i, 0, -1.5);
        glScalef(0.1, 1, 1);
        drawCube1(0.412, 0.412, 0.412,  0.0,0.0,0.0);
        glPopMatrix();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, ID2[3] );

    glPushMatrix();
    glTranslatef(-6.9, 0, 1.7);
    glScalef(3.7, 1, 0.01);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.9, 0, -1.7);
    glScalef(3.7, 1, 0.01);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pirateBoat()
{
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glScalef(1.3, 1, 1.3);
    ground2();
    glPopMatrix();
    //base
    //base stand
    glPushMatrix();
    glTranslatef(0.5, -19.5, 0);
    //glRotatef(-105, 0, 0, 1);
    glScalef(6,0.5,4);
    glTranslatef(-1.5, -1.5, -1.5);
    drawCube1(0.545,0.271,0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

    //translate down
    glPushMatrix();
    glTranslatef(0, -5.5, 0);

    glPushMatrix();
    glTranslatef(0, 0, -4);
    glScalef(0.2, 0.2, 0.5);
    drawCylinder(1,0,0, 0.5,0,0.5);
    glPopMatrix();

    //boat body
    glPushMatrix();
    glRotatef(pirateBoatTheta, 0, 0, 1);
    glTranslatef(1.5, -12, 0);
    boatBody();
    glPopMatrix();

    //stand on the front
    glPushMatrix();
    glTranslatef(0, 0, 1.4);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-55, 0, 0, 1);
    glScalef(4,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
    glPushMatrix();
    glRotatef(-125, 0, 0, 1);
    glScalef(4,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();
    glPopMatrix();

    //stand on the back
    glPushMatrix();
    glTranslatef(0, 0, -1.6);
    glRotatef(pirateBoatTheta, 0, 0, 1);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-55, 0, 0, 1);
    glScalef(4,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
    glPushMatrix();
    glRotatef(-125, 0, 0, 1);
    glScalef(4,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();
    glPopMatrix();

    //base stand at the front
    glPushMatrix();
    glTranslatef(0, 0, 5);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-60, 0, 0, 1);
    glScalef(6,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
    glPushMatrix();
    glRotatef(-120, 0, 0, 1);
    glScalef(6,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.055);
    glPopMatrix();
    glPopMatrix();

    //base stand at the back
    glPushMatrix();
    glTranslatef(0, 0, -5);
    drawSphere(0, 0, 1, 0, 0, 0.5);
    //left stand
    glPushMatrix();
    glRotatef(-60, 0, 0, 1);
    glScalef(6,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

    //right stand
    glPushMatrix();
    glRotatef(-120, 0, 0, 1);
    glScalef(6,0.28,0.1);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

void chair()
{
    //seat part
    glPushMatrix();
    glScalef(0.5, 0.05, 0.5);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left back
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right back
    glPushMatrix();
    glTranslatef(1.35, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1.5 , 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left front leg
    glPushMatrix();
    glTranslatef(0, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right front leg
    glPushMatrix();
    glTranslatef(1.35, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

}

//Calculate the bezier point
double drawBezierx(double x[], double t)
{
    double xx = pow((1 - t), 2) * x[0] + 2 * t * (1 -t) * x[1] + pow (t, 2)* x[2];
    return xx;
}
double drawBeziery(double y[], double t)
{
    double yy = pow((1 - t), 2) * y[0] + 2 * t * (1 -t) * y[1] + pow (t, 2)* y[2];
    return yy;
}
void drawLine(double x1,double y1, double x2, double y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}
void DrawCircle(double cx, double cy, double cz, double r, double num_segments) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.8, 0.08, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.9, 0.1, 0.0, 1.0 };
    GLfloat mat_specular[] = { 1, 0.1, 0.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_LINE_LOOP);
    for (double ii = 0; ii < num_segments; ii++)   {
        double theta = 2.0f * 3.1415926f * ii / num_segments;//get the current angle
        double x = r * cosf(theta);//calculate the x component
        double z = r * sinf(theta);//calculate the y component
        glVertex3f(x + cx, cy, z + cz);//output vertex
    }
    glEnd();
}


void table()
{
    //table
    glPushMatrix();
    glScalef(4, 0.3, 4);
    drawSphere(0.8,0.4,0.00,  0.4,0.2,0);
    glPopMatrix();

    //stand
    glPushMatrix();
    glScalef(0.1, -1, -0.1);
    drawCube1(0,0,0, 0,0,0.8);
    glPopMatrix();

    //stand bottom
    glPushMatrix();
    glTranslatef(0, -2.8, 0);
    glScalef(1, 0.2, 1);
    drawSphere(1,0.549,0.00,  0.5,0.2745,0);
    glPopMatrix();
}

void diningSet()
{
    glPushMatrix();
    glTranslatef(0, -16, 0);
    table();
    glPopMatrix();

    for(int i = 0; i <= 360; i+=90)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        glTranslatef(0, -17, -4);
        chair();
        glPopMatrix();
    }
}

void quad1()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(10,4,3);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,4,3);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,3);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(10,0,3);
    glEnd();
}

void quad2()
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0,8,5);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,8,0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0,0,5);
    glEnd();
}


void icecreamParlor()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID2[26]);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[17]);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[18]);

    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[5]);
    glPushMatrix();
    glTranslatef(0, 8, 1);
    glScalef(1, 1, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


}

void pizzaHut()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID2[15]);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[22]);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[18]);
    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[4]);
    glPushMatrix();
    glTranslatef(0, 6, 1);
    glScalef(1, 1, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void cola()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID2[15]);
    glPushMatrix();
    quad1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 11, -2);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1.5, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[22]);
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1, 2, 1);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[18]);
    glPushMatrix();
    glTranslatef(0, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0, -2);
    quad2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 3, -2);
    glRotatef(90, 1, 0, 0);
    quad1();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,ID2[6]);
    glPushMatrix();
    glTranslatef(0, 6, 1);
    glScalef(1, 0.5, 1);
    quad1();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void complexOrbiterUnit()
{
    glPushMatrix();
    drawSphere(0, 0, 1, 0, 0, 0.5);
    glPopMatrix();


    glPushMatrix();
    glRotatef(cmOrbiterTheta, 0, 1, 0);

    int j = 0;
    for(int i = 0; i<360; i+=90)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glRotatef(-45, 0, 0, 1);
        glTranslatef(4, 0, -2.4);
        glRotatef(45, 0, 0, 1);
        ferrisWheelSeat();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0, -0.5);
        glRotatef(-45, 0, 0, 1);
        glScalef(1.6, 0.2, 0.2);
        drawCube1(colors[j][0],colors[j][1],colors[j][2], colors[j][3],colors[j][4],colors[j][5]);
        glPopMatrix();

        glPopMatrix();

        j++;
    }
    glPopMatrix();
}

void complexOrbiter()
{
    glPushMatrix();
    //glTranslatef(1, 0, 0);
    glScalef(2, 1, 2);
    ground2();
    glPopMatrix();
    /* //the base
     glPushMatrix();
     glTranslatef(0, -19.5, 0);
     glScalef(11,0.5,11);
     glTranslatef(-1.5, -1.5, -1.5);
     //drawBox();
     drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
     glPopMatrix(); */

    //the sphere
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glScalef(2, 2, 2);
    drawSphere(1,0,0 ,0.5,0,0);
    glPopMatrix();

    //the cylinder stand
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    drawCylinder(0, 1, 0, 0, 0.5, 0.5);
    glPopMatrix();

    //the ride
    glPushMatrix();
    glRotatef(cmOrbiterAlpha, 0, 1, 0);

    for(int i=0; i<360; i+=72)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);

        glPushMatrix();
        glTranslatef(0, 0, -0.5);
        glRotatef(-45, 0, 0, 1);
        glScalef(5.8, 0.2, 0.2);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(12, -12, 0);
        complexOrbiterUnit();
        glPopMatrix();

        glPopMatrix();
    }

    glPopMatrix();
}


void flagpole()
{
    quad = gluNewQuadric();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 1.5);
    drawCylinder(1, 0, 0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.5, .2, 1.5);
    gluQuadricTexture(quad,1);
    //gluSphere(quad,4,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glScalef(0.5, 0.5, 0.5);
    drawSphere(.502, 0, 0, 0.26, 0, 0);
    glPopMatrix();

    matCurve(0, 0, 1);
//    drawFlag();
}

void flagpole2()
{
    quad = gluNewQuadric();

    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 1, 1);
    drawCylinder(1, 0.6, 0, 0.7, 0.3, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.5, .2, 1.5);
    gluQuadricTexture(quad,1);
    //gluSphere(quad,14,10,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6.5, 0);
    glScalef(2, 2, 2);
    drawSphere(.7, 0, 0, 0.26, 0, 0);
    glPopMatrix();

    matCurve(0, 0, 1);
//    drawFlag();
}

void rightwall()
{
    materialProperty();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID2[35]);

    glPushMatrix();
    glTranslatef(-50, -100, -80);
    glScalef(5, 10, 120);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(650, -100, -80);
    glScalef(5, 10, 120);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, -100, 280);
    glScalef(235 , 10, 3);
    drawBox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, -100, -80);
    glScalef(80 , 10, 3);
    drawBox();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(280, -100, -80);
    glScalef(125 , 10, 3);
    drawBox();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);




}

void gatelock()
{


    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID2[37]);
    glPushMatrix();
    glTranslatef(79, -20, -172);
    glScalef(31 , 15, .01);
    //glRotatef(90,0,1,0);
    glRotatef(90,0,0,1);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotatef(5,1,0,0);
    glTranslatef(55, 0, -170);
    glScalef(6, 1, .01);
    //glRotatef(900,1,0);

    //drawBox();
    glPopMatrix();

}

void road()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,ID2[29]);
    glPushMatrix();
    glTranslatef(620, -120, -200);
    glScalef(350 , .01, 10);
    //glRotatef(90,0,1,0);
    glRotatef(90,0,0,1);
    drawBox();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}




void materialProperty_car(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void car(double pri_x, double pri_y, double pri_z, double sec_x, double sec_y, double sec_z)
{
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glEnd();


    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
//    glColor3f(1, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( sec_x, sec_y, sec_z, sec_x, sec_y, sec_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0f,-15.0f,15.0f);
    glVertex3f(-30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,15.0f);
    glEnd();


    glBegin(GL_3D);
//    glColor3f(1, 0, 0);
    glTranslated(-20.0f,-15.0f,15.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);


//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,-30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(45.0f,0.0f,0.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
    glEnd();




    glPushMatrix();
    glColor3f(3.0,4.0,5.0);
    //glRotatef(45,0,0,1);
    glScalef(10,0.3,3);

//    glutWireCube(-20);


    glPopMatrix();


    glPopMatrix();
}


void maketree(float height,float Base)
{

    materialProperty_car(0, 1, 0, 0.5, .5, .5 );
	glPushMatrix();
	float angle;
	makecylinder(height, Base);
	glTranslatef(0.0f, height,0.0f);
	height -= height * 0.2f;
	Base -= Base * 0.3f;

	if (height > 1)
	{
		angle = 22.5f;
		glPushMatrix();
		glRotatef(angle, -1.0f, 0.0f, 0.0f);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5f, 0.0f, 0.866f);
		maketree(height, Base);
		glPopMatrix();
		glPushMatrix();
		glRotatef(angle, 0.5f, 0.0f, -0.866f);
		maketree(height, Base);
		glPopMatrix();
	}
	glPopMatrix();
}


void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {.5, .5, .5, 1.0};
    GLfloat light_diffuse[]  = { .2, .2, .2, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 20.0, 50.0, 0.0, 0.0 };

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /* GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}


void streetLampbody()
{
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glScalef(0.5, 0.5, 1);
    drawCylinder(0.1, 0.1, 0.1, 0.05, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -19, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(0.1,0.1,0.1, 0.05,0.05,0.05,  2,5,32,64);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    drawTorus(0.1,0.1,0.1, 0.05,0.05,0.05,  2,5,32,64);
    glPopMatrix();
}


GLfloat light_ambient[][4] = {
        {.2, 0.2, 0.2, 1.0},
        {0.0, 0.0, 1.0, 1.0},
        {0.0, 1.0, 0, 1.0},
        {1.0, 0.0, 0.0, 1.0}
};
GLfloat light_diffuse[][4] = {
        { .5, .5, .5, 1.0 },
        { .5, .5, 1.0, 1.0 },
        { .5, 1, .5, 1.0 },
        { 1, .5, .5, 1.0 }
};
GLfloat light_specular[][4] = {
        { .5, .5, .5, 1.0 },
        { .5, .5, 1.0, 1.0 },
        { .5, 1, .5, 1.0 },
        { 1, .5, .5, 1.0 }
};

void spotLight1()
{
//    glPushMatrix();

    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = { lamp_x[0], 30, lamp_z[0], 0 };

    //GLfloat light_position[] = { 10, 5, 30, 1};

    //cout<<lamp_x[0]<<" "<<lamp_z[0]<<endl;

//    cout<<light1_c<<endl;
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient[light1_c]);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse[light1_c]);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular[light1_c]);

    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0, -1, 0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 70.0);
//    glPopMatrix();
}

void spotLight2()
{
//    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = { lamp_x[1], 30, lamp_z[1], 0 };  //0.7, 4.5, 9.0

    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient[light2_c]);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse[light2_c]);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular[light2_c]);

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.0, -1, 0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, -70.0);
//    glPopMatrix();
}


void streetLight1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};

    glPushMatrix();
    glTranslatef (0,2,0);
    glScalef(2, 2, 2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(light1_on == 0){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

    streetLampbody();
}


void streetLight2()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};

    glPushMatrix();
    glTranslatef (0,2,0);
    glScalef(2, 2, 2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(light2_on == 0){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

    streetLampbody();
}



void maze()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID2[14]);

    glPushMatrix();
    glScalef(3.2, 1, 0.1);
    glTranslatef (-1.1,0, 30);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 1, 3.5);
    glTranslatef (60,0,-2.05);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(3.2, 1, 0.1);
    glTranslatef (-1.8,0, -72);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 1, 3.5);
    glTranslatef (-60,0,-2.05);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 1, 2.7);
    glTranslatef (35,0,-2.6);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 1, 2.2);
    glTranslatef (10,0,-1.5);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.1, 1, 1.8);
    glTranslatef (-15,0,-3.9);
    //drawBox();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.1, 1, 1.8);
    glTranslatef (-37,0,-3);
    //drawBox();
    glPopMatrix();


    glPushMatrix();
    glScalef(1.6, 1, 0.1);
    glTranslatef (-3.7,0, 0);
    //drawBox();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 0.1);
    glTranslatef (-1.3,0, -50);
    //drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //ground
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID2[14]);
    glPushMatrix();
    glTranslatef(-7.3, 0, -8);
    glScalef(7, 0.03, 4);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void skyDropStructure()
{
    for(float i = 0; i<=90; i+=2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glScalef(0.1, 0.1, -1.5);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();
    }

    for(float i = 0; i<=87.2; i+=2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(32, 1, 0, 0);
        glScalef(0.1, 0.1, -1.8);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();
    }


    for(float i = 2.8; i<=90; i+=2.8)
    {
        glPushMatrix();
        glTranslatef(0, i, 0);
        glRotatef(-32, 1, 0, 0);
        glScalef(0.1, 0.1, -1.8);
        drawCube1(1, 0, 0, 0.5,0,0);
        glPopMatrix();
    }
}

void skyDropSeat()
{
    glPushMatrix();
    glTranslatef(-6, 3.2, 1);

    glPushMatrix();
    glScalef(6, 1.8, 0.2);
    drawCube1(1,1,0, 0.5,0.5,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(6, 0.2, 1.2);
    drawCube1(1,1,0, 0.5,0.5,0.5);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 2, 0);
    glScalef(2.2, 0.4, 0.5);
    drawCube1(1,0,1, 0.5,0.5,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 0.5, 0);
    glScalef(0.3, 3, 0.5);
    drawCube1(0,0,1, 0,0.5,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.2, 0.5, 0);
    glScalef(0.3, 3, 0.5);
    drawCube1(0,0,1, 0,0.5,0.5);
    glPopMatrix();

    for(float i = -5.5; i<= 13; i+=2.1)
    {
        glPushMatrix();
        glTranslatef(i, 8, 1.5);
        glRotatef(25, 1, 0, 0);
        glScalef(0.1, 0.1, 0.15);
        drawCylinder(0.412, 0.412, 0.412, 0.2, 0.2, 0.2);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i, 6.8, 4);
        glRotatef(90, 1, 0, 0);
        glScalef(0.1, 0.1, 0.19);
        drawCylinder(0.412, 0.412, 0.412, 0.2, 0.2, 0.2);
        glPopMatrix();
    }


}

void skyDropTexture()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, ID2[12]);
    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2,0,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2,20,0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,20,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void skyDropLogo()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, ID2[13]);
    glPushMatrix();
    materialProperty();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(3,0,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(3,5,0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,5,0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void skyDrop()
{
    for(float i = 0; i <=5; i+=5)
    {
        glPushMatrix();
        glTranslatef(i, 0, 0);
        glScalef(0.2, 30, 0.2);
        drawCube1(0, 0, 1, 0,0,0.5);
        glPopMatrix();
    }

    for(float i = 0; i <=5; i+=5)
    {
        glPushMatrix();
        glTranslatef(i, 0, -5);
        glScalef(0.2, 30, 0.2);
        drawCube1(0, 0, 1, 0,0,0.5);
        glPopMatrix();
    }


    skyDropStructure();

    glPushMatrix();
    glTranslatef(5, 0, 0);
    skyDropStructure();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7, 0, -5);
    glRotatef(-90, 0, 1, 0);
    skyDropStructure();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, skyDropPos, 0);
    //glTranslatef(-6, 0, 1);
    skyDropSeat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0, 0);
    glScalef(2, 4.5, 1);
    skyDropTexture();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, 90, 1);
    glScalef(2.5, 2, 1);
    skyDropLogo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 20, 0);
    ground2();
    glPopMatrix();
}




void birds_view(){

    swap(ey, ez);
}
void display(void)
{
    //sndPlaySound("bird.wav", SND_NOSTOP);
    if (light0_on == 0)
    {

        glClearColor(1, 1, 1, 1);
    }
    else
    {
        glClearColor(0, 0, 0, 0);
    }
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90,1,1,500);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(ex,ey,ez,lx,ly, lz,ux, uy, uz);

    //glViewport(0, 0, windowHeight, windowWidth);

    glScalef(zx,zy,zz);
    glScalef(1,1.6,1);

    glEnable(GL_LIGHTING);

    glPushMatrix();
    sky(ex+(0.05*lx),ey+(0.05*ly),ez+(0.05*lz),250,250,250);
    glPopMatrix();

    // Ground
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID2[30]);
    glPushMatrix();
    glTranslatef(-1000, -15, -400);
    glScalef(1000,.1,300);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    if (light0_on == 0)
    {
        glEnable( GL_LIGHT0);
    }
    else
    {
        glDisable( GL_LIGHT0);
    }

    if (light1_on == 0)
    {
        glEnable( GL_LIGHT1);
    }
    else
    {
        glDisable( GL_LIGHT1);
    }

    if (light2_on == 0)
    {
        glEnable( GL_LIGHT2);
    }
    else
    {
        glDisable( GL_LIGHT2);
    }

    glEnable( GL_DEPTH_TEST );

    glScalef(.2,.2,-.8);
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-225, 0, 100);
    glScalef(4,4,4);
    //ferrisWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200, -80, 90);
    glScalef(12,12,8);
    maze();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-200, 0, -100);
    //glScalef(4,4,3);
    rightwall();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-100, 0, -100);
    glScalef(4,4,3);
    orbiter();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 0, 80);
    glScalef(4,4,4);
    pirateBoat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65, -78, -50);
    glScalef(3, 2, 3);
    glRotatef(180, 0, 1, 0);
    skyDrop();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(-70, -10, -3);
    glScalef(4,4,2);
    //diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 20);
    glTranslatef(lamp_x[0], -10, lamp_z[0]);
    glScalef(4,4,2);
    streetLight1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 20, 35);
    glTranslatef(lamp_x[1], -10, lamp_z[1]);
    glScalef(4,4,2);
    streetLight2();
    glPopMatrix();

    // Shops

    //ground
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,ID2[2]);
    glPushMatrix();
    glTranslatef(100, -85, -150);
    glScalef(67, 0.03, 58);
    drawBox();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(290, -87, -50);
    glScalef(6, 8, 5);
    glRotatef(180, 0, 1, 0);
    cola();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(210, -87, -50);
    glScalef(8, 6, 5);
    glRotatef(180, 0, 1, 0);
    icecreamParlor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(287, -87, -140);
    glScalef(4, 6, 5);
    glRotatef(270, 0, 1, 0);
    pizzaHut();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(230, -30, -90);
    glScalef(4,4,2);
     diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(180, -30, -90);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(130, -30, -90);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(230, -30, -110);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(180, -30, -110);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(130, -30, -110);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(230, -30, -130);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(180, -30, -130);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glTranslatef(130, -30, -130);
    glScalef(4,4,2);
    diningSet();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0, 20, -50);
    glTranslatef(85, -30, -170);
    glScalef(4,4,2);
    flagpole2();
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0, 20, -50);
    glTranslatef(-20, -30, -170);
    glScalef(4,4,2);
    flagpole2();
    glPopMatrix();

    glPushMatrix();

    gatelock();
    glPopMatrix();


    glPushMatrix();
    road();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-40, -100, -185);
    glScalef(.7,.7,.2);
    //glRotatef(90, 0,1,0);
    car(0, .5, .5, 0, .5, .6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(290, -100, -190);
    glScalef(.7,.7,.2);
    //glRotatef(90, 0,1,0);
    car(.3, .1,.8, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(190+gari_nore, -100, -200);
    glScalef(.7,.7,.2);
    //glRotatef(90, 0,1,0);
    car(1, .1,0, 0.5, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-120, -100, -200);
    glScalef(.7,.7,.2);
    //glRotatef(90, 0,1,0);
    car(1, .2, .5, 0.5, .5, .5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, -100, -190);
    glScalef(4,4,4);
    maketree(4.0,.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(80, -100, -190);
    glScalef(4,4,4);
    maketree(4.0,.1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, -100, -100);
    glScalef(6,6,6);
    maketree(4.0,.1);
    glPopMatrix();






    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}

void myMouseFunc(int button, int state, int x, int y)
{

}

void myKeyboardFunc( unsigned char key, int x, int y )
{
//    printf("%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n\n", ex,ey,ez,lx,ly, lz,ux, uy, uz, zx, zy, zz);


    switch ( key )
    {
        case 'x':
        case 'X':
            bRotate = !bRotate;
            uRotate = false;
            zRotate = false;
            axis_x=0.0;
            axis_y=1.0;
            axis_z = 0.0;
            break;

        case 'y':
        case 'Y':
            uRotate = !uRotate;
            bRotate = false;
            zRotate = false;
            axis_x=1.0;
            axis_y=0.0;
            axis_z=0.0;
            break;

        case 'z':
        case 'Z':
            zRotate = !zRotate;
            bRotate = false;
            uRotate = false;
            axis_x=0.0;
            axis_y=0.0;
            axis_y=1.0;
            break;

        case '+':
            zx+=0.05;
            zy+=0.05;
            zz+=0.05;
            break;

        case '-':
            zx-=0.05;
            zy-=0.05;
            zz-=0.05;
            break;

        case 'm':
            Txval += 0.2;
            break;

        case 'M':
            Txval -= 0.2;
            break;

        case 'n':
            Tyval += 0.2;

        case 'N':
            Tyval -= 0.2;
            break;

        case 'b':
            Tzval += 0.2;
            break;

        case 'B':
            Tzval -= 0.2;
            break;

        case 'q':
            ey+=3;
            ly+=3;
            glutPostRedisplay();
            break;
        case 'e':
            ey-=3;
            ly-=3;
            glutPostRedisplay();
            break;
            ///panning
        case 'd':
            ex+=3;
            lx+=3;
            glutPostRedisplay();
            break;
        case 'a':
            ex-=3;
            lx-=3;
            glutPostRedisplay();
            break;

        case 's':
            ez+=3;
            lz+=3;
            glutPostRedisplay();
            break;
        case 'w':
            ez-=3;
            lz-=3;
            glutPostRedisplay();
            break;

        case 'i':
            if (p_state) {
                ly += 2;
                lz = -sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            else {
                ly -= 2;
                lz = sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            if (ez*ez - (lx-ex)*(lx-ex) - (ly-ey)*(ly-ey) < 0) p_state = !p_state;

            glutPostRedisplay();
            break;
        case 'j':
            if (p_state) {
                ly -= 2;
                lz = -sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            else {
                ly += 2;
                lz = sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            if (ez*ez - (lx-ex)*(lx-ex) - (ly-ey)*(ly-ey) < 0) p_state = !p_state;

            glutPostRedisplay();
            break;
        case 'o':
            if (y_state) {
                lx += 2;
                lz = -sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            else {
                lx -= 2;
                lz = sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            if (ez*ez - (lx-ex)*(lx-ex) - (ly-ey)*(ly-ey) < 0) y_state = !y_state;

            glutPostRedisplay();
            break;
        case 'k':
            if (y_state) {
                lx -= 2;
                lz = -sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            else {
                lx += 2;
                lz = sqrt(ez*ez - (lx-ex)*(lx-ex) - (ly-ex)*(ly-ex)) + ez;
            }
            if (ez*ez - (lx-ex)*(lx-ex) - (ly-ey)*(ly-ey) < 0) y_state = !y_state;

            glutPostRedisplay();
            break;

        case 'p':
            if (r_state) {
                ux += 0.03;
                uy = sqrt(1 - ux*ux);
            }
            else {
                ux -= 0.03;
                uy = -sqrt(1 - ux*ux);
            }
            if ((1 - ux*ux) < 0) r_state = !r_state;

            glutPostRedisplay();
            break;
        case 'l':
            if (r_state) {
                ux -= 0.03;
                uy = sqrt(1 - ux*ux);
            }
            else {
                ux += 0.03;
                uy = -sqrt(1 - ux*ux);
            }
            if ((1 - ux*ux) < 0) r_state = !r_state;

            glutPostRedisplay();
            break;

        case '1':
            day = true;
            light0_on = 0;
            break;
        case '2':
            day = false;
            light0_on = 1;
            break;

        case '3':
            light1_on = 0;
            break;
        case '4':
            light1_on = 1;
            break;

        case '5':
            light2_on = 0;
            break;
        case '6':
            light2_on = 1;
            break;

        case '9':
//            light1_c = 1;
            light1_c = (light1_c + 1) % 4;
            break;
//        case '$':
//            light1_c = 0;
//            break;

        case '0':
//            light1_c = 2;
            light2_c = (light2_c + 1) % 4;
            break;

        case 't': //orbiter
            if(orbiterFlag == false) {
                sndPlaySound("1.wav", SND_ASYNC);
                orbiterFlag = true; break;
            }
            else if( orbiterFlag == true) {
                sndPlaySound(NULL, SND_ASYNC);
                orbiterFlag = false; break;
            }
        case 'g': //complex orbiter
            if(cmOrbiterFlag == false) {
                cmOrbiterFlag = true; break;
            }
            else if( cmOrbiterFlag == true) {
                cmOrbiterFlag = false; break;
            }
        case 'u': //pirate boat
            if(pirateBoatFlag == false) {
                sndPlaySound("pirate.wav", SND_ASYNC);
                pirateBoatFlag = true; break;
            }
            else if( pirateBoatFlag == true) {
                sndPlaySound(NULL, SND_ASYNC);
                pirateBoatFlag = false; break;
            }

        case 'v': //skydrop
            if(skyDropFlag == false) {
                sndPlaySound("sky.wav", SND_ASYNC);
                skyDropFlag = true; break;
            }
            else if( skyDropFlag == true) {
                sndPlaySound(NULL, SND_ASYNC);
                skyDropFlag = false; break;
            }
        case 'r':

            gari_nore+=2;
//            if (gari_switch ==1 ){
//                gari_switch =0;
//            }
//            else if (gari_switch ==0 ){
//                gari_switch =1;
//            }

            break;
        case 'R':

            gari_nore-=2;
            break;
        case 'V':
            birds_view();
            //gari_nore-=2;
            break;

        case 27:
            exit(1);
    }
}



void animate()
{
    if (bRotate == true)
    {

        if(theta < 0.0)
        {
            flag1 = 0;
        }
        else if(theta > 360.0)
        {
            flag1 = 1;
        }

        if(flag1 == 0)
        {
            theta += 0.02;

        }
        else if(flag1 == 1)
        {
            theta -= 0.02;

        }

    }

    if (uRotate == true)
    {
        if(alpha < 0.0)
        {
            flag2 = 0;
        }
        else if(alpha > 360.0)
        {
            flag2 = 1;
        }

        if(flag2 == 0)
        {
            alpha += 0.02;


        }
        else if(flag2 == 1)
        {
            alpha -= 0.02;

        }
    }

    if (zRotate == true)
    {
        if(beta < 0.0)
        {
            flag3 = 0;
        }
        else if(beta > 360.0)
        {
            flag3 = 1;
        }

        if(flag3 == 0)
        {
            beta += 0.02;


        }
        else if(flag3 == 1)
        {
            beta -= 0.02;

        }
    }

    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient[light1_c]);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse[light1_c]);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular[light1_c]);

    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient[light2_c]);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse[light2_c]);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular[light2_c]);



    if (fanSwitch == true)
    {
        theta += 2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }



    if(cmOrbiterFlag == true)
    {
        cmOrbiterTheta += 10;
        cmOrbiterAlpha += 1;
    }


    if(orbiterFlag == true)
    {

        orbiterTheta += 3;
        if(orbiterTheta > 360.0)
            orbiterTheta -= 360.0*floor(theta/360.0);

            orbiterAlpha += 2;
         if (orbiterAlpha >= 45)
             orbiterAlpha = 45;
    }
    else
    {
        orbiterAlpha -= 1;
        if (orbiterAlpha <= -45)
            orbiterAlpha = -45;

        orbiterTheta += 3;
        if(orbiterAlpha == -45)
            orbiterTheta = 0;
    }

    if(pirateBoatFlag == true)
    {
        if(pirateBoatCheck == true)
        {
            pirateBoatTheta += 2;
            if(pirateBoatTheta == 60)
            {
                pirateBoatCheck = false;
            }
        }
        else
        {
            pirateBoatTheta -= 2;
            if(pirateBoatTheta == -70)
            {
                pirateBoatCheck = true;
            }
        }
    }
    else
    {
        if(pirateBoatTheta < 0)
        {
            pirateBoatTheta += 2;
            if(pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
        else if(pirateBoatTheta > 0)
        {
            pirateBoatTheta -= 2;
            if(pirateBoatTheta == 0)
            {
                pirateBoatTheta = 0;
            }
        }
    }

    if(skyDropFlag == true)
    {
        if(upFlag == true)
        {
            skyDropPos += 1.2;
            if(skyDropPos >= 80)
            {
                upFlag = false;
            }
        }
        else
        {
            if(downFlag1 == true && downFlag2 == false && downFlag3 == false)
            {
                skyDropPos -= 5;
                if(skyDropPos <= 5)
                {
                    upFlag = true;
                    downFlag1 = false;
                    downFlag2 = true;
                    downFlag3 = false;
                }
            }
            else if(downFlag1 == false && downFlag2 == true && downFlag3 == false)
            {
                skyDropPos -= 3;
                if(skyDropPos <= 45)
                {
                    upFlag = true;
                    downFlag1 = false;
                    downFlag2 = false;
                    downFlag3 = true;
                }
            }
            else if(downFlag1 == false && downFlag2 == false && downFlag3 == true)
            {
                skyDropPos -= 4;
                if(skyDropPos <= 15)
                {
                    upFlag = true;
                    downFlag1 = true;
                    downFlag2 = false;
                    downFlag3 = false;
                }
            }

        }

    }
    else
    {
        skyDropPos -= 2;
        if(skyDropPos <= 2 )
        {
            skyDropPos = 2;
        }
    }

//    if (gari_switch ==1 ){
//        gari_nore = 100;
//    }

    glutPostRedisplay();

}

static void reshape(int width, int height)
{
    const float ar = (float) height / (float) width;
//    ini_x = width/2;
//    ini_y = height/2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,1,500);

    printf("he");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(300,300);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Park");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();
    spotLight1();
    spotLight2();

    LoadTexture2("sgi images/whiteground.sgi",2);
    LoadTexture2("sgi images/whiteground.sgi",3);
    LoadTexture2("sgi images/pirate-copy.sgi",4);
    LoadTexture2("sgi images/red-metal.sgi",5);
    LoadTexture2("sgi images/baskinrobbinslogo.sgi",6);
    LoadTexture2("sgi images/pizzahut.sgi",7);
    LoadTexture2("sgi images/dunkindonuts.sgi",8);
    LoadTexture2("sgi images/front.sgi",9);
    LoadTexture2("sgi images/back.sgi",10);
    LoadTexture2("sgi images/right.sgi",11);
    LoadTexture2("sgi images/left.sgi",12);
    LoadTexture2("sgi images/skydrop.sgi", 13);
    LoadTexture2("sgi images/skydroplogo.sgi", 14);
    LoadTexture2("sgi images/grass.sgi", 15);
    LoadTexture2("sgi images/blackred.sgi", 16);
    LoadTexture2("sgi images/pinkblue.sgi", 17);
    LoadTexture2("sgi images/baskin-robin-ad.sgi", 18);
    LoadTexture2("sgi images/de5b9e.sgi", 19);
    LoadTexture2("sgi images/pinkorange.sgi", 20);
    LoadTexture2("sgi images/ff6d0d.sgi", 21);
    LoadTexture2("sgi images/dd.sgi", 22);
    LoadTexture2("sgi images/pizzahutad.sgi", 23);
    LoadTexture2("sgi images/bush.sgi", 24);
    LoadTexture2("sgi images/bushflower.sgi", 25);
    LoadTexture2("sgi images/brickwall.sgi", 26);
    LoadTexture2("sgi images/redwhite.sgi", 27);
    LoadTexture2("sgi images/up.sgi", 28);
    LoadTexture2("sgi images/nightsky.sgi", 29);
    LoadTexture2("sgi images/rasta.sgi", 30);
    LoadTexture2("sgi images/bush.sgi", 31);
    LoadTexture2("sgi images/purplewall.sgi", 32);
    LoadTexture2("sgi images/soil.sgi", 33);
    LoadTexture2("sgi images/gass2.sgi", 34);
    LoadTexture2("sgi images/carpet.sgi", 35);
    LoadTexture2("sgi images/stone.sgi", 36);
    LoadTexture2("sgi images/park.sgi", 37);


    glutKeyboardFunc(myKeyboardFunc);
    glutMouseFunc(myMouseFunc);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
