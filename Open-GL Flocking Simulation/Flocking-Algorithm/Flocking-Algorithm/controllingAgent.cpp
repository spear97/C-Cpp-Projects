//#include <windows.h>
//#pragma comment(lib, "user32.lib") 

/*INCLUDES AND NAMESPACES TO USE*/

#include <GL/glut.h>  
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

#include "Color.h"
#include "Vector.h"
using namespace mathtool;
#include "Simulator.h"
#include "Environment.h"

/*GLOBAL VARIABLES*/

double theta = 0;
double speedTheta = 0.1;
double alpha = 0.5;

int drawMode=1;
int numDraws = 0;
int windowW = 800;
int windowH = 800;
int homeX, homeY;
int timeSincePress = 0;
int changeY = 0;
int changeX = 0;
static int window_id;
static int menu_id;

bool isConvex = true;
bool isSimulating = false;
bool isFollowing = false;
bool addIndividual = true;
bool addGroup = false;
bool addAttractionPt = false;
bool addAdversary = false;
bool mousePressed = false;

vector<MyColor> colors;
MyColor bColor(0.49,0.80,1);
Simulator gSim;
Environment* gEnv=NULL;
Vector3d followPt;

/*PROTOTYPES*/
void init();
void setFollowCamera();
void menu(int num);
void createMenu();
void update();
void customDraw();
void mousebutton(int button, int state, int x, int y);
void setBackgroundColor(int colorIndex, double colorDif, double colorRange);
void keyboard(unsigned char key, int x, int y);
void otherKeyInput(int key, int x, int y);
////////////////////

/*FUNCTIONS*/

//Setups Top-Down View
void init() 
{
	glClearColor(bColor.r, bColor.g, bColor.b, 0.0); //Set display-window color to white.
	glMatrixMode(GL_PROJECTION);      //Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(-windowW/2,windowW/2, -windowH/2, windowH/2);
	if( gEnv == NULL ) gEnv = new Environment("env.txt", -windowW / 2, windowW / 2, -windowH / 2, windowH / 2);
}

//Sets Camera to follow a particular agent
void setFollowCamera() 
{
	glMatrixMode(GL_PROJECTION);      //Set projection parameters.
	glLoadIdentity();
	double newXMin = followPt[0] - windowW/10;
	double newXMax = followPt[0] + windowW/10;
	double newYMin = followPt[1] - windowH/10;
	double newYMax = followPt[1] + windowH/10;
	gluOrtho2D(newXMin, newXMax, newYMin, newYMax);
}

//Menu Functionality
void menu(int num) 
{
	string fileToLoad="";
	bool fileSpecified = false;

	switch (num)
	{
		//Terminate the Simulation
		case 0:
			glutDestroyWindow(window_id);
			exit(0);
			break;

		//Add a Single Agent into the Environment
		case 1:
			addIndividual = true;
			addGroup = false;
			addAttractionPt = false;
			break;

		//Add a Group of Agents into the Environment
		case 2:
			addIndividual = false;
			addGroup = true;
			addAttractionPt = false;
			break;

		//Add an Attraction Point into the Environment
		case 3:
			addAttractionPt = true;
			addIndividual = false;
			addGroup = false;
			break;

		//Set Next Spawned Agents to be Adversaries, or not to be Adversaries
		case 4:
			addAdversary = !addAdversary;
			break;
	}
}

