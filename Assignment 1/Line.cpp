#include <GL/glut.h> // (or others, depending on the system in use)
#include <iostream>
#include <math.h>
using namespace std;
int a,b,c,e;
void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // display window color .
    glMatrixMode (GL_PROJECTION); // projection parameters.
    glLoadIdentity();
    gluOrtho2D (0,500,0,500);
}
void Line_drawing (void)
{
    glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f (0.0, 0.0, 0.0);
    glBegin (GL_POINTS);

    int x0,y0,x1,y1,de,dne,x,y,d,m;
    x0=a;
    y0=b;
    x1=c;
    y1=e;
    cout<<"Start Point = "<<x0<<","<<y0<<endl;
    cout<<"End Point = "<<x1<<","<<y1<<endl;
    int dx=x1-x0;
    int dy=y1-y0;
    if((dx>0 && dy>0)||(dx<0 && dy<0))
        m = 1;
    else
        m=-1;
    cout<<dy<<endl;
    cout<<dx<<endl;
    if (dx==0)
    {
        cout<<"Slope = infinity"<<endl;
        if(y0>y1)
            swap(y0,y1);
        for (int i=y0;i<=y1;i++)
        glVertex2i(x0,i);

    }
    else if (dy==0)
    {
        cout<<"Slope = 0"<<endl;
        if(x0>x1)
            swap(x0,x1);
        for (int i=x0;i<=x1;i++)
        glVertex2i(i,y0);
    }
    else if (m>0)
    {
        dx = abs(dx);
        dy = abs(dy);
        cout<<"Positive Slope"<<endl;
        if (dy<=dx)
        {
            cout<<"Slope < 1"<<endl;
            if(x0>x1)
            {
                swap(x0,x1);
                swap(y0,y1);
            }
                dx=x1-x0;
                dy=y1-y0;
                d=2*dy - dx;
                de=2*dy;
                dne = 2*(dy-dx);
                x=x0;
                y=y0;
                glVertex2i(x, y);
                while (x<=x1)
                {
                    if (d<=0)
                    {
                        d = d + de;
                        x++;
                    }
                    else
                    {
                        d = d + dne;
                        x++;
                        y++;
                    }
                glVertex2i(x, y);
                }
        }
        else if(dy>dx)
        {
            cout<<"Slope > 1"<<endl;
            if(y0>y1)
            {
                swap(x0,x1);
                swap(y0,y1);
            }
                dx=x1-x0;
                dy=y1-y0;
                d=dy - 2*dx;
                de=-2*dx;
                dne = 2*(dy-dx);
                x=x0;
                y=y0;
                glVertex2i(x, y);
                while (y<=y1)
                {
                    if (d>=0)
                    {
                        d = d + de;
                        y++;
                    }
                    else
                    {
                        d = d + dne;
                        x++;
                        y++;
                    }
                glVertex2i(x, y);
                }
        }
    }
    else
    {

        dx = abs(dx);
        dy = abs(dy);
        cout<<"Negative Slope"<<endl;
        if (dy<=dx)
        {
            cout<<"Slope > -1"<<endl;
            if(x0>x1)
            {
                swap(x0,x1);
                swap(y0,y1);
            }
            dx=x1-x0;
            dy=y1-y0;
            d=-2*dy - dx;
            de=-2*dy;
            dne = -2*(dy+dx);
            x=x0;
            y=y0;
            glVertex2i(x, y);
            while (x<=x1)
            {
                if (d<=0)
                {
                    d = d + de;
                    x++;
                }
                else
                {
                    d = d + dne;
                    x++;
                    y--;
                }
            glVertex2i(x, y);
            }
        }
        else if(dy>dx)
        {
            cout<<"Slope < -1"<<endl;
            if(y0>y1)
            {
                swap(x0,x1);
                swap(y0,y1);
            }
                dx=x1-x0;
                dy=y1-y0;
                d=-dy - 2*dx;
                de=2*dx;
                dne = 2*(dy-dx);
                x=x0;
                y=y0;
                glVertex2i(x, y);
                while (y<=y1)
                {
                    if (d>=0)
                    {
                        d = d + de;
                        y++;
                    }
                    else
                    {
                        d = d + dne;
                        x--;
                        y++;
                    }
                glVertex2i(x, y);
                }
        }

    }
    glEnd();
    /* Checking for correctness
    glBegin (GL_LINES);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(x0,y0);
    glVertex2i(x1,y1);
    glEnd ( );
    */
    glFlush ( );
}
int main (int argc, char** argv)
{
    cout<<"Enter First Coordinate:"<<endl;
    cin>>a>>b;
    cout<<"Enter Second Coordinate:"<<endl;
    cin>>c>>e;
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
    glutInitWindowPosition (10, 30); // Set top-left display-window position.
    glutInitWindowSize (500, 500); // Set display-window width and height.
    glutCreateWindow ("Line Drawing Midpoint Integer Arithmetic"); // Create display window.
    init ( ); // Execute initialization procedure
    glutDisplayFunc (Line_drawing); // Send graphics to display window.
    glutMainLoop ( ); // Display everything and wait.
}
