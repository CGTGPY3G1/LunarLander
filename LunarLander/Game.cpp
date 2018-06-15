#include<gl/glut.h>
#include "Game.h"
#include "Random.h"
#include "Meteor.h"
#include "Lander.h"
#include "Ground.h"
#include "BackgroundPlanet.h"
#include "Image.h"
#include "Transform.h"
#include "CollisionManager.h"
#include <sstream>
#include <string>
#include <iomanip>

const unsigned int NO_OF_KEYS = 256;
bool keyStates[NO_OF_KEYS];
bool oldKeyStates[NO_OF_KEYS];

Game::Game(const float & worldWidth, const float & worldHeight) {
	this->width = worldWidth; this->height = worldHeight;
}

Game::~Game() {
	CleanUp();
}

void Game::Display() {
	// Draw all GameObjects, starting with background objects in the order the were added to the array
	for(std::vector<GameObject*>::iterator i = backgroundObjects.begin(); i != backgroundObjects.end(); ++i) {
		(*i)->Draw();
	}
	if(ground) // then if the ground has been created draw it
		ground->Draw();
	if(lander) // then if the lander has been created draw it
		lander->Draw();
	// disable GL_BLEND & GL_TEXTURE_2D to prevent them affecting the overlayed shapes and text
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	// print the GUI
	PrintHUD();
	// swaps old key buffer array with the new 1
	UpdateKeys();
}

void Game::Update(const float & deltaTime) {
	// if at least 1 attempt has been made
	if(tryCount > 0) {
		// count down time to spawn a meteor
		meteorTimer -= deltaTime;
		// and create 1 if the time reaches 0
		if(meteorTimer <= 0) CreateMeteor();
	}
	// for all background objects
	for(std::vector<GameObject*>::iterator i = backgroundObjects.begin(); i != backgroundObjects.end(); i++) {
		// Uodate the object by the frame time
		(*i)->Update(deltaTime);
		if((*i)->GetAlive()) { // if the object is still alive
			bool isStopped = (*i)->GetStopped();
			if(lander && !lander->GetStopped()) { //if the lander exists and has not stopped
				if(CollisionManager::CheckCollision((*i), lander) || CollisionManager::CheckCollision((*i), lander->GetChild(0))) {
					// if the object collides with the lander
					// end the attempt as a failure
					EndAttempt(false);
					if(!isStopped) // if the object isn't already stopped
						(*i)->Kill(1); // kill it
				}
			}
			if(!isStopped && ground && CollisionManager::CheckCollision(ground, (*i))) {
				// if the object isn't already stopped
				(*i)->Kill(1); // kill it
			}
		}
	}
	if(lander) { // if the lander exists
				 // Uodate the lander by the frame time
		lander->Update(deltaTime);
		if(GetKey(GLUT_KEY_RIGHT)) {
			// move lander right
			lander->Move(Vector2(1.0f, 0.0f));
		}
		if(GetKey(GLUT_KEY_LEFT)) {
			// move lander left
			lander->Move(Vector2(-1.0f, 0.0f));
		}
		if(GetKey(GLUT_KEY_UP)) {
			// move lander up
			lander->Move(Vector2(0.0f, 1.0f));
		}
	}
	if(!gameOver) { // if game not over
					// check for collisions between the ground and any part of the lander and the landing pad "ground->GetChild(0)" and the landers body
		if(CollisionManager::CheckCollision(ground, lander) || CollisionManager::CheckCollision(ground, lander->GetChild(0)) || CollisionManager::CheckCollision(ground->GetChild(0), lander)) {
			EndAttempt(false); // end the attempt as a failure
		}
		// check for collisions between the landing pad and the landers legs
		else if(CollisionManager::CheckCollision(ground->GetChild(0), lander->GetChild(0))) {
			float v = lander->GetVelocity().Magnitude(); // get the speed of the lander
														 // get the distance between the lander and the landing pad on the x axis
			float distX = abs(lander->GetChild(0)->GetTransform()->GetPosition().GetX() - ground->GetChild(0)->GetTransform()->GetPosition().GetX());
			//get half the width of the lander
			float landerWidth = lander->GetRenderable("Lander")->GetWidth() / 2;
			//get half the width of the landing pad
			float PadWidth = ground->GetChild(0)->GetRenderable("LandingPad")->GetWidth() / 2;
			// true if the landers speed is less than 10 and the 
			// lander has not overshot the landing pad, else false
			bool landed = (v < 10 && distX <= PadWidth - landerWidth);
			EndAttempt(landed);
		}
		// increase the attempts play time
		playTime += deltaTime;
	}
	else { // if game over
		if(GetKey(GLUT_KEY_DOWN)) {
			SetUp(); // set up a new attempt
		}
	}
}

