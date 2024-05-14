#include <windows.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>

// define colors
#define SILVER glColor3f(0.612, 0.612, 0.612);
#define WHITE glColor3f(1.0, 1.0, 1.0);
#define BLACK glColor3f(0, 0, 0);
#define BEIGE glColor3f(1.0, 0.96, 0.76);
#define BROWN glColor3f(0.5, 0.25, 0.05);
#define GRAY glColor3f(0.65, 0.65, 0.65);
#define DARK_GRAY glColor3f(0.16, 0.16, 0.16);
#define LIGHT_GRAY glColor3f(0.8, 0.8, 0.8);
#define LIGHT_BLUE glColor3f(0.69, 0.77, 0.87);

// dimensions for camera
GLfloat Cx = 0, Cy = 0, Cz = 4.0, degree = 0;
bool rotation = false;
GLfloat angleX = 0.45;
GLfloat angleY = 0.0;
GLfloat angleZ = 0.0;

bool openedWindows = false, openedDoor = false;

float leftWheelCenterX = 0.0;
float leftWheelCenterY = 0.0;
float leftWheelCenterZ = 0.0;

GLfloat byciclePosX = 0;
GLfloat wheelAngle = 0.0;
GLfloat bycicleRotation = 0.0;
bool isMoving = false;

using namespace std;

// ------------------- COMMON FUNCTIONS ----------------------------------------
void drawCircle(float cx, float cy, float cz, float r, int numSegments) {
    // draw circle 3D
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0 * 3.14 * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = r * cos(theta);
        float y = r * sin(theta);
        glVertex3f(x + cx, y + cy, cz);
    }
    glEnd();
}

