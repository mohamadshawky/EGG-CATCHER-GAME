#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<cmath>
#include <ctime>
#include<Windows.h>
#include <gl/stb_image.h>
#include<gl/glut.h>
#include <sstream>
#include <stdlib.h>
#include<cstdlib>
			
GLfloat
lightamb[] = { 1,1,1,1 },
lightdiff[] = { .6,.6,0,1 },
lightspec[] = { .2,.2,.2,1 },
lightPos[] = { 0.0, 1.0, -3.0, 1.0 };
GLfloat amb[] = { 1.0f,1.0f,0.0f,1.0f };
GLfloat diff[] = { 1.0f,1.0f,0.0f,1.0f };
GLfloat spec[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat shine[] = { 75.0f };

int selected;
int score, miss = 20;
bool basket1 = true, basket2 = false, basket3 = false, basket4 = false;
float screenLeft, screenRight,screenBottom, screenTop;

int y = 20;
bool changecolor = false;
float basketX = 0, basketY = 0, basketZ = 0;
unsigned int texture;
int width, height, nrChannels;
unsigned char *data = NULL;
bool fullScreen;
float ratio;

void background();
void mydraw();
void reshape(int, int);
void timer(int);
void timer2(int);
void timer3(int v);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);
void load(int imgnum);
void check(unsigned char *data);
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius);
void drawBasket(int, int, int);
void print(float x, float y, char *string);


void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	glutCreateWindow(" Egg Catcher ");
	background();
	glutDisplayFunc(mydraw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, timer2, 0);
	glutTimerFunc(0, timer3, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	
	
	
	glutMainLoop();
}

void background() {
	glClearColor(0, 0, 0, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightamb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightspec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiff);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);


}

void mydraw() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1, 1, 1);
	glLoadIdentity();
	glRotated(20, 1, 1, 0);
	glTranslatef(40,51, -9);
	glColor4f(1, 1, 0, 1);
	glutSolidSphere(.1, 50, 10);
	glLoadIdentity();
	glTranslatef(0, 0, -53);
	load(3);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(0, 0);//

	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(width, 0);


	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(width, height);//

	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(0, height);//

	glEnd();

	glDisable(GL_TEXTURE_2D);
	

	glEnable(GL_TEXTURE_2D);
	if (basket1)
	{
		glLoadIdentity();
		glTranslatef(5, 4.5, -5);
		glScalef(.8, 1.4, .1);
		drawBasket(basketX, basketY, basketZ);
	}
	if (basket2)
	{

		glLoadIdentity();
		glTranslatef(18, 5, -5);
		glScalef(-.5, 1.5, .2);
		drawBasket(basketX, basketY, basketZ);
	}
	if (basket3)
	{
		glLoadIdentity();
		glTranslatef(32, 5, -5);
		glScalef(.4, 1.55, .15);
		drawBasket(basketX, basketY, basketZ);
	}
	if (basket4)
	{
		glLoadIdentity();
		glTranslatef(47, 5, -5);
		glScalef(.5, 1.6, .1);
		drawBasket(basketX, basketY, basketZ);
	}


	glDisable(GL_TEXTURE_2D);
	glLoadIdentity();
	glTranslatef(0, 0, -3);

	if ((selected == 1) && (y >= 1)) {
		drawFilledCircle(2.6, y, .27);
		y--;
		if ((basket1 == true) && (y <= 4)) {
			score += 10;
			y = -10;
			PlaySound(TEXT("Egg-Catcher-PC-browser-game-2.wav"), NULL, SND_ASYNC);

		}
	}
	
	if (selected == 2 && y >= 1) {
		drawFilledCircle(10.5, y, .27);
		y--;
		if ((basket2 == true) && (y <= 4)) {
			score+=10;
			y = -10;
			PlaySound(TEXT("Egg-Catcher-PC-browser-game-2.wav"), NULL, SND_ASYNC);
			
		}
	}
	

	if (selected == 3 && y >= 1) {
		drawFilledCircle(18.9, y, .27);
		y--;
		if ((basket3 == true) && (y <= 4)) {
			score+=10;
			y = -10;
			PlaySound(TEXT("Egg-Catcher-PC-browser-game-2.wav"), NULL, SND_ASYNC);
			
		}
	}
	
	if (selected == 4 && y >= 1) {
		drawFilledCircle(27.5, y, .27);
		y--;
		if ((basket4 == true) && (y <= 4)) {
			score+=10;
			y = -10;
			PlaySound(TEXT("Egg-Catcher-PC-browser-game-2.wav"), NULL, SND_ASYNC);
			
		}
	}
	if (y == 0)
		miss--;
	
	if(miss == -1)
	{
		int result = MessageBox(NULL, TEXT("Game Over"), TEXT("GameEnd!"), MB_RETRYCANCEL | MB_ICONEXCLAMATION);
		if (result == IDRETRY) {
			miss = 20;
			score = 0;
			glutTimerFunc(1500, timer2, 0);

		}
		else {
			exit(0);
		}
	}
	

	if (changecolor == false) 
		glColor3f(1, 1, 1);
		

	if (changecolor == true) 
		glColor3f(1, 0, 1);
		
	
	char text[64]= "Score : ";
	char integer_string[32];
	sprintf_s(integer_string, "%d", score);
	strcat_s(text, integer_string);
	print(.5, 29,text);

	

	char text2[64]="Miss : ";
	char integer_string2[32];
	sprintf_s(integer_string2, "%d", miss);
	strcat_s(text2, integer_string2);
	print(27.5, 29, text2);

	glutSwapBuffers();
}

