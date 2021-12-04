#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

// Initializing the initial parameters
void init (void)
{
  // color is set to grey
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


// function used for taking input as single lines and then split the line based on spaces to get the values of coordinates
vector<string> split(string s) {
	vector<string> out;
	string t = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			out.push_back(t);
			t = "";
		}
		else {
			t += s[i];
		}
	}
	if (t != "") {
		out.push_back(t);
	}
	return out;
}
// s is used to store the file you want to access
string s;
// Function for rasterization of objects/mesh models
void Rasterize (void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glScalef(0.3f, 0.3f, 0.3f);

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//Reading Data from File

	string Str;
	ifstream File(s);
	getline (File, Str);
  getline (File, Str);

	vector<string> t = split(Str);

	long int number_of_vertices = stoi(t[0]);
	long int number_of_triangles = stoi(t[1]);

	float vertexs[number_of_vertices][3];
	long int triangles[number_of_triangles][3];
  cout<<"Number of triangles: "<<number_of_triangles<<endl;
  cout<<"Number of Vertices: "<<number_of_vertices<<endl;

	for (long int i = 0; i < number_of_vertices; i++) {
		getline (File, Str);
		t = split(Str);

		vertexs[i][0] = stof(t[0]);
		vertexs[i][1] = stof(t[1]);
		vertexs[i][2] = stof(t[2]);
	}

	for (long int i = 0; i < number_of_triangles; i++) {

		getline (File, Str);
		t = split(Str);

		triangles[i][0] = stoi(t[1]);
		triangles[i][1] = stoi(t[2]);
		triangles[i][2] = stoi(t[3]);

	}
// closing the file
	File.close();


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//      Transforming the object w.r.t. the camera coordinate system.
	//      Camera cordinates are taken as 0,0,0 since it is given that camera and object are aligned if not change the cordinates.
	float camera_x = 0;
	float camera_y = 0;
	float camera_z = 0;

	cout<<"Camera coordinates are: "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
	if (camera_x==0 && camera_y==0 && camera_z==0)
  {
    cout<<"Camera coordinates are aligned with object"<<endl;
  }
	for (long int i = 0; i < number_of_vertices; i++) {
		vertexs[i][0] -= camera_x ;
		vertexs[i][1] -= camera_y ;
		vertexs[i][2] -= camera_z ;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//    Find oriented normal for each triangle.
	//     consider that U = p2 - p1
	//     and V = p3 - p1
	//     normal can be calculatd as N = U X V
	//     here x coordinates is Nx = UyVz - UzVy
	//     y coordinates is Ny = UzVx - UxVz
	//     z coordinates is Nz = UxVy - UyVx
	//

	cout<<"Calculating normals"<<endl;

	float nor[number_of_triangles][3];

	for (long int i = 0; i < number_of_triangles; i++) {

		float p1_x = vertexs[triangles[i][0]][0];
		float p1_y = vertexs[triangles[i][0]][1];
		float p1_z = vertexs[triangles[i][0]][2];

		float p2_x = vertexs[triangles[i][1]][0];
		float p2_y = vertexs[triangles[i][1]][1];
		float p2_z = vertexs[triangles[i][1]][2];

		float p3_x = vertexs[triangles[i][2]][0];
		float p3_y = vertexs[triangles[i][2]][1];
		float p3_z = vertexs[triangles[i][2]][2];


		float u_x = p2_x - p1_x;
		float u_y = p2_y - p1_y;
		float u_z = p2_z - p1_z;

		float v_x = p3_x - p1_x;
		float v_y = p3_y - p1_y;
		float v_z = p3_z - p1_z;

		nor[i][0] = u_y * v_z  - u_z * v_y ;
		nor[i][1] = u_z * v_x  - u_x * v_z ;
		nor[i][2] = u_x * v_y  - u_y * v_x ;

	}
cout<<"Calculating normals done"<<endl;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//         Determine the coordinates of the view frustum such that all the triangles lie in the view frustum.
//
//

	float x_min = vertexs[0][0];
	float x_max = vertexs[0][0];

	float y_min = vertexs[0][1];
	float y_max = vertexs[0][1];

	float z_min = vertexs[0][2];
	float z_max = vertexs[0][2];



	for (long int i = 0; i < number_of_vertices; i++) {

		if (vertexs[i][0] > x_max) x_max = vertexs[i][0];
		if (vertexs[i][0] < x_min) x_min = vertexs[i][0];

		if (vertexs[i][1] > y_max) y_max = vertexs[i][1];
		if (vertexs[i][1] < y_min) y_min = vertexs[i][1];

		if (vertexs[i][2] > z_max) z_max = vertexs[i][2];
		if (vertexs[i][2] < z_min) z_min = vertexs[i][2];

	}

	cout<<"For View frustum"<<endl;
	cout<<"X coordinates are: "<<x_max<<" "<<x_min<<endl;
	cout<<"Y coordinates are: "<<y_max<<" "<<y_min<<endl;
	cout<<"Z coordinates are: "<<z_max<<" "<<z_min<<endl;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//           Applying BackFace Culling Algorithm and Phong Shading
//            Light source is considered at -80,50,60
cout<<"Applying BackFace and Phong"<<endl;

	float light_x = -80;
	float light_y = 50;
	float light_z = 60;

	camera_x = 0;
	camera_y = 0;
	camera_z = 0;

	long int phong[number_of_triangles] = {0};
	long int backFace[number_of_triangles] = {0};

	for (long int i = 0; i < number_of_triangles; i++) {

		float c = light_x * nor[i][0] + light_y * nor[i][1] + light_z * nor[i][2];
		float n = camera_x * nor[i][0] + camera_y * nor[i][1] + camera_z * nor[i][2];

		if (c > 0) {
			phong[i] = 1;
		}

		if (n >= 0) {
			backFace[i] = 1;
		}

	}
cout<<"Applying BackFace and Phong done"<<endl;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Triangle Rasterization
//
cout<<"Rasterizing triangles"<<endl;
int x =9;
	glBegin(GL_TRIANGLES);

	for (long int i = 0; i < number_of_triangles; i++) {


		if (phong[i] == 1)glColor3f(0.8f, 0.9f, 0.0f);
		else glColor3f(0.0f, 0.0f, 0.0f);

		if (backFace[i] == 1) {
			int v1 = triangles[i][0];
			int v2 = triangles[i][1];
			int v3 = triangles[i][2];
			glVertex3f(vertexs[v1][0] /x, vertexs[v1][1] /x, vertexs[v1][2] /x);
			glVertex3f(vertexs[v2][0] /x, vertexs[v2][1] /x, vertexs[v2][2] /x);
			glVertex3f(vertexs[v3][0] /x, vertexs[v3][1] /x, vertexs[v3][2] /x);
		}
	}
	glEnd();
	glutSwapBuffers();
	cout<<"Rasterizing triangles done"<<endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Perspective Projection
// reshaping the object
void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, aspect, 0.1f, 100.0f);
}


int main (int argc, char** argv)
{
    int i;
    cout<<"1. Wolf"<<endl<<"2. Gorilla"<<endl<<"3. Cat"<<endl<<"4. Michael"<<endl<<"Enter your choice: 1,2,3,4"<<endl;
    cin>>i;
    switch(i)
    {
      case 3: s="cat01.off";
                    break;
      case 1: s="wolf02.off";
                    break;
      case 2: s="gorilla05.off";
                    break;
      case 4: s="michael18.off";
                    break;
      default: cout<<"Incorrect choice..."<<endl;
                    break;
    }
  glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (0,0);
	glutInitWindowSize (1000, 1000);
	glutCreateWindow("CSL7450: Assignment 2 ");
	glutReshapeFunc(reshape);
	init();
	glutDisplayFunc (Rasterize);
	glutMainLoop();
}
