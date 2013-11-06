#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Framework/Player2D.h"
#include "Framework/Enemy.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#define PI 3.14159265358979323846
using namespace std;

Visual2D *v2d1, *v2d2;
Rectangle2D *boudaryBox;
Player2D *ship;
Enemy *firstEnemy, *secondEnemy, *thirdEnemy;
vector<bool> enemyType;
bool enemyDead;
bool gameStatus;

float enemyStep;
float angle;


void DrawingWindow::init()
{
	enemyType.push_back(false); // Initially, I don't have any enemy
	enemyType.push_back(false);
	enemyType.push_back(false);
	enemyDead = false;
	gameStatus = false;

	// Viewport border
	boudaryBox = new Rectangle2D(Point2D(0,0),width,height,Color(1,1,1),false); // Color warning here

	// Scoreboard
	v2d1 = new Visual2D(5,5,DrawingWindow::width-13,50,5,5,DrawingWindow::width-13,50);  
	addVisual2D(v2d1);

	// Game area
	v2d2 = new Visual2D((float)0,(float)0,(float)DrawingWindow::width,(float)DrawingWindow::height,5,55,DrawingWindow::width-13,DrawingWindow::height-5);  
	addVisual2D(v2d2);
	addObject2D_to_Visual2D(boudaryBox, v2d2);

	// Player ship
	ship = new Player2D(v2d2);
	ship->scoreTotal = new Text("Score:",Point2D(150,25),Color(1,1,1),BITMAP_TIMES_ROMAN_24);
	DrawingWindow::addText_to_Visual2D(ship->scoreTotal,v2d1);
	
	// Initial score and lives
	ship->lifeOne = new Circle2D(Point2D(460,25),5,Color(1,0.937,0),true);
	ship->lifeTwo = new Circle2D(Point2D(450,25),5,Color(1,0.937,0),true);
	ship->lifeThree = new Circle2D(Point2D(440,25),5,Color(1,0.937,0),true);

	DrawingWindow::addObject2D_to_Visual2D(ship->lifeOne, v2d1);
	DrawingWindow::addObject2D_to_Visual2D(ship->lifeTwo, v2d1);
	DrawingWindow::addObject2D_to_Visual2D(ship->lifeThree, v2d1);

	// Enemy1
	firstEnemy = new Enemy(v2d2,0); // Enemy type 0
	enemyType[0] = true;

	// Initial coordinates for enemy
	firstEnemy->enemyCoordinates.x = 200;
	firstEnemy->enemyCoordinates.y = 450;

	// Translate enemy to random initial position
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(firstEnemy->enemyCoordinates.x,firstEnemy->enemyCoordinates.y);
	Transform2D::applyTransform(firstEnemy->enemyZeroPartOne);
	Transform2D::applyTransform(firstEnemy->enemyZeroPartTwo);
			
	
	// Enemy2
	secondEnemy = new Enemy(v2d2,1); // Enemy type 1
	enemyType[1] = true;

	secondEnemy->enemyCoordinates.x = 450;
	secondEnemy->enemyCoordinates.y = 450;

	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(secondEnemy->enemyCoordinates.x,secondEnemy->enemyCoordinates.y);
	Transform2D::applyTransform(secondEnemy->enemyOnePartOne);
	Transform2D::applyTransform(secondEnemy->enemyOnePartTwo);

	// Enemy3
	thirdEnemy = new Enemy(v2d2,2); // Enemy type 2
	enemyType[2] = true;

	thirdEnemy->enemyCoordinates.x = 10;
	thirdEnemy->enemyCoordinates.y = 450;

	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(thirdEnemy->enemyCoordinates.x,thirdEnemy->enemyCoordinates.y);
	Transform2D::applyTransform(thirdEnemy->enemyTwoPartOne);
	Transform2D::applyTransform(thirdEnemy->enemyTwoPartTwo);

}

// Animation
void DrawingWindow::onIdle()
{
	// gameStatus = true means the game is over and I shouldn't do anything in onIdle()
	if (gameStatus == false) {

		// Check if ship is dead
		gameStatus = ship->manageLives(v2d1); 

		// Check if I have enemies
		if (enemyType[0] == false && enemyType[1] == false && enemyType[2] == false){ 
			gameStatus = true; // If gameStatus = true, I won
			ship->gameStatus = new Text("You won!",Point2D(300,25),Color(1,1,1),BITMAP_TIMES_ROMAN_24);
			DrawingWindow::addText_to_Visual2D(ship->gameStatus,v2d1);
		}

		// If I have enemy1, he has to move after the player
		if (enemyType[0] == true) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(firstEnemy->enemyCoordinates.x,firstEnemy->enemyCoordinates.y);
			firstEnemy->followShip(ship,0.005,0);
			enemyDead = firstEnemy->collision(v2d2,ship,0,v2d1);

			if (enemyDead == true)
				enemyType[0] = false;
		}

		// Same
		if (enemyType[1] == true) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(secondEnemy->enemyCoordinates.x,secondEnemy->enemyCoordinates.y);
			secondEnemy->followShip(ship,0.009,1);
			enemyDead = secondEnemy->collision(v2d2,ship,1,v2d1);

			if (enemyDead == true)
				enemyType[1] = false;
		}

		// Same
		if (enemyType[2] == true) {
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(thirdEnemy->enemyCoordinates.x,thirdEnemy->enemyCoordinates.y);
			thirdEnemy->followShip(ship,0.017,2);
			enemyDead = thirdEnemy->collision(v2d2,ship,2,v2d1);

			if (enemyDead == true)
				enemyType[2] = false;
		}
	}
}

void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(5,5,width-13,50);
	v2d2->poarta(5,55,width-13,height-5);

}

// On key operations
void DrawingWindow::keyOperations()
{
	// This is the movement of the player/ship/Pacman :D
	static float step = 0;
	bool limit = false;

	// Open/close mouth (drill)
	if (DrawingWindow::keyStates[32]){
		if (ship->mouthIsOpen){ // Kinda obvious
			ship->shutIt(v2d2);
			ship->mouthIsOpen = false;
		}
		else {
			ship->openWide(v2d2);
			ship->mouthIsOpen = true;
		}
	}

	// Actual movement	
	if (DrawingWindow::keyStates[119]){ // Up
		ship->moveUp(step);
	}

	if (DrawingWindow::keyStates[115]){ // Down
		ship->moveDown(step);
	}

	if (DrawingWindow::keyStates[97]){ // Left
		if (ship->mouthIsOpen)
			ship->shipRotation = (float)(ship->shipRotation + 2.5);
		else
			ship->shipRotation = (float)(ship->shipRotation + 3);

		ship->rotate();
	}

	if (DrawingWindow::keyStates[100]){ // Right
		if (ship->mouthIsOpen)
			ship->shipRotation = (float)(ship->shipRotation - 2.5);
		else
			ship->shipRotation = (float)(ship->shipRotation - 3);

		ship->rotate();
	}
	
	// Exit
	if (DrawingWindow::keyStates[27]){
		exit(0);
	}

	// Speed limitation
	if (step > 3)
		limit = true;

	if (step <= 0)
		limit = false;

	if (limit){
		// If my mouth is open, I'm slowed...damn logic!
		if (ship->mouthIsOpen)
			step = (float)(step - 0.05);
		else
			step = (float)(step - 0.5);
	}

	if (!limit){
		if (ship->mouthIsOpen)
			step = (float)(step + 0.05);
		else
			step = (float)(step + 0.5);
	}

}

void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)

{
	DrawingWindow dw(argc, argv, 500, 500, 200, 100, "Pacman meets Geometry");
	dw.init();
	dw.run();
	return 0;

}