/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

 #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<math.h>

GLfloat ya=50,xa=10;
//the animation part
//we keep moving the points and create a wigling flag

int yFlag = 1,xFlag=1,AniFlag=1;
void Animate()
{
    if(AniFlag==1)
    {
        if(ya>-50 && yFlag==1)
    {
         ya=ya-0.2;
    }
    if(ya<=-50 && yFlag==1)
    {
        yFlag=0;
    }
    if(ya<50 && yFlag == 0)
    {
        ya=ya+0.2;
    }
    if(ya>=50 && yFlag==0)
    {
        yFlag=1;
    }

    if(xa>-50 && xFlag==1)
    {
         xa=xa-0.2;
    }
    if(xa<=-50 && xFlag==1)
    {
        xFlag=0;
    }
    if(xa<50 && xFlag == 0)
    {
        xa=xa+0.2;
    }
    if(xa>=50 && xFlag==0)
    {
        xFlag=1;
    }
    }

    glutPostRedisplay();

}
void Draw()
{
    GLfloat x[4];
    GLfloat y1[4];
    GLfloat y2[4];
    GLfloat y3[4];
    GLdouble xt[200],y1t[200],y2t[200],y3t[200],t;
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    x[0]=100;
    x[1]=200;
    x[2]=200;
    x[3]=300;
    y1[0]=450;
    y1[1]=450+ya;
    y1[2]=450-ya;
    y1[3]=450;
    y2[0]=400;
    y2[1]=400+ya;
    y2[2]=400-ya;
    y2[3]=400;
    y3[0]=350;
    y3[1]=350+ya;
    y3[2]=350-ya;
    y3[3]=350;

    for(i=0,t=0;t<=1;i++,t=t+0.01)
    {
        xt[i]=pow(1-t,3)*x[0]+3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t,3)*x[3];
        //to form a rectangular strip
        //2 strips then 3 values
        y1t[i]=pow(1-t,3)*y1[0]+3*t*pow(1-t,2)*y1[1]+3*pow(t,2)*(1-t)*y1[2]+pow(t,3)*y1[3];
        y2t[i]=pow(1-t,3)*y2[0]+3*t*pow(1-t,2)*y2[1]+3*pow(t,2)*(1-t)*y2[2]+pow(t,3)*y2[3];
        y3t[i]=pow(1-t,3)*y3[0]+3*t*pow(1-t,2)*y3[1]+3*pow(t,2)*(1-t)*y3[2]+pow(t,3)*y3[3];
    }
    //glPointSize(3);
    //function to draw first strip
    glColor3f(1,0,0);
    glBegin(GL_QUAD_STRIP);
        for(i=0;i<200;i++)
        {
            glVertex2d(xt[i],y1t[i]);
            glVertex2d(xt[i],y2t[i]);
        }
    glEnd();
    //function to draw second strip
    glColor3f(0,1,0);
    glBegin(GL_QUAD_STRIP);
        for(i=0;i<200;i++)
        {
            glVertex2d(xt[i],y2t[i]);
            glVertex2d(xt[i],y3t[i]);
        }
    glEnd();

    //for the pole
    glColor3f(1,1,1);
    glRecti(90,450,100,50);
    glFlush();
}

void Menu(int n)
{
    if(n==1)
    {
        AniFlag=1;
    }
    else if (n==2)
    {
        AniFlag=0;
    }
    if(n==3)
    {
        exit(0);
    }
    glutPostRedisplay();
}
void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);

    //menu
    glutCreateMenu(Menu);
    glutAddMenuEntry("start",1);
    glutAddMenuEntry("stop",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("animate flag");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Animate);
    glutMainLoop();
    return 0;
}