// ------------------- 3D BUILDING FUNCTIONS ----------------------------------------
void drawRoof() {
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

void drawRectangle(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[]) {
    glBegin(GL_POLYGON);
    glVertex3fv(V0); // Top-left vertex
    glVertex3fv(V1); // Top-right vertex
    glVertex3fv(V2); // Bottom-right vertex
    glVertex3fv(V3); // Bottom-left vertex
    glEnd();
}


void openDoor() {
    if (openedDoor) {
        glTranslatef(-0.61, 0, 0.6);
        // rotate by 90
        glRotatef(90.0, 0, 1.0, 0);
    }
}

void drawDoorKnock() {
    WHITE
    glPushMatrix();
    if (openedDoor) {
        glTranslatef(-0.622, 0, 0.691);
        // rotate by 90
        glRotatef(90.0, 0, 1.0, 0);
    }
    drawCircle(0.05, -0.4, 0.52, 0.012, 100);
    glPopMatrix();
}

void drawDoor() {
    GLfloat V[4][3] = {
        { -0.1, -0.5, 0.51 }, // Top-left vertex 
        { 0.1, -0.5, 0.51 },  // Top-right vertex 
        { 0.1, -0.2, 0.51 },  // Bottom-right vertex
        { -0.1, -0.2, 0.51 }  // Bottom-left vertex 
    };
    BROWN
    glPushMatrix();
    openDoor();
    drawRectangle(V[0], V[1], V[2], V[3]);
    glPopMatrix();

    // draw door knock
    drawDoorKnock();

    // draw shadow background 
    BLACK
    drawRectangle(V[0], V[1], V[2], V[3]);
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

void drawWindows() {
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
    drawRectangle(window1[0], window1[1], window1[2], window1[3]);
    glPopMatrix();
    // draw shadow background
    BLACK
    drawRectangle(window1[0], window1[1], window1[2], window1[3]);

    // WINDOW 2
    WHITE
    glPushMatrix();
    openRightWindows();
    drawRectangle(window2[0], window2[1], window2[2], window2[3]);
    glPopMatrix();
    // draw shadow background  
    BLACK
    drawRectangle(window2[0], window2[1], window2[2], window2[3]);

    // WINDOW 3
    WHITE
    glPushMatrix();
    openLeftWindows();
    drawRectangle(window3[0], window3[1], window3[2], window3[3]);
    glPopMatrix();
    // draw shadow background  
    BLACK
    drawRectangle(window3[0], window3[1], window3[2], window3[3]);

    // WINDOW 4
    WHITE
    glPushMatrix();
    openRightWindows();
    drawRectangle(window4[0], window4[1], window4[2], window4[3]);
    glPopMatrix();
    // draw shadow background  
    BLACK
    drawRectangle(window4[0], window4[1], window4[2], window4[3]);
}

void drawSingleFloor(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[],
    GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]) {
    drawRectangle(V0, V1, V2, V3); // Front Wall
    drawRectangle(V4, V5, V6, V7); // Back Wall
    drawRectangle(V0, V3, V7, V4); // Left Wall
    drawRectangle(V1, V2, V6, V5); // Right Wall
    drawRectangle(V0, V1, V5, V4); // Top Wall
    WHITE
    drawRectangle(V3, V2, V6, V7); // Bottom Wall
}

void drawFloors() {
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
    drawSingleFloor(VFloor1[0], VFloor1[1], VFloor1[2], VFloor1[3], VFloor1[4], VFloor1[5], VFloor1[6], VFloor1[7]);
    LIGHT_GRAY
    drawRectangle(VDivider1[0], VDivider1[1], VDivider1[2], VDivider1[3]); // floor 1 room divider

    // second floor
    LIGHT_BLUE
    drawSingleFloor(VFloor2[0], VFloor2[1], VFloor2[2], VFloor2[3], VFloor2[4], VFloor2[5], VFloor2[6], VFloor2[7]);
    LIGHT_BLUE
    drawRectangle(VDivider2[0], VDivider2[1], VDivider2[2], VDivider2[3]); // floor 2 room divider
}

void draw3DBuilding() {
    // draw the building components
    drawRoof();
    drawFloors();
    drawDoor();
    drawWindows();
}

// ------------------- 3D BICYLE FUNCTIONS ----------------------------------------
void drawCylinder(GLfloat radius, GLfloat length, float pX, float pY, float pZ, float angle,bool planeXY = true)
{
    GLUquadricObj* cylinder;
    cylinder = gluNewQuadric();
    glPushMatrix();
    if(planeXY)
        glRotatef(90, 0.0f, 1.0f, 0.0f);
    glTranslatef(pZ, pY, pX);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    gluCylinder(cylinder, radius, radius, length, 15, 5);
    glPopMatrix();
}

void drawWheel(float cx, float cy , float cz) {
	// draw the wheel
    BLACK
    glPushMatrix();
    glTranslatef(cx, cy, cz);
    glRotatef(-degree, 0, 0, 1);
    glutSolidTorus(0.02, 0.08, 12, 12);
    glPopMatrix();


}
void drawLeftWheel(){
    // draw left wheel
    drawWheel(leftWheelCenterX, leftWheelCenterY, -leftWheelCenterZ);
    drawCylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ - 0.03, -55);
    drawCylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ + 0.03, -55);
    drawCylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ - 0.03, 0);
    drawCylinder(0.01, 0.1, leftWheelCenterX, leftWheelCenterY, leftWheelCenterZ + 0.03, 0);
}

void drawRightWheel(int f) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(leftWheelCenterX + 0.35, leftWheelCenterY, -leftWheelCenterZ); // move back to focus of gluLookAt
    glRotatef(wheelAngle, 0, f,0);
    glTranslatef(-(leftWheelCenterX + 0.35), -leftWheelCenterY, leftWheelCenterZ); // move object to center
    // draw right wheel
    drawWheel(leftWheelCenterX + 0.35, leftWheelCenterY, -leftWheelCenterZ);
    drawCylinder(0.01, 0.1, leftWheelCenterX + 0.32, leftWheelCenterY + 0.09, leftWheelCenterZ - 0.03, 70);
    drawCylinder(0.01, 0.1, leftWheelCenterX + 0.32, leftWheelCenterY + 0.09, leftWheelCenterZ + 0.03, 70);
    drawCylinder(0.01, 0.18, leftWheelCenterX + 0.26, leftWheelCenterY + 0.25, leftWheelCenterZ, 70);

    // draw the bicycle handles
    SILVER
    drawCylinder(0.013, 0.14, -leftWheelCenterZ - 0.07, leftWheelCenterY + 0.26, leftWheelCenterX + 0.25, 0, false);

    glPopMatrix();
}