void Game::SpecialKeyUp(int key, int x, int y) {
	keyStates[key] = false;
}

void Game::SpecialKeyDown(int key, int x, int y) {
	keyStates[key] = true;
}

// prints a string at the position specified by x and y, at a scale defined by scaleX and scaleY, with the specified r,g,b 
// values for colour.  the aliignement is either 1- centre aligned, 2 - right alighted and left aligned with any other number
void Game::PrintString(float x, float y, float scaleX, float scaleY, std::string toPrint, float r, float g, float b, int alignment) {
	float offset = 0; // used to offset the x position
	if(alignment == 1 || alignment == 2) { // if not left aligned
										   // get the total width of the string
		for(int i = 0; i < (int)toPrint.length(); i++) {
			float charWidth = (float)glutStrokeWidth(GLUT_STROKE_ROMAN, toPrint[i]);
			offset -= charWidth * scaleX;
		}
		if(alignment == 1) // if centre aligned
			offset *= 0.5f; // half the offset 
	}
	glColor3f(r, g, b);
	glPushMatrix();
	// se the drawing position
	glTranslatef(x + offset, y, 0);
	// set the scale of the text
	glScalef(scaleX, scaleY, 1.0f);
	// print the string 1 character at a time
	for(size_t i = 0; i < toPrint.length(); i++) {
		char a = toPrint[i]; // get the current character
		glutStrokeCharacter(GLUT_STROKE_ROMAN, a);// print it
		// move drawing position on the x axis by either the width of the character at the specified scale
		// or the width of the character at 10% of the specified scale if the character is a space
		glTranslatef(((GLfloat)glutStrokeWidth(GLUT_STROKE_ROMAN, a)) * (a == ' ') ? scaleX * 0.1f : scaleX, 0, 0);
	}
	glPopMatrix();
}


std::string Game::TimeAsString(int precision) {
	std::stringstream toPrint;
	toPrint << std::fixed;
	toPrint << std::setprecision(2);
	toPrint << playTime;
	return toPrint.str();
}

void Game::PrintHUD() {
	if(gameOver) {
		// draw a rectangle, in the centre of the screen
		Vector2 position = Vector2(width / 2, height / 2), dimensions = Vector2(width / 2, height / 3);
		DrawRect(position, dimensions, 0.8f, 0.8f, 0.8f);
		// set text scale and colour values
		float textScaleX = 0.25f, textScaleY = 0.25f;
		float r = 1.0f, g = 0.0f, b = 0.0f;
		// offset positions Y to centre text 
		position.SetY(position.GetY() - 10);
		if(tryCount > 0) { // if at least 1 attempt has been made
			if(success) // if lander landed
				PrintString(position.GetX(), position.GetY() + dimensions.GetY() / 3.0f, textScaleX, textScaleY, "You Landed In", r, g, b, 1);
			else // if the lander crahed
				PrintString(position.GetX(), position.GetY() + dimensions.GetY() / 3.0f, textScaleX, textScaleY, "You Crashed In", r, g, b, 1);
			// print the attemp time
			PrintString(position.GetX(), position.GetY() + dimensions.GetY() / 9.0f, textScaleX, textScaleY, TimeAsString(2) + " Seconds", r, g, b, 1);
			// print restart button info
			PrintString(position.GetX(), position.GetY() - dimensions.GetY() / 9.0f, textScaleX, textScaleY, "Press Down", r, g, b, 1);
			PrintString(position.GetX(), position.GetY() - dimensions.GetY() / 3.0f, textScaleX, textScaleY, "To Play Again", r, g, b, 1);
		}
		else {
			// print start button info
			PrintString(position.GetX(), position.GetY() + dimensions.GetY() / 3.5f, textScaleX, textScaleY, "Press Down", r, g, b, 1);
			PrintString(position.GetX(), position.GetY(), textScaleX, textScaleY, "To", r, g, b, 1);
			PrintString(position.GetX(), position.GetY() - dimensions.GetY() / 4.0f, textScaleX, textScaleY, "Begin", r, g, b, 1);
		}
	}
	// draw the menu with the play time at the start 
	DrawRect(Vector2(width / 2, height - 30), Vector2(width, 60), 0.0f, 0.0f, 0.0f);
	PrintString(15, 560, 0.2f, 0.2f, "Time: " + TimeAsString(2), 1.0f, 1.0f, 1.0f, 0);
	// If the lander exists, print it's fuel value else print 0
	std::string trys = "Fuel: " + std::to_string(lander ? (int) static_cast<Lander*>(lander)->GetFuel() : 0);
	PrintString(width / 2 - width / 5, 560, 0.2f, 0.2f, trys, 1.0f, 1.0f, 1.0f, 0);
	// print the number of crashes and landings
	std::string crashes = ("Crashed: " + std::to_string(crashCount));
	PrintString(width - 25, 560, 0.2f, 0.2f, crashes, 1.0f, 1.0f, 1.0f, 2);
	std::string landings = ("Landed: " + std::to_string(landCount));
	PrintString(width / 2 + (width / 20), 560, 0.2f, 0.2f, landings, 1.0f, 1.0f, 1.0f, 0);
}

