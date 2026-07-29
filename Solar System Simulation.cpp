#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


static int m = 0, M = 0, v = 0, V = 0, E = 0, e = 0, r = 0, R = 0;
static int j = 0, J = 0, s = 0, S = 0, U = 0, u = 0, n = 0, N = 0;
static int X = 0, z = 0, b = 0;

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

void myinit(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

    // إ (موقع الشمس)
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void update(int value) {
    z = (z + 1) % 360;

    M = (M + 4) % 360; m = (m + 2) % 360; // عطارد
    V = (V + 3) % 360; v = (v + 2) % 360; // الزهرة
    E = (E + 2) % 360; e = (e + 3) % 360; // الأرض
    X = (X + 6) % 360;                   // القمر
    R = (R + 1) % 360; r = (r + 3) % 360; // المريخ
    J = (J + 1) % 360; j = (j + 4) % 360; // المشتري
    S = (S + 1) % 360; s = (s + 2) % 360; // زحل
    U = (U + 1) % 360; u = (u + 2) % 360; // أورانوس
    N = (N + 1) % 360; n = (n + 2) % 360; // نبتون

    b = (b + 1) % 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); 
}


void drawOrbit(float radius) {
    glDisable(GL_LIGHTING);
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159f / 180.0f;
        glVertex3f(cos(rad) * radius, 0.0f, sin(rad) * radius);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 12.0, 16.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glDisable(GL_LIGHTING); // جعل الشمس مضيئة بنفسها
    glRotatef((GLfloat)z, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.6, 0.0); // لون برتقالي/ذهبي
    glutSolidSphere(0.9, 40, 16);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //  (Mercury) 
    drawOrbit(1.8);
    glPushMatrix();
    glRotatef((GLfloat)M, 0.0, 1.0, 0.0); // الدوران حول الشمس
    glTranslatef(1.8, 0.0, 0.0);           // البعد عن المركز
    glRotatef((GLfloat)m, 0.0, 1.0, 0.0); // الدوران حول المحور
    glColor3f(0.7, 0.7, 0.7);
    glutSolidSphere(0.12, 20, 8);
    glPopMatrix();

    //  (Venus) 
    drawOrbit(2.6);
    glPushMatrix();
    glRotatef((GLfloat)V, 0.0, 1.0, 0.0);
    glTranslatef(2.6, 0.0, 0.0);
    glRotatef((GLfloat)v, 0.0, 1.0, 0.0);
    glColor3f(0.9, 0.6, 0.2);
    glutSolidSphere(0.18, 20, 8);
    glPopMatrix();

    // (Earth & Moon) 
    drawOrbit(3.6);
    glPushMatrix();
    glRotatef((GLfloat)E, 0.0, 1.0, 0.0);
    glTranslatef(3.6, 0.0, 0.0);

    // رسم الأرض
    glPushMatrix();
    glRotatef((GLfloat)e, 0.0, 1.0, 0.0);
    glColor3f(0.1, 0.5, 0.9);
    glutSolidSphere(0.22, 20, 8);
    glPopMatrix();

    // رسم القمر 
    glRotatef((GLfloat)X, 0.0, 1.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    glColor3f(0.8, 0.8, 0.8);
    glutSolidSphere(0.06, 10, 6);
    glPopMatrix();

    //  (Mars)
    drawOrbit(4.6);
    glPushMatrix();
    glRotatef((GLfloat)R, 0.0, 1.0, 0.0);
    glTranslatef(4.6, 0.0, 0.0);
    glRotatef((GLfloat)r, 0.0, 1.0, 0.0);
    glColor3f(0.9, 0.3, 0.1);
    glutSolidSphere(0.15, 20, 8);
    glPopMatrix();

    // (Jupiter)
    drawOrbit(6.0);
    glPushMatrix();
    glRotatef((GLfloat)J, 0.0, 1.0, 0.0);
    glTranslatef(6.0, 0.0, 0.0);
    glRotatef((GLfloat)j, 0.0, 1.0, 0.0);
    glColor3f(0.8, 0.6, 0.4);
    glutSolidSphere(0.45, 20, 16);
    glPopMatrix();

    //  (Saturn) 
    drawOrbit(7.5);
    glPushMatrix();
    glRotatef((GLfloat)S, 0.0, 1.0, 0.0);
    glTranslatef(7.5, 0.0, 0.0);
    glRotatef((GLfloat)s, 0.0, 1.0, 0.0);

    // الكوكب
    glColor3f(0.8, 0.7, 0.4);
    glutSolidSphere(0.35, 20, 16);

    // حلقات زحل
    glDisable(GL_LIGHTING);
    glColor3f(0.6, 0.5, 0.3);
    glRotatef(70.0, 1.0, 0.0, 0.0);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex3f(sin(rad) * 0.45, cos(rad) * 0.45, 0.0);
        glVertex3f(sin(rad) * 0.65, cos(rad) * 0.65, 0.0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //  (Uranus) 

    drawOrbit(8.8);
    glPushMatrix();
    glRotatef((GLfloat)U, 0.0, 1.0, 0.0);
    glTranslatef(8.8, 0.0, 0.0);
    glRotatef((GLfloat)u, 0.0, 1.0, 0.0);
    glColor3f(0.4, 0.7, 0.9);
    glutSolidSphere(0.3, 20, 16);
    glPopMatrix();

    // (Neptune) 

    drawOrbit(10.0);
    glPushMatrix();
    glRotatef((GLfloat)N, 0.0, 1.0, 0.0);
    glTranslatef(10.0, 0.0, 0.0);
    glRotatef((GLfloat)n, 0.0, 1.0, 0.0);
    glColor3f(0.2, 0.3, 0.9);
    glutSolidSphere(0.28, 20, 16);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Solar System 3D Simulation Mikhail ");

    myinit();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}