void drawBody() {
    // draw the structure of the bicycle body
    BLACK

    drawCylinder(0.01, 0.12, leftWheelCenterX + 0.05, leftWheelCenterY+0.08,leftWheelCenterZ, -55);
    drawCylinder(0.01, 0.04, leftWheelCenterX + 0.10, leftWheelCenterY,leftWheelCenterZ, 0);
    drawCylinder(0.01, 0.25, leftWheelCenterX + 0.15, leftWheelCenterY - 0.005,leftWheelCenterZ, -100);
    drawCylinder(0.01, 0.20, leftWheelCenterX + 0.15, leftWheelCenterY - 0.005,leftWheelCenterZ, -60);
    drawCylinder(0.01, 0.16, leftWheelCenterX + 0.12, leftWheelCenterY + 0.18,leftWheelCenterZ, 0);
    SILVER
    drawCylinder(0.01, 0.04, -leftWheelCenterZ - 0.02, leftWheelCenterY - 0.005, leftWheelCenterX + 0.15, 0, false);
}

void drawSeat() {
    float X = leftWheelCenterX+0.06, Y = leftWheelCenterY + 0.26, Z = -leftWheelCenterZ+0.04;

    BLACK
    // Draw the top of the seat
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


    // Draw the bottom base part of the seat
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

    // Draw the sides of the seat
    glBegin(GL_QUADS);

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

void draw3DBicycle() {
    // draw bicycle to rotate in a direction
    leftWheelCenterX = byciclePosX;
    leftWheelCenterY = -0.4;
    leftWheelCenterZ = -1.2;

    glPushMatrix();

    glRotatef(bycicleRotation, 0, 1, 0);
    // draw left wheel
    drawLeftWheel();
    // draw right wheel
    drawRightWheel(1);
    // draw body
    drawBody();
    // draw seat
    drawSeat();

    glPopMatrix();
}

void draw3DBicycle2() {
    // draw bicycle to rotate in opposite direction of first bicycle
    leftWheelCenterX = -byciclePosX;
    leftWheelCenterY = -0.4;
    leftWheelCenterZ = -1.6;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRotatef(bycicleRotation, 0, -1, 0);
    glTranslatef(leftWheelCenterX, leftWheelCenterY, -leftWheelCenterZ); // move back to focus of gluLookAt
    glRotatef(180, 0, 1, 0);
    glTranslatef(-(leftWheelCenterX), -leftWheelCenterY, leftWheelCenterZ); //move object to center
    // draw left wheel
    drawLeftWheel();
    // draw right wheel
    drawRightWheel(-1);
    // draw body
    drawBody();
    // draw seat
    drawSeat();

    glPopMatrix();
}

void spinBicycle() {
    // start spinning the bicycle around the building
    if (isMoving) {
        wheelAngle = 15;
        bycicleRotation += 0.1;
        degree += 0.1;
        if (bycicleRotation > 360)
            bycicleRotation = 0;
        if (bycicleRotation > 360)
            degree = 0;
        glutPostRedisplay();
    }

}

void drawDottedCircles() {
    // some dotted circles within dark gray circle space to separate street direction 
    for (int i = 0; i < 10; ++i) {
        // calculate angle for each dotted circle
        float angle = i * (360.0 / 10);
        float x = 1.41 * cos(angle * 3.14 / 180.0);
        float y = 1.41 * sin(angle * 3.14 / 180.0);
        WHITE
        drawCircle(x, y, 0.49, 0.07, 100);
    }
}

// ------------------- CIRCULAR STREET FUNCTION ----------------------------------------
void drawRoundStreet() {
    glPushMatrix();

    glRotatef(90, 1, 0, 0);
    // first circle
    WHITE
    drawCircle(0, 0, 0.51, 2, 100);
    // second circle
    DARK_GRAY
    drawCircle(0, 0, 0.505, 1.8, 100);
    // third circle
    GRAY
    drawCircle(0, 0, 0.50, 1, 100);
    // dotted circles
    drawDottedCircles();

    glPopMatrix();
}

// ------------------- WINDOW FUNCTIONS ----------------------------------------
void display() {
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
    // draw circular street
    drawRoundStreet();
    // start drawing the building
    draw3DBuilding();
    // start drawing the bicycle
    draw3DBicycle();
    draw3DBicycle2();
    // save drawing changes
    glutSwapBuffers();
}

void key(unsigned char ch, int x, int y) {
    switch (ch) {
    case 'x':
        // camera pos x
        if(rotation)
            angleX += 5.0;
		else
			Cx -= 0.05;
        break;
    case 'X':
        if(rotation)
			angleX -= 5.0;
        else
            Cx += 0.05;
        break;
    case 'y':
        // camera pos y
        if(rotation)
			angleY += 5.0;
		else
			Cy -= 0.05;
        break;
    case 'Y':
        if(rotation)
            angleY -= 5.0;
		else
            Cy += 0.05;
        break;
    case 'z':
        // camera pos z
        if(rotation)
			angleZ += 5.0;
        else
            Cz -= 0.05;
        break;
    case 'Z':
        if(rotation)
            angleZ -= 5.0;
		else
            Cz += 0.05;
        break;
    case 'o':
        // open the door
        openedDoor = true;
        break;
        // close the door
    case 'c':
        openedDoor = false;
        break;
    case 'O':
        // open the windows
        openedWindows = true;
        break;
    case 'C':
        // close the windows
        openedWindows = false;
        break;
    case 'f':
        // move bicycle in forward x-axis direction
        wheelAngle = 0;
        byciclePosX += 0.04;
        if(byciclePosX > 1.35)
			byciclePosX = -1.45;
        cout << byciclePosX << endl;
        degree += 5;
        if(degree > 360)
			degree = 0;
        break;
    case 'b':
        // move bicycle in backward x-axis direction
        wheelAngle = 0;
        byciclePosX -= 0.04;
        if(byciclePosX < -1.50)
            byciclePosX = 1.45;
        degree -= 5;
        if (degree < -360)
            degree = 0;
        break;
    case 'r':
        // rotate right wheel of bicycle
        if(wheelAngle < 25)
            wheelAngle += 5.0;
        break;
    case 'l':
        // rotate left wheel of bicycle
        if(wheelAngle > -25)
            wheelAngle -= 5.0;
        break;
    case 's':
        // camera rotation
        rotation = !rotation;
        std::cout << "rotation: " <<  rotation << std::endl;
        break;
    case 'q':
        // initialize all values to default
        wheelAngle = 0;
        byciclePosX = 0;
        bycicleRotation = 0;
        isMoving = false;
        break;
    case 27:
		exit(0);
		break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    // left mouse clicked, spin
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isMoving = true;
	}
    // right mouse clicked, stop spinning
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        isMoving = false;
    }
	glutPostRedisplay();
}

void myInit() {
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

// ------------------- MAIN FUNCTION ----------------------------------------
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
    myInit();
    // display function for window
    glutDisplayFunc(display);
    // keys clicked func
    glutKeyboardFunc(key);
    // mouse clicked func
    glutMouseFunc(mouse);
    // idle function
    glutIdleFunc(spinBicycle);
    // main loop to make the window appear
    glutMainLoop();
    
    // exit
    return 0;
}