void Game::SetUp() {
	CleanUp();
	// position a new lander near the top centre of the screen
	lander = new Lander(Vector2(width / 2, height*0.8f), Vector2(1, 0));
	lander->SetName("Lander");
	// position the ground at the bottom centre of the screen passing world width/height along with number of ground segments
	ground = new Ground(Vector2(width / 2, 0.0f), Vector2(1.0f, 0.0f), width, height, 18);
	ground->SetName("Moon");
	// position the space background in the centre of the screen
	GameObject * space = new GameObject(Vector2(width / 2, height / 2), Vector2(1, 0));
	space->SetName("Space");
	// pick 1 of 4 images to assign to the space object
	int imageNo = Random::RandomInt(1, 5);
	std::stringstream imageName;
	imageName << "space" << imageNo << ".png";
	// add the chosen image to the object as a renderable
	space->AddRenderable(new Image(imageName.str().c_str(), width, height));
	// add space to the backgroundObjects array
	backgroundObjects.push_back(space);
	// add a new planet to the backgroundObjects array, positioned off screen and set to orbit the ground by the screen width on the x axis and the height *0.8 on the y
	backgroundObjects.push_back(new BackgroundPlanet(Vector2(2000, 50), Vector2(1.0f, 0.0f), ground->GetTransform()->GetPosition()));
	// sets a random length of time before the next meteor spawns
	meteorTimer = Random::RandomFloat(0.1f, 3.0f);
	// reset play time, and game over 
	playTime = 0; gameOver = false;
	tryCount++;
}

void Game::CreateMeteor() {
	// get a position from the center 3 5ths of the screen on the x axis and just above the screen height on the y
	Vector2 position = Vector2(Random::RandomFloat(width * 0.2f, width * 0.8f), height * 1.1f);
	// create a new meteor in the position above, oriented towards the right of the screen with a  
	// velocity betweem + or - width/6 in the x axis and a maximum speed of height *0.4 on the y
	GameObject * meteor = new Meteor(position, Vector2(1.0f, 0.0f), Vector2(Random::RandomFloat(-width / 6, width / 6), -Random::RandomFloat(height * 0.08f, height * 0.4f)));
	meteor->SetName("Meteor");
	// add the meteor to the backgroundObjects array
	backgroundObjects.push_back(meteor);
	// sets a random length of time before the next meteor spawns
	meteorTimer = Random::RandomFloat(0.1f, 3.0f);
}

// free the memory allocated to the objects
void Game::CleanUp() {
	if(lander)
		delete lander;
	if(ground)
		delete ground;
	if(backgroundObjects.size() > 0) {
		for(std::vector<GameObject*>::iterator i = backgroundObjects.begin(); i != backgroundObjects.end(); i++) {
			delete * i;
		}
		backgroundObjects.clear();
	}
}

// called when the lander crashes or lands
void Game::EndAttempt(const bool & landed) {
	gameOver = true;
	success = landed;
	if(success) { // deactivate the lander 
		lander->SetStopped(true);
		landCount++;
	}
	else { // destroy the lander
		lander->Kill(1);
		crashCount++;
	}
}

// draw a box in the specified position, with the specified dimensions and colour
// position is centred and colour supplied via r, g, and b parameters
void Game::DrawRect(Vector2 position, Vector2 dimensions, float r, float g, float b) {
	glColor3f(r, g, b);
	// get the half width and half height to position the vertices
	float halfWidth = dimensions.GetX() / 2, halfHeight = dimensions.GetY() / 2;
	float x = position.GetX(), y = position.GetY();
	// draw a rectangle with the specified parameters
	glBegin(GL_POLYGON);
	glVertex2f(x - halfWidth, y - halfHeight);
	glVertex2f(x + halfWidth, y - halfHeight);
	glVertex2f(x + halfWidth, y + halfHeight);
	glVertex2f(x - halfWidth, y + halfHeight);
	glEnd();
}

bool Game::GetKey(unsigned int key) {
	return key < NO_OF_KEYS ? keyStates[key] : false;
}

void Game::UpdateKeys() {
	for(size_t i = 0; i < NO_OF_KEYS; i++) 
		oldKeyStates[i] = keyStates[i];
}
