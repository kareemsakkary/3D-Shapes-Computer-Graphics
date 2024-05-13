#include <windows.h>
#include <gl/glu.h>
#include <gl/glut.h>

// define colors
#define WHITE glColor3f(1.0f, 1.0f, 1.0f);
#define BLACK glColor3f(0.0f, 0.0f, 0.0f);
#define BEIGE glColor3f(1.0f, 0.96f, 0.76f);
#define BROWN glColor3f(0.5f, 0.25f, 0.05f);
#define LIGHT_GRAY glColor3f(0.8f, 0.8f, 0.8f);
#define LIGHT_BLUE glColor3f(0.69f, 0.77f, 0.87f);

// dimensions for camera
GLfloat Cx = 0.0f, Cy = 0.0f, Cz = 3.0f;
// door and window angles
GLfloat doorAngle = 0.0f;
GLfloat windowAngle1 = 0.0f, windowAngle2 = 0.0f;

void MyInit() {
    // background color (r, g, b, transparency)
    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
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
        { 0.0f, 1.25f, 0.0f },   // Top vertex
        { -0.5f, 0.5f, 0.5f },  // Front bottom-left vertex
        { 0.5f, 0.5f, 0.5f },   // Front bottom-right vertex
        { 0.5f, 0.5f, -0.5f },  // Back bottom-right vertex 
        { -0.5f, 0.5f, -0.5f } // Back bottom-left vertex 
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

void DrawDoor() {
    GLfloat V[4][3] = {
        { -0.1f, -0.5f, 0.51f }, // Top-left vertex 
        { 0.1f, -0.5f, 0.51f },  // Top-right vertex 
        { 0.1f, -0.2f, 0.51f },  // Bottom-right vertex
        { -0.1f, -0.2f, 0.51f }  // Bottom-left vertex 
    };

    BROWN // set drawing color to brown color

    glPushMatrix();
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    DrawRectangle(V[0], V[1], V[2], V[3]);
    glPopMatrix();
}


void DrawWindows() {
    // top-left window
    GLfloat window1[4][3] = {
        { -0.4f, 0.3f, 0.51f }, // Top-left vertex
        { -0.2f, 0.3f, 0.51f }, // Top-right vertex
        { -0.2f, 0.1f, 0.51f }, // Bottom-right vertex
        { -0.4f, 0.1f, 0.51f }  // Bottom-left vertex
    };
    // top-right window
    GLfloat window2[4][3] = {
        { 0.2f, 0.3f, 0.51f }, // Top-left vertex
        { 0.4f, 0.3f, 0.51f }, // Top-right vertex
        { 0.4f, 0.1f, 0.51f }, // Bottom-right vertex
        { 0.2f, 0.1f, 0.51f }  // Bottom-left vertex
    };
    // bottom-left window
    GLfloat window3[4][3] = {
        { -0.4f, -0.3f, 0.51f }, // Top-left vertex
        { -0.2f, -0.3f, 0.51f }, // Top-right vertex
        { -0.2f, -0.1f, 0.51f }, // Bottom-right vertex
        { -0.4f, -0.1f, 0.51f }  // Bottom-left vertex
    };
     // bottom-right window
    GLfloat window4[4][3] = {
        { 0.2f, -0.3f, 0.51f }, // Top-left vertex
        { 0.4f, -0.3f, 0.51f }, // Top-right vertex
        { 0.4f, -0.1f, 0.51f }, // Bottom-right vertex
        { 0.2f, -0.1f, 0.51f }  // Bottom-left vertex
    };

    WHITE // set drawing color to white color

    // draw each window
    glPushMatrix();
    glRotatef(windowAngle1, 0.0f, 1.0f, 0.0f);
    DrawRectangle(window1[0], window1[1], window1[2], window1[3]);
    glPopMatrix();

    WHITE // set drawing color to white color

    glPushMatrix();
    glRotatef(windowAngle2, 0.0f, 1.0f, 0.0f);
    DrawRectangle(window2[0], window2[1], window2[2], window2[3]);
    glPopMatrix();

    WHITE // set drawing color to black color

    glPushMatrix();
    glRotatef(windowAngle1, 0.0f, 1.0f, 0.0f);
    DrawRectangle(window3[0], window3[1], window3[2], window3[3]);
    glPopMatrix();

    WHITE // set drawing color to white color

    glPushMatrix();
    glRotatef(windowAngle2, 0.0f, 1.0f, 0.0f);
    DrawRectangle(window4[0], window4[1], window4[2], window4[3]);
    glPopMatrix();
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
        {-0.5f, 0.0f, 0.5f},    // Top-left vertex
        {0.5f, 0.0f, 0.5f},     // Top-right vertex
        {0.5f, -0.5f, 0.5f},    // Bottom-right vertex
        {-0.5f, -0.5f, 0.5f},   // Bottom-left vertex

        // back
        {-0.5f, 0.0f, -0.5f},   // Top-left vertex
        {0.5f, 0.0f, -0.5f},    // Top-right vertex
        {0.5f, -0.5f, -0.5f},   // Bottom-right vertex
        {-0.5f, -0.5f, -0.5f}   // Bottom-left vertex
    };

    GLfloat VDivider1[4][3] = {
    { 0.01f, 0.0f, 0.5f },   // Top-left vertex
    { 0.01f, 0.0f, -0.5f },  // Top-right vertex
    { 0.01f, -0.5f, -0.5f }, // Bottom-right vertex
    { 0.01f, -0.5f, 0.5f }   // Bottom-left vertex
    };

    GLfloat VFloor2[8][3] = {
        // front
        {-0.5f, 0.5f, 0.5f},    // Top-left vertex
        {0.5f, 0.5f, 0.5f},     // Top-right vertex
        {0.5f, 0.0001f, 0.5f},    // Bottom-right 
        {-0.5f, 0.001f, 0.5f},   // Bottom-left

        // back
        {-0.5f, 0.5f, -0.5f},   // Top-left vertex
        {0.5f, 0.5f, -0.5f},    // Top-right vertex
        {0.5f, 0.0001f, -0.5f},   // Bottom-right vertex
        {-0.5f, 0.0001f, -0.5f}   // Bottom-left vertex
    };

    GLfloat VDivider2[4][3] = {
    { 0.01f, 0.5f, 0.5f },   // Top-left vertex
    { 0.01f, 0.5f, -0.5f },  // Top-right vertex
    { 0.01f, 0.0f, -0.5f }, // Bottom-right vertex
    { 0.01f, 0.0f, 0.5f }   // Bottom-left vertex
    };

    // first floor
    LIGHT_GRAY
    DrawSingleFloor(VFloor1[0], VFloor1[1], VFloor1[2], VFloor1[3], VFloor1[4], VFloor1[5], VFloor1[6], VFloor1[7]);
    LIGHT_GRAY
    DrawRectangle(VDivider1[0], VDivider1[1], VDivider1[2], VDivider1[3]); // floor divider
    // second floor
    LIGHT_BLUE
    DrawSingleFloor(VFloor2[0], VFloor2[1], VFloor2[2], VFloor2[3], VFloor2[4], VFloor2[5], VFloor2[6], VFloor2[7]);
    LIGHT_BLUE
    DrawRectangle(VDivider2[0], VDivider2[1], VDivider2[2], VDivider2[3]); // floor divider
}

void Draw3DBuilding() {
    // draw the building components
    DrawRoof();
    DrawFloors();
    DrawDoor();
    DrawWindows();
}

void Draw3DBicycle() {

}

void Display() {
    // clear background to BG color to draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // reset to default
    glLoadIdentity();
    // camera positions
    gluLookAt(Cx, Cy, Cz, 0, 0, 0, 0, 1, 0);
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
        Cx -= 0.5f; 
        break;
    case 'X':
        Cx += 0.5f;
        break;
    // camera pos y
    case 'y':
        Cy -= 0.5f;
        break;
    case 'Y':
        Cy += 0.5f;
        break;
    // camera pos z
    case 'z':
        Cz -= 0.5f;
        break;
    case 'Z':
        Cz += 0.5f;
        break;
    // open the door
    case 'o':
        doorAngle = 25.0f;
        break;
    // close the door
    case 'c':
        doorAngle = 0.0f; 
        break;
    // open the windows
    case 'O':
        windowAngle1  = -2.5f;
        windowAngle2  = 2.5f;
        break;
    // close the windows
    case 'C':
        windowAngle1 = windowAngle2 = 0.0f;
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