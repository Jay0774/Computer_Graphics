#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;

void Init_window (void)
{
    glClearColor(1.0, 1.0, 1.0,1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
void Circle_Integer (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    int x,y,r,d,x0,y0,e,se;
    r=100;
    x0=200;
    y0=200;
    x=-0.70*r;
    y=0.70*r;
    d=1-1.5*0.7*r;
    e=-2*y+3;
    se=5-2*(y+x);
    glVertex2i(x+x0,y+y0);
    //cout<<d<<" "<<x<<" "<<y<<endl;
    while (y>=0)
    {
        if(d>0)
        {
            d+=e;
            y=y-1;
            e=e+2;
            se=se+2;
            //cout<<d<<" "<<x<<" "<<y<<endl;
        }
        else
        {
            d+=se;
            y=y-1;
            x=x-1;
            e=e+2;
            se=se+4;
            //cout<<d<<" "<<x<<" "<<y<<endl;
        }
        glVertex2i(x+x0,y+y0);
        //cout<<"("<<x+x0<<" "<<y+y0<<")"<<endl;
    }
    //int x,y,r,d,x0,y0,e,se;
    r=100;
    x0=200;
    y0=200;
    x=-r-1;
    y=0;
    d=1+2*r;
    glVertex2i(x+x0,y+y0);
    //cout<<d<<" "<<x<<" "<<y<<endl;
    while (y>-0.57*r)
    {
        if(d<0)
        {
            d+=-2*y+3;
            y=y-1;
            //cout<<d<<" "<<x<<" "<<y<<endl;
        }
        else
        {
            d+=5-2*(y-x);
            y=y-1;
            x=x+1;
            //cout<<d<<" "<<x<<" "<<y<<endl;
        }
        glVertex2i(x+x0,y+y0);
        //cout<<"("<<x+x0<<" "<<y+y0<<")"<<endl;
    }
    glEnd();
    glFlush();
}
int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle Drawing using mid point algorithm");
    Init_window();
    glutDisplayFunc(Circle_Integer);
    glutMainLoop();
}