//Allows for creation of a Menu
void createMenu() 
{
	menu_id = glutCreateMenu(menu);
		glutAddMenuEntry("Toggle Adversary", 4);
		glutAddMenuEntry("Add Attraction Point", 3);
		glutAddMenuEntry("Add Group", 2);
		glutAddMenuEntry("Add Indiv.", 1);
		glutAddMenuEntry("Quit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//Updates Simulation
void update() 
{
	if (isSimulating)
	{
		gSim.Update();
	} 

	if( mousePressed ) 
	{
		speedTheta = changeY*0.2;
		timeSincePress += 1;
	}

	if( isFollowing ) 
	{
		followPt = gSim.GetPointToFollow();
		setFollowCamera();
	}

	customDraw();
}

//Determines how the entire program will be rendered
void customDraw() 
{
	  glClearColor(bColor.r, bColor.g, bColor.b, 0.0); //Set display-window color to white.
	  glClear(GL_COLOR_BUFFER_BIT);     //Clear display window.

	  gEnv->Draw();
	  gSim.Draw();

	  glFlush();                        //Process all OpenGL routines as quickly as possible.
}

//What will occur when the mouse button is pressed?
void mousebutton(int button, int state, int x, int y)
{
	//When Mouse Button is pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		if( !mousePressed ) 
		{
			homeX = x;
			homeY = y;
			timeSincePress = 0;
		}

		double tx = -windowW/2 + (1.0*x/windowW)*(windowW);
		double ty = -windowH/2 + ((1.0*windowH-y)/windowH)*(windowH);

		if (addIndividual)
		{
			gSim.AddMember(-1, tx, ty, addAdversary);
		}
     
		else if (addGroup)
		{
			for (int i = 0; i < 5; i++)
			{
				gSim.AddMember(-1, tx, ty, addAdversary);
			}
		}
     
		else if( addAttractionPt ) 
		{
			gEnv->AddAttractionPoint(tx,ty);
		}
		mousePressed = true;
		glutPostRedisplay();
	}

	//When Mouse Button is released
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		theta = theta+timeSincePress*speedTheta;
		speedTheta = 1;
		changeY = 0;
		mousePressed = false;
		timeSincePress = 0;
	}
}

//Set BackgroundColor of the Simulation
void setBackgroundColor(int colorIndex, double colorDif, double colorRange) 
{
	colorIndex = (colorIndex >= colors.size()) ? colors.size() - 1 : colorIndex;
	
	MyColor& c_i = colors[colorIndex];

	int j = ((colorIndex + 1) >= colors.size()) ? colors.size() - 1 : colorIndex + 1;
	
	MyColor& c_j = colors[j];

	double s = colorDif / colorRange;	
	double tr = (1-s)*c_i.r + s*c_j.r;
	double tg = (1-s)*c_i.g + s*c_j.g;
	double tb = (1-s)*c_i.b + s*c_j.b;

	bColor.r = tr;	
	bColor.g = tg;	
	bColor.b = tb;	
}

//What will occur when keyboard input is received?
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
	  //Terminate Simulation
	  case 'q':
		exit(0);
		break;

	  case 27:	// ESCAPE key
		exit(0);
		break;
	  ////////////////

	  //Toggle Simulation to run or not run
	  case ' ':
		isSimulating = !isSimulating; 
		break;
	  ////////////////

	  //Refresh Simulation Screen
	  case 'f':
  		isSimulating = true;
		update();
		isSimulating = false;
  		break;
	  //////////////

	  //Draw Agent as a Fish
	  case '1':
		drawMode = 1; 
		break;
	  //////////

	  //Draw Agent as a Triangle
	  case '2':
		drawMode = 2; 
		break;
	  /////////

	  //Draw Agent as a Circle
	  case '3':
		drawMode = 3; 
		break;
	  ////////
  }
}

//The Driver for the simulation
int main(int argc, char** argv) 
{
	glutInit(&argc, argv);							//Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   //Set display mode.
	glutInitWindowSize(windowW, windowH);           //Set display-window width and height.
	window_id = glutCreateWindow("Flocking Simulator");  //Create display window.

	init();                                        //Execute initialization procedure.

	createMenu();
	glutIdleFunc(update);
	glutDisplayFunc(customDraw);                   //Send graphics to display window.
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mousebutton);                    //How to handle mouse press events. 
	glutMainLoop();                                //Display everything and wait.
}
//////////////////////////////////////////////////////////////////////////////////////////////