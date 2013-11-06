#pragma once
#include "Visual2D.h"
#include "Object2D.h"
#include "Transform2D.h"
#include "Circle2D.h"
#include "Rectangle2d.h"
#include "Line2D.h"
#include "Polygon2D.h"
#include "DrawingWindow.h"

#define PI 3.14159265358979323846

class Player2D {

public:
	Circle2D *head; // Ship body
	Point2D shipCoordinates; // Ship coordinates

	Line2D *mouthClosed1,*mouthClosed2,*mouthClosed3,*mouthClosed4,*mouthClosed5; // Closed mouth

	Polygon2D *mouthOpen; // Open mouth <- a triangle
	bool mouthIsOpen;
	float shipRotation;

	// Lives and scoreboard
	int livesLeft;
	int score;
	Circle2D *lifeOne, *lifeTwo, *lifeThree;
	Text *scoreTotal;
	Text *gameStatus;

	Player2D();
	Player2D(Visual2D* visualContext);
	~Player2D();

	void moveUp(int step);
	void moveDown(int step);
	void rotate();
	void openWide(Visual2D* visualContext);
	void shutIt(Visual2D* visualContext);
	void shipRespawn();
	bool manageLives(Visual2D* visualContext);
	void showScore(Visual2D* visualContext);

private:
	void restrictBoundaries();
	void moveObjectUp(Object2D* object, int step);
	void moveObjectDown(Object2D* object, int step);
	void rotateObject(Object2D* object);

};

