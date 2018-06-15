#include<gl/glut.h>
#include "Game.h"

using namespace std;
// the window width and height
const float WIDTH = 800.0f, HEIGHT = 600.0f;
Game game;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	game.Display();
	glutSwapBuffers();
}

// number of miliseconds since glutInit was called
int oldTime = 0;
void Update(int a) {
	// get number of miliseconds since glutInit was called
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	// get the frame time in seconds
	float deltaTime = (newTime - oldTime) / 1000.0f;
	oldTime = newTime;

	game.Update(deltaTime);

	glutTimerFunc(a, Update, a);
}

void Idle(void) { 
	glutPostRedisplay();
}

void Reshape(int w, int h) { 
	// resize the viewport with the window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void main(int argA, char** argB) {
	glutInit(&argA, argB);
	// set the window mode to RGB and double buffered
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize((int)WIDTH, (int)HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lunar Lander");
	// enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// enable 2d textures
	glEnable(GL_TEXTURE_2D);
	glClearColor(0, 0, 0, 1);// set the clear colour to black
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	game = Game(WIDTH, HEIGHT);
	// register callbacks 
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Game::SpecialKeyDown);
	glutSpecialUpFunc(Game::SpecialKeyUp);
	glutTimerFunc(20, Update, 20);
	glutIdleFunc(Idle);
	glutMainLoop();
}