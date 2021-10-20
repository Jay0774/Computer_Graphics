#include <GL/glut.h> // (or others, depending on the system in use)
#include <iostream>
#include <math.h>
using namespace std;
int a1,a2,a3,b1,b2,b3;
void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // display window color .
    glMatrixMode (GL_PROJECTION); // projection parameters.
    glLoadIdentity();
    gluOrtho2D (0,500,0,500);
}
float area_of_given_triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}
bool is_point_Inside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
   float a = area_of_given_triangle (x1, y1, x2, y2, x3, y3);
   float a1 = area_of_given_triangle (x, y, x2, y2, x3, y3);
   float a2 = area_of_given_triangle (x1, y1, x, y, x3, y3);
   float a3 = area_of_given_triangle (x1, y1, x2, y2, x, y);
   return (a == a1 + a2 + a3);
}
int minimum(int x0,int x1,int x2)
{
    int x_min;
    if(x0<=x1&&x0<=x2)
        x_min=x0;
    else if(x1<=x0&&x1<=x2)
        x_min=x1;
    else
        x_min=x2;
    return x_min;
}
int maximum(int x0,int x1, int x2)
{
    int x_max;
    if(x0>=x1&&x0>=x2)
        x_max=x0;
    else if(x1>=x0&&x1>=x2)
        x_max=x1;
    else
        x_max=x2;
    return x_max;
}
void draw_edges (int x0,int y0,int x1,int y1,int x2,int y2)
{
    glBegin (GL_LINES);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(x0,y0);
    glVertex2i(x1,y1);
    glEnd();
    glBegin (GL_LINES);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(x0,y0);
    glVertex2i(x2,y2);
    glEnd();
    glBegin (GL_LINES);
    glColor3f (1.0, 0.0, 0.0);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
}
void draw_bounding_box(int x_min,int x_max,int y_min,int y_max,int res)
{
    x_min*=res;
    x_max*=res;
    y_min*=res;
    y_max*=res;
    glBegin (GL_LINES);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(x_min,y_min);
    glVertex2i(x_min,y_max);
    glEnd();
    glBegin (GL_LINES);
    glColor3f (.0, 1.0, 0.0);
    glVertex2i(x_max,y_min);
    glVertex2i(x_max,y_max);
    glEnd();
    glBegin (GL_LINES);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(x_min,y_min);
    glVertex2i(x_max,y_min);
    glEnd();
    glBegin (GL_LINES);
    glColor3f (0.0, 1.0, 0.0);
    glVertex2i(x_min,y_max);
    glVertex2i(x_max,y_max);
    glEnd();
}
void Triangle_drawing (void)
{
    glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
    int x0,y0,x1,y1,x2,y2,dx[3],dy[3],x_min,x_max,y_min,y_max,q,f0,f1,f2,x,y,g0,g1,g2,res=1;
    x0=a1;
    y0=b1;
    x1=a2;
    y1=b2;
    x2=a3;
    y2=b3;

    // code for Drawing the edges.
    //draw_edges(x0,y0,x1,y1,x2,y2);

    x_min = minimum(x0,x1,x2);
    y_min = minimum(y0,y1,y2);
    x_max = maximum(x0,x1,x2);
    y_max = maximum(y0,y1,y2);
    cout<<"y Min = "<<y_min<<endl;
    cout<<"y Max = "<<y_max<<endl;
    cout<<"x Min = "<<x_min<<endl;
    cout<<"x Max = "<<x_max<<endl;

    // code for drawing the bounding box
    draw_bounding_box(x_min,x_max,y_min,y_max,res);

    // code for drawing the triangle
    glBegin(GL_POINTS);
    /*
    dx[0] = x1-x0;
    dx[1] = x2-x1;
    dx[2] = x0-x2;
    dy[0] = y1-y0;
    dy[1] = y2-y1;
    dy[2] = y0-y2;
    q = x_max-x_min;
    f0 = (x_min-x0)*dy[0]-(y_max-y0)*dx[0];
    f1 = (x_min-x1)*dy[1]-(y_max-y1)*dx[1];
    f2 = (x_min-x1)*dy[2]-(y_max-y2)*dx[2];
    cout<<dx[0]<<" "<<dx[1]<<" "<<dx[2]<<endl;
    cout<<dy[0]<<" "<<dy[1]<<" "<<dy[2]<<endl;
    cout<<f0<<" "<<f1<<" "<<f2<<endl;

    for (y=y_max;y>=y_min;y--)
    {
        for (x=x_min;x<=x_max;x++)
        {
            cout<<x<<" "<<y<<endl;
            if(f0<0 && f1>0 && f2<0)
              glVertex2i(x,y);
            f0+=dy[0];
            f1+=dy[1];
            f2+=dy[2];
            cout<<f0<<" "<<f1<<" "<<f2<<endl;
        }
        f0-=q*dy[0];
        f1-=q*dy[1];
        f2-=q*dy[2];
        f0+=dx[0];
        f1+=dx[1];
        f2+=dx[2];
        cout<<f0<<" "<<f1<<" "<<f2<<endl;
    }
    */

    // each pixel is divided into 2 parts since 2x is used then the percentage is calculated by checking the pixels that lie inside the triangle
    int count=0;
    for (y=y_min;y<=y_max;y++)
    {
        for (x=x_min;x<=x_max;x++)
        {
            count=0;
            if(is_point_Inside(x0,y0,x1,y1,x2,y2,x,y))
                count++;
            if(is_point_Inside(x0,y0,x1,y1,x2,y2,x+1,y+1))
                count++;
            //cout<<x<<" "<<y<<endl;
            //cout<<pointInTriangle(x0,y0,x1,y1,x2,y2,x,y)<<endl;
            if(count==1)
            {
                glColor3f (0.0,1.0,1.0);
                glVertex2i(x,y);
            }
            else if(count==2)
            {
                glColor3f (0.0, 1.0,1.0);
                glVertex2i(x,y);
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
    cout<<"Enter First Point:"<<endl;
    cin>>a1>>b1;
    cout<<"Enter Second Point:"<<endl;
    cin>>a2>>b2;
    cout<<"Enter Third Point:"<<endl;
    cin>>a3>>b3;
    cout<<"Green color for bounding box."<<endl;
    cout<<"Red color for Triangle edges."<<endl;
    cout<<"Blue color for Triangle."<<endl;
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
    glutInitWindowPosition (10, 30); // Set top-left display-window position.
    glutInitWindowSize (500, 500); // Set display-window width and height.
    glutCreateWindow ("Triangle Drawing"); // Create display window.
    init ( ); // Execute initialization procedure.
    glutDisplayFunc (Triangle_drawing); // Send graphics to display window.
    glutMainLoop ( ); // Display everything and wait.
}
