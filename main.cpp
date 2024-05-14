#include <windows.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>

// define colors
#define WHITE glColor3f(1.0, 1.0, 1.0);
#define BLACK glColor3f(0, 0, 0);
#define BEIGE glColor3f(1.0, 0.96, 0.76);
#define BROWN glColor3f(0.5, 0.25, 0.05);
#define GRAY glColor3f(0.16, 0.16, 0.16);
#define LIGHT_GRAY glColor3f(0.8, 0.8, 0.8);
#define LIGHT_BLUE glColor3f(0.69, 0.77, 0.87);

bool openedWindows = false, openedDoor = false;
// dimensions for camera
GLfloat Cx = 0, Cy = 0, Cz = 4.0, degree = 0;
bool rotation = false;
GLfloat angleX = 0.0;
GLfloat angleY = 0.0;
GLfloat angleZ = 0.0;


float leftWheelCenterX = 0.0;
float leftWheelCenterY = 0.0;
float leftWheelCenterZ = 0.0;

GLfloat posX = 0;
GLfloat posY = 0;
GLfloat posZ =-0.60;
GLfloat angle = 0.0;
GLfloat length = 0.0;
using namespace std;


void MyInit() {
    // background color (r, g, b, transparency)
    glClearColor(0, 0.5, 0, 1.0);
    // enable z axis
    glEnable(GL_DEPTH_TEST);
    // camera perspective intialization
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
}

void DrawRoof() {
    GLfloat V[5][3] = {
        { 0, 1.25, 0 },   // Top vertex
        { -0.5, 0.5, 0.5 },  // Front bottom-left vertex
        { 0.5, 0.5, 0.5 },   // Front bottom-right vertex
        { 0.5, 0.5, -0.5 },  // Back bottom-right vertex 
        { -0.5, 0.5, -0.5 } // Back bottom-left vertex 
    };

    BROWN // set drawing color to brown color
    glBegin(GL_TRIANGLES);
    // front face
    glVertex3fv(V[0]);    // Top vertex
    glVertex3fv(V[1]);  // Bottom-left vertex
    glVertex3fv(V[2]);    // Bottom-right vertex

    // back face
    glVertex3fv(V[0]);    // Top vertex
    glVertex3fv(V[4]);  // Bottom-left vertex
    glVertex3fv(V[1]);    // Bottom-right vertex

    // right face
    glVertex3fv(V[0]);    // Top vertex
    glVertex3fv(V[2]);  // Bottom-left vertex
    glVertex3fv(V[3]);    // Bottom-right vertex

    // left face
    glVertex3fv(V[0]);    // Top vertex
    glVertex3fv(V[3]);  // Bottom-left vertex
    glVertex3fv(V[4]);    // Bottom-right vertex
    glEnd();
}

void DrawRectangle(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[]) {
    glBegin(GL_POLYGON);
    glVertex3fv(V0); // Top-left vertex
    glVertex3fv(V1); // Top-right vertex
    glVertex3fv(V2); // Bottom-right vertex
    glVertex3fv(V3); // Bottom-left vertex
    glEnd();
}

void DrawGround() {
    GLfloat V[4][3] = {
        {-10.0, -0.501, -10.0},
        {-10.0, -0.501, 10.0},
        {10.0, -0.501, 10.0},
        {10.0, -0.501, -10.0},
    };
    GRAY
    DrawRectangle(V[0], V[1], V[2], V[3]);
}

void openDoor() {
    if (openedDoor) {
        glTranslatef(-0.61, 0, 0.6);
        // rotate by 90
        glRotatef(90.0, 0, 1.0, 0);
    }
}

void DrawDoor() {
    GLfloat V[4][3] = {
        { -0.1, -0.5, 0.51 }, // Top-left vertex 
        { 0.1, -0.5, 0.51 },  // Top-right vertex 
        { 0.1, -0.2, 0.51 },  // Bottom-right vertex
        { -0.1, -0.2, 0.51 }  // Bottom-left vertex 
    };
    BROWN
    glPushMatrix();
    openDoor();
    DrawRectangle(V[0], V[1], V[2], V[3]);
    glPopMatrix();

    // draw interior background 
    BLACK
    DrawRectangle(V[0], V[1], V[2], V[3]);
}

void openLeftWindows() {
    if (openedWindows) {
        glTranslatef(-0.91, 0, 0.3);
        // rotate by 90
        glRotatef(90.0, 0, 1.0, 0);
    }
}