void reshape(int w, int h) {
	

	
	if (h == 0) h = 1;
	ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(0, 10, 0, 10, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(5, timer, 0);
	y--;


}
void timer2(int v) {
	
	glutTimerFunc(1500, timer2, 0);
	srand(time(NULL));
	selected = rand() % ((4 - 1) + 1) + 1;
	y = 20;
	
}
void timer3(int v) {
	
	glutTimerFunc(1000, timer3, 0);
	changecolor = !changecolor;
}

void keyboard(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
	else if (key == 65 || key == 97)
	{
		basket1 = true;
		basket2 = false;
		basket3 = false;
		basket4 = false;
	}
	else if (key == 83 || key == 115)
	{
		basket1 = false;
		basket2 = true;
		basket3 = false;
		basket4 = false;
	}
	else if (key == 68 || key == 100)
	{
		basket1 = false;
		basket2 = false;
		basket3 = true;
		basket4 = false;
	}
	else if (key == 70 || key == 102)
	{
		basket1 = false;
		basket2 = false;
		basket3 = false;
		basket4 = true;
	}
}

void specialKeyboard(int key, int x, int y) {

	if (key == GLUT_KEY_F1) {
		fullScreen = !fullScreen;
		if (fullScreen)
			glutFullScreen();
		else {
			glutPositionWindow(10, 10);
			glutReshapeWindow(600, 600);
		}
	}

	

}



void load(int imgnum) {
	if (imgnum == 3) {

		data = stbi_load("123crop2.bmp", &width, &height, &nrChannels, 0);
		check(data);
	}
	else if (imgnum == 1) {

		data = stbi_load("123.jpg", &width, &height, &nrChannels, 0);
		check(data);
	}
	
}

void check(unsigned char *data) {
	if (data)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {



	int z = -3;
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

							 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14;
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(x, y, 0); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex3f(x + (radius * cos(i *  twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)), 0);
	}
	glEnd();
}

void drawBasket(int x, int y, int z)
{


	load(1);
	glBegin(GL_QUADS);


	//botton

	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x + 1, y - 1, z - 1);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x - 3, y - 1, z - 1);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x - 3, y - 1, z + 1);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x + 1, y - 1, z + 1);
	glEnd();

	load(1);
	glBegin(GL_QUADS);
	//right
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x + 1, y + 1, z - 1);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x + 1, y - 1, z - 1);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x + 1, y - 1, z + 1);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x + 1, y + 1, z + 1);
	glEnd();

	load(1);
	glBegin(GL_QUADS);
	//left
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x - 3, y + 1, z - 1);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x - 3, y - 1, z - 1);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x - 3, y - 1, z + 1);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x - 3, y + 1, z + 1);
	glEnd();

	load(1);
	glBegin(GL_QUADS);
	//back
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x + 1, y + 1, z - 1);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x - 3, y + 1, z - 1);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x - 3, y - 1, z - 1);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x + 1, y - 1, z - 1);
	glEnd();

	load(1);
	glBegin(GL_QUADS);
	//front
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x + 1, y + 1, z + 1);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x - 3, y + 1, z + 1);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x - 3, y - 1, z + 1);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x + 1, y - 1, z + 1);
	glEnd();
}

void print(float x,float y, char* string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
};

