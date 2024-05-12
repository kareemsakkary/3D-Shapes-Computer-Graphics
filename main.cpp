#include <windows.h>
#include <gl/glu.h>
#include <gl/glut.h>

// define colors
#define WHITE glColor3f(1.0f, 1.0f, 1.0f);
#define BEIGE glColor3f(1.0f, 0.96f, 0.76f);
#define BROWN glColor3f(0.5f, 0.25f, 0.05f);
#define LIGHT_GRAY glColor3f(0.8f, 0.8f, 0.8f);
#define LIGHT_BLUE glColor3f(0.69f, 0.77f, 0.87f);

// dimensions for camera
GLfloat Cx = 0, Cy = 0, Cz = 3;

void MyInit() {
    // background color (r, g, b, transparency)
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    // enable z axis
    glEnable(GL_DEPTH_TEST); 
    // camera perspective intialization
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 10);
    glMatrixMode(GL_MODELVIEW);
}

void DrawRoof() {
    GLfloat V0[] = { 0.0f, 1.0f, 0.0f };   // Top vertex of roof
    GLfloat V1[] = { -0.5f, 0.5f, 0.5f };  // Front bottom-left vertex of roof
    GLfloat V2[] = { 0.5f, 0.5f, 0.5f };   // Front bottom-right vertex of roof
    GLfloat V3[] = { 0.5f, 0.5f, -0.5f };  // Back bottom-right vertex of roof
    GLfloat V4[] = { -0.5f, 0.5f, -0.5f }; // Back bottom-left vertex of roof

    BROWN // set drawing color to brown color

    glBegin(GL_TRIANGLES);
        // front face
        glVertex3fv(V0);    // Top
        glVertex3fv(V1);  // Bottom-left
        glVertex3fv(V2);    // Bottom-right

        // back face
        glVertex3fv(V0);    // Top
        glVertex3fv(V4);  // Bottom-left
        glVertex3fv(V1);    // Bottom-right

        // right face
        glVertex3fv(V0);    // Top
        glVertex3fv(V2);  // Bottom-left
        glVertex3fv(V3);    // Bottom-right

        // left face
        glVertex3fv(V0);    // Top
        glVertex3fv(V3);  // Bottom-left
        glVertex3fv(V4);    // Bottom-right
    glEnd();
}

void DrawDoor() {
    GLfloat V0[] = { -0.1f, -0.5f, 0.51f }; // Top-left vertex of door
    GLfloat V1[] = { 0.1f, -0.5f, 0.51f }; // Top-right vertex of door
    GLfloat V2[] = { 0.1f, -0.2f, 0.51f }; // Bottom-right vertex of door
    GLfloat V3[] = { -0.1f, -0.2f, 0.51f }; // Bottom-left vertex of door

    BROWN // set drawing color to brown color

    glBegin(GL_POLYGON);
        glVertex3fv(V0); // Top-left vertex
        glVertex3fv(V1); // Top-right vertex
        glVertex3fv(V2); // Bottom-right vertex
        glVertex3fv(V3); // Bottom-left vertex
    glEnd();
}

void DrawSingleWindow(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[]) {
    WHITE // set drawing color to white color

    glBegin(GL_POLYGON);
        glVertex3fv(V0); // Top-left vertex
        glVertex3fv(V1); // Top-right vertex
        glVertex3fv(V2); // Bottom-right vertex
        glVertex3fv(V3); // Bottom-left vertex
    glEnd();
}