void openRightWindows() {
    if (openedWindows) {
        glTranslatef(-0.31, 0, 0.89);
        // rotate by 90
        glRotatef(90.0, 0, 1.0, 0);
    }
}

void DrawWindows() {
    // top-left window
    GLfloat window1[4][3] = {
        { -0.4, 0.3, 0.51 }, // Top-left vertex
        { -0.2, 0.3, 0.51 }, // Top-right vertex
        { -0.2, 0.1, 0.51 }, // Bottom-right vertex
        { -0.4, 0.1, 0.51 }  // Bottom-left vertex
    };
    // top-right window
    GLfloat window2[4][3] = {
        { 0.2, 0.3, 0.51 }, // Top-left vertex
        { 0.4, 0.3, 0.51 }, // Top-right vertex
        { 0.4, 0.1, 0.51 }, // Bottom-right vertex
        { 0.2, 0.1, 0.51 }  // Bottom-left vertex
    };
    // bottom-left window
    GLfloat window3[4][3] = {
        { -0.4, -0.3, 0.51 }, // Top-left vertex
        { -0.2, -0.3, 0.51 }, // Top-right vertex
        { -0.2, -0.1, 0.51 }, // Bottom-right vertex
        { -0.4, -0.1, 0.51 }  // Bottom-left vertex
    };
    // bottom-right window
    GLfloat window4[4][3] = {
        { 0.2, -0.3, 0.51 }, // Top-left vertex
        { 0.4, -0.3, 0.51 }, // Top-right vertex
        { 0.4, -0.1, 0.51 }, // Bottom-right vertex
        { 0.2, -0.1, 0.51 }  // Bottom-left vertex
    };

    // WINDOW 1
    WHITE
    glPushMatrix();
    openLeftWindows();
    DrawRectangle(window1[0], window1[1], window1[2], window1[3]);
    glPopMatrix();
    // draw interior background
    BLACK
    DrawRectangle(window1[0], window1[1], window1[2], window1[3]);

    // WINDOW 2
    WHITE
    glPushMatrix();
    openRightWindows();
    DrawRectangle(window2[0], window2[1], window2[2], window2[3]);
    glPopMatrix();
    // draw interior background  
    BLACK
    DrawRectangle(window2[0], window2[1], window2[2], window2[3]);

    // WINDOW 3
    WHITE
    glPushMatrix();
    openLeftWindows();
    DrawRectangle(window3[0], window3[1], window3[2], window3[3]);
    glPopMatrix();
    // draw interior background  
    BLACK
    DrawRectangle(window3[0], window3[1], window3[2], window3[3]);

    // WINDOW 4
    WHITE
    glPushMatrix();
    openRightWindows();
    DrawRectangle(window4[0], window4[1], window4[2], window4[3]);
    glPopMatrix();
    // draw interior background  
    BLACK
    DrawRectangle(window4[0], window4[1], window4[2], window4[3]);
}

void DrawSingleFloor(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[],
    GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]) {
    DrawRectangle(V0, V1, V2, V3); // Front Wall
    DrawRectangle(V4, V5, V6, V7); // Back Wall
    DrawRectangle(V0, V3, V7, V4); // Left Wall
    DrawRectangle(V1, V2, V6, V5); // Right Wall
    DrawRectangle(V0, V1, V5, V4); // Top Wall
    WHITE
    DrawRectangle(V3, V2, V6, V7); // Bottom Wall
}

