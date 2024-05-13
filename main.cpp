#include <windows.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>

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
GLfloat Cx = 0, Cy = 0, Cz = 3.0, degree = 0;

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

void Draw3DBicycle() {

}

void Display() {
    // clear background to BG color to draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // reset to default
    glLoadIdentity();
    // camera positions
    gluLookAt(Cx, Cy, Cz, 0, 0, 0, 0, 1, 0);
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
        Cx -= 0.5;
        break;
    case 'X':
        Cx += 0.5;
        break;
        // camera pos y
    case 'y':
        Cy -= 0.5;
        break;
    case 'Y':
        Cy += 0.5;
        break;
        // camera pos z
    case 'z':
        Cz -= 0.5;
        break;
    case 'Z':
        Cz += 0.5;
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
    case 'r':
        // TO BE IMPLEMENTED
        break;
        // rotate left wheel of bicycle 
    case 'l':
        // TO BE IMPLEMENTED
        break;
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