void DrawWindows() {
    // Top-left window
    GLfloat window1[4][3] = {
        { -0.4f, 0.3f, 0.51f }, // Top-left vertex
        { -0.2f, 0.3f, 0.51f }, // Top-right vertex
        { -0.2f, 0.1f, 0.51f }, // Bottom-right vertex
        { -0.4f, 0.1f, 0.51f }  // Bottom-left vertex
    };
    // Top-right window
    GLfloat window2[4][3] = {
        { 0.2f, 0.3f, 0.51f }, // Top-left vertex
        { 0.4f, 0.3f, 0.51f }, // Top-right vertex
        { 0.4f, 0.1f, 0.51f }, // Bottom-right vertex
        { 0.2f, 0.1f, 0.51f }  // Bottom-left vertex
    };
    // Bottom-left window
    GLfloat window3[4][3] = {
        { -0.4f, -0.3f, 0.51f }, // Top-left vertex
        { -0.2f, -0.3f, 0.51f }, // Top-right vertex
        { -0.2f, -0.1f, 0.51f }, // Bottom-right vertex
        { -0.4f, -0.1f, 0.51f }  // Bottom-left vertex
    };
     // Bottom-right window
    GLfloat window4[4][3] = {
        { 0.2f, -0.3f, 0.51f }, // Top-left vertex
        { 0.4f, -0.3f, 0.51f }, // Top-right vertex
        { 0.4f, -0.1f, 0.51f }, // Bottom-right vertex
        { 0.2f, -0.1f, 0.51f }  // Bottom-left vertex
    };

    // Draw each window
    DrawSingleWindow(window1[0], window1[1], window1[2], window1[3]);
    DrawSingleWindow(window2[0], window2[1], window2[2], window2[3]);
    DrawSingleWindow(window3[0], window3[1], window3[2], window3[3]);
    DrawSingleWindow(window4[0], window4[1], window4[2], window4[3]);
}

void DrawWall(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
    glBegin(GL_POLYGON);
        glVertex3fv(A); // Top-left vertex
        glVertex3fv(B); // Top-right vertex
        glVertex3fv(C); // Bottom-right vertex
        glVertex3fv(D); // Bottom-left vertex
    glEnd();
}

void DrawSingleFloor(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[],
    GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]) {
    DrawWall(V0, V1, V2, V3); // Front Wall
    DrawWall(V4, V5, V6, V7); // Back Wall
    DrawWall(V0, V3, V7, V4); // Left Wall
    DrawWall(V1, V2, V6, V5); // Right Wall
    DrawWall(V0, V1, V5, V4); // Top Wall
    DrawWall(V3, V2, V6, V7); // Bottom Wall
}

void DrawFloors() {
    GLfloat VFloor1[8][3] = {
        // front
        {-0.5f, 0.5f, 0.5f},    // Top-left 
        {0.5f, 0.5f, 0.5f},     // Top-right 
        {0.5f, 0.0f, 0.5f},    // Bottom-right 
        {-0.5f, 0.0f, 0.5f},   // Bottom-left

        // back
        {-0.5f, 0.5f, -0.5f},   // Top-left
        {0.5f, 0.5f, -0.5f},    // Top-right
        {0.5f, 0.0f, -0.5f},   // Bottom-right
        {-0.5f, 0.0f, -0.5f}   // Bottom-left 
    };

    GLfloat VFloor2[8][3] = {
        // front
        {-0.5f, 0.0f, 0.5f},    // Top-left 
        {0.5f, 0.0f, 0.5f},     // Top-right 
        {0.5f, -0.5f, 0.5f},    // Bottom-right 
        {-0.5f, -0.5f, 0.5f},   // Bottom-left

        // back
        {-0.5f, 0.0f, -0.5f},   // Top-left
        {0.5f, 0.0f, -0.5f},    // Top-right
        {0.5f, -0.5f, -0.5f},   // Bottom-right
        {-0.5f, -0.5f, -0.5f}   // Bottom-left 
    };
    // first floor
    LIGHT_BLUE
    DrawSingleFloor(VFloor1[0], VFloor1[1], VFloor1[2], VFloor1[3], VFloor1[4], VFloor1[5], VFloor1[6], VFloor1[7]);
    // second floor
    LIGHT_GRAY
    DrawSingleFloor(VFloor2[0], VFloor2[1], VFloor2[2], VFloor2[3], VFloor2[4], VFloor2[5], VFloor2[6], VFloor2[7]);
}

void Draw3DBuilding() {
    // Draw the building components
    DrawRoof();
    DrawFloors();
    DrawWindows();
    DrawDoor();
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
        // TO BE IMPLEMENTED
        break;
    // close the door
    case 'c':
        // TO BE IMPLEMENTED
        break;
    // open the windows
    case 'O':
        // TO BE IMPLEMENTED
        break;
    // close the windows
    case 'C':
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
    glutInitWindowPosition(400, 50);
    // initialize window size (width, height)
    glutInitWindowSize(800, 700);
    // display mode initialization
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // create window
    glutCreateWindow("3D Building");
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