void DrawFloors() {
    GLfloat VFloor1[8][3] = {
        // front
        {-0.5, 0, 0.5},    // Top-left vertex
        {0.5, 0, 0.5},     // Top-right vertex
        {0.5, -0.5, 0.5},    // Bottom-right vertex
        {-0.5, -0.5, 0.5},   // Bottom-left vertex

        // back
        {-0.5, 0, -0.5},   // Top-left vertex
        {0.5, 0, -0.5},    // Top-right vertex
        {0.5, -0.5, -0.5},   // Bottom-right vertex
        {-0.5, -0.5, -0.5}   // Bottom-left vertex
    };

    GLfloat VDivider1[4][3] = {
    { 0.01, 0, 0.5 },   // Top-left vertex
    { 0.01, 0, -0.5 },  // Top-right vertex
    { 0.01, -0.5, -0.5 }, // Bottom-right vertex
    { 0.01, -0.5, 0.5 }   // Bottom-left vertex
    };

    GLfloat VFloor2[8][3] = {
        // front
        {-0.5, 0.5, 0.5},    // Top-left vertex
        {0.5, 0.5, 0.5},     // Top-right vertex
        {0.5, 0.0001, 0.5},    // Bottom-right 
        {-0.5, 0.0001, 0.5},   // Bottom-left

        // back
        {-0.5, 0.5, -0.5},   // Top-left vertex
        {0.5, 0.5, -0.5},    // Top-right vertex
        {0.5, 0.0001, -0.5},   // Bottom-right vertex
        {-0.5, 0.0001, -0.5}   // Bottom-left vertex
    };

    GLfloat VDivider2[4][3] = {
    { 0.01, 0.5, 0.5 },   // Top-left vertex
    { 0.01, 0.5, -0.5 },  // Top-right vertex
    { 0.01, 0.0, -0.5 }, // Bottom-right vertex
    { 0.01, 0.0, 0.5 }   // Bottom-left vertex
    };

    // first floor
    LIGHT_GRAY
    DrawSingleFloor(VFloor1[0], VFloor1[1], VFloor1[2], VFloor1[3], VFloor1[4], VFloor1[5], VFloor1[6], VFloor1[7]);
    LIGHT_GRAY
    DrawRectangle(VDivider1[0], VDivider1[1], VDivider1[2], VDivider1[3]); // floor 1 room divider

    // second floor
    LIGHT_BLUE
    DrawSingleFloor(VFloor2[0], VFloor2[1], VFloor2[2], VFloor2[3], VFloor2[4], VFloor2[5], VFloor2[6], VFloor2[7]);
    LIGHT_BLUE
    DrawRectangle(VDivider2[0], VDivider2[1], VDivider2[2], VDivider2[3]); // floor 2 room divider
}

void Draw3DBuilding() {
    // draw the building components
    DrawRoof();
    DrawFloors();
    DrawDoor();
    DrawWindows();
}

void Spin() {
    degree = degree + 0.25;
    if (degree > 360)
        degree = 0;
    glutPostRedisplay();
}

//void drawCircle(float cx, float cy, float r, int numSegments) {
//    glBegin(GL_TRIANGLE_FAN);
//    for (int i = 0; i < numSegments; ++i) {
//        float theta = 2.0 * 3.14 * static_cast<float>(i) / static_cast<float>(numSegments);
//        float x = r * cos(theta);
//        float y = r * sin(theta);
//        glVertex2f(x + cx, y + cy);
//    }
//    glEnd();
//}

void Cylinder(GLfloat radius, GLfloat length, float pX, float pY, float pZ, float angle,bool planXY = true)
{

    GLUquadricObj* cylinder;
    cylinder = gluNewQuadric();
    //glColor3f(1, 0, 0);
    glPushMatrix();
    if(planXY)
        glRotatef(90, 0.0f, 1.0f, 0.0f);
    glTranslatef(pZ, pY, pX);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    gluCylinder(cylinder, radius, radius, length, 15, 5);
    glPopMatrix();
}

void DrawWheel(float cx, float cy , float cz) {
	// draw the wheel
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glRotatef(degree, 0, 0, 1);
    glColor3f(0, 0, 0);
    glutSolidTorus(0.02, 0.08, 12, 12);
    glPopMatrix();

}
void DrawLeftWheel(){
    // draw left wheel
    DrawWheel(leftWheelCenterX, leftWheelCenterY, -leftWheelCenterZ);
    glColor3f(1, 0, 0);
    Cylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ - 0.03, -55);
    Cylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ + 0.03, -55);
    Cylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ - 0.03, 0);
    Cylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ + 0.03, 0);
}
void DrawRightWheel() {
    //DrawWheel (- 0.45, leftWheelCenterY, -leftWheelCenterZ);
    DrawWheel(leftWheelCenterX+0.35, leftWheelCenterY, -leftWheelCenterZ);
    glColor3f(1, 0, 0);
    Cylinder(0.01, 0.1, leftWheelCenterX + 0.32 , leftWheelCenterY+0.09, leftWheelCenterZ - 0.03, 70);
    Cylinder(0.01, 0.1, leftWheelCenterX + 0.32,  leftWheelCenterY+0.09, leftWheelCenterZ + 0.03, 70);
    Cylinder(0.01, 0.18, leftWheelCenterX + 0.26, leftWheelCenterY + 0.25, leftWheelCenterZ, 70);
    glColor3f(0, 0, 0);
    // draw the wheel axis
    Cylinder(0.013, 0.14, -leftWheelCenterZ-0.07, leftWheelCenterY + 0.26, leftWheelCenterX + 0.25, 0,false);

}
void DrawBody() {
    glColor3f(1, 0, 0);
    Cylinder(0.01, 0.12, leftWheelCenterX + 0.05, leftWheelCenterY+0.08,leftWheelCenterZ, -55);
    Cylinder(0.01, 0.04, leftWheelCenterX + 0.10, leftWheelCenterY,leftWheelCenterZ, 0);
    Cylinder(0.01, 0.25, leftWheelCenterX + 0.15, leftWheelCenterY - 0.005,leftWheelCenterZ, -100);
    Cylinder(0.01, 0.20, leftWheelCenterX + 0.15, leftWheelCenterY - 0.005,leftWheelCenterZ, -60);
    Cylinder(0.01, 0.15, leftWheelCenterX + 0.12, leftWheelCenterY + 0.18,leftWheelCenterZ, 0);
    glColor3f(0, 0, 0);
    Cylinder(0.01, 0.04, -leftWheelCenterZ - 0.02, leftWheelCenterY - 0.005, leftWheelCenterX + 0.15, 0, false);
}

void DrawSeat() {
    float X = leftWheelCenterX+0.06, Y = leftWheelCenterY + 0.26, Z = -leftWheelCenterZ+0.04;

    /*********************************
    *   Draw the top of the seat
    **********************************/
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(X, Y, Z);
    glVertex3f(X + 0.03, Y, Z);
    glVertex3f(X + 0.06, Y, Z - 0.02);
    glVertex3f(X + 0.12, Y, Z - 0.03);
    glVertex3f(X + 0.12, Y, Z - 0.05);
    glVertex3f(X + 0.06, Y, Z - 0.06);
    glVertex3f(X + 0.03, Y, Z - 0.08);
    glVertex3f(X, Y, Z - 0.08);
    glEnd();


    ///**********************************
    //*   Draw the bottom base part of the
    //*   seat
    //************************************/
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(X, Y - 0.02, Z);
    glVertex3f(X + 0.03, Y - 0.02, Z);
    glVertex3f(X + 0.06, Y - 0.02, Z - 0.02);
    glVertex3f(X + 0.12, Y - 0.02, Z - 0.03);
    glVertex3f(X + 0.12, Y - 0.02, Z - 0.05);
    glVertex3f(X + 0.06, Y - 0.02, Z - 0.06);
    glVertex3f(X + 0.03, Y - 0.02, Z - 0.08);
    glVertex3f(X, Y - 0.02, Z - 0.08);
    glEnd();

    ///**********************
    //*   Draw the sides!
    //***********************/
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);

    glVertex3f(X, Y, Z);
    glVertex3f(X, Y, Z - 0.08);
    glVertex3f(X, Y - 0.02, Z - 0.08);
    glVertex3f(X, Y - 0.02, Z);


    glVertex3f(X, Y, Z);
    glVertex3f(X + 0.03, Y, Z);
    glVertex3f(X + 0.03, Y - 0.02, Z);
    glVertex3f(X, Y - 0.02, Z);

   
   
    glVertex3f(X, Y - 0.02, Z - 0.08);
    glVertex3f(X + 0.03, Y - 0.02, Z - 0.08);
    glVertex3f(X + 0.03, Y, Z - 0.08);
    glVertex3f(X, Y, Z - 0.08);


    glVertex3f(X + 0.03, Y, Z);
    glVertex3f(X + 0.06, Y, Z - 0.02);
    glVertex3f(X + 0.06, Y - 0.02, Z - 0.02);
    glVertex3f(X + 0.03, Y - 0.02, Z);

    glVertex3f(X + 0.03, Y, Z - 0.08);
    glVertex3f(X + 0.06, Y, Z - 0.06);
    glVertex3f(X + 0.06, Y - 0.02, Z - 0.06);
    glVertex3f(X + 0.03, Y - 0.02, Z - 0.08);


    glVertex3f(X + 0.06, Y, Z - 0.02);
    glVertex3f(X + 0.12, Y, Z - 0.03);
    glVertex3f(X + 0.12, Y - 0.02, Z - 0.03);
    glVertex3f(X + 0.06, Y - 0.02, Z - 0.02);

    glVertex3f(X + 0.06, Y, Z - 0.06);
    glVertex3f(X + 0.12, Y, Z - 0.05);
    glVertex3f(X + 0.12, Y - 0.02, Z - 0.05);
    glVertex3f(X + 0.06, Y - 0.02, Z - 0.06);

    glVertex3f(X + 0.12, Y, Z - 0.03);
    glVertex3f(X + 0.12, Y, Z - 0.05);
    glVertex3f(X + 0.12, Y - 0.02, Z - 0.05);
    glVertex3f(X + 0.12, Y - 0.02, Z - 0.03);


    glEnd();
}

void Draw3DBicycle() {
    cout << "posX: " << posX << " posY: " << posY << " posZ : " << posZ << endl;
    cout << "angle: " << angle << " len : " << length << endl;
    leftWheelCenterX = posX;
    leftWheelCenterY = posY;
    leftWheelCenterZ = posZ;

    // draw left wheel
    DrawLeftWheel();
    // draw right wheel
    DrawRightWheel();
    // draw body
    DrawBody();
    // draw seat
    DrawSeat();
}

void Display() {
    // clear background to BG color to draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // reset to default
    glLoadIdentity();
    // camera positions
    gluLookAt(Cx, Cy, Cz, 0, 0, 0, 0, 1, 0);
    // rotate the scene
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    // draw ground
    DrawGround();
    // start drawing the building
    Draw3DBuilding();
    // start drawing the bicycle
    Draw3DBicycle();
    // save drawing changes
    glutSwapBuffers();
}

void Key(unsigned char ch, int x, int y) {
    switch (ch) {
        // camera pos x
    case 'x':
        if(rotation)
            angleX += 5.0;
		else
			Cx -= 0.01;
        break;
    case 'X':
        if(rotation)
			angleX -= 5.0;
        else
            Cx += 0.01;
        break;
        // camera pos y
    case 'y':
        if(rotation)
			angleY += 5.0;
		else
			Cy -= 0.01;
        break;
    case 'Y':
        if(rotation)
            angleY -= 5.0;
		else
            Cy += 0.01;
        break;
        // camera pos z
    case 'z':
        if(rotation)
			angleZ += 5.0;
        else
            Cz -= 0.01;
        break;
    case 'Z':
        if(rotation)
            angleZ -= 5.0;
		else
            Cz += 0.01;
        break;
        // open the door
    case 'o':
        openedDoor = true;
        break;
        // close the door
    case 'c':
        openedDoor = false;
        break;
        // open the windows
    case 'O':
        openedWindows = true;
        break;
        // close the windows
    case 'C':
        openedWindows = false;
        break;
        // move bicycle in forward x-axis direction
    case 'f':
        // TO BE IMPLEMENTED
        break;
        // move bicycle in backward x-axis direction
    case 'b':
        // TO BE IMPLEMENTED
        break;
        // rotate right wheel of bicycle 
   // case 'r':
        // TO BE IMPLEMENTED
       // break;
        // rotate left wheel of bicycle 
    case 'l':
        // TO BE IMPLEMENTED
        break;
    case 's':
        rotation = !rotation;
        std::cout << "rotation: " <<  rotation << std::endl;
        break;
    case 'w':
        posX +=0.01;
        break;
    case 'W':
		posX -=0.01;
		break;
    case 'q':
        posY +=0.01;
		break;
    case 'Q':
        posY -=0.01;
        break;

    case 'e':
        posZ +=0.01;
		break;
    case 'E':
		posZ -=0.01;
		break;
    case 'r':
        angle += 5.0;
        break;
    case 'R':
        angle -= 5.0;
		break;
    case 't':
		length += 0.1;
		break;
    case 'T':
        length -= 0.1;

    }
    glutPostRedisplay();
}

int main(int argC, char *argV[])
{
    // initialization function
    glutInit(&argC, argV);
    // initial position of window (space from left, space from up)
    glutInitWindowPosition(250, 50);
    // initialize window size (width, height)
    glutInitWindowSize(1000, 700);
    // display mode initialization
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // create window
    glutCreateWindow("3D Shapes");
    // initialization function for window
    MyInit();
    // display function for window
    glutDisplayFunc(Display);
    // keys clicked func
    glutKeyboardFunc(Key);
    // main loop to make the window appear
    glutMainLoop();
    // exit
    return 0;
}
