#include "Player2D.h"

// Player ship
Player2D::Player2D(Visual2D* visualContext){

	// Originally, mouth is closed
	mouthIsOpen = false;
	// I have 3 lives
	livesLeft = 3;
	// My score is zero
	score = 0;
	// My ship is not rotated
	shipRotation = 0;

	// Creating the objects
	mouthClosed1 = new Line2D(Point2D(0,0),Point2D(3.5,6.25),Color(0,0,0));
	mouthClosed2 = new Line2D(Point2D(3.5,6.25),Point2D(-6,10.5),Color(0,0,0));
	mouthClosed3 = new Line2D(Point2D(-6,10.5),Point2D(5,14),Color(0,0,0));
	mouthClosed4 = new Line2D(Point2D(5,14),Point2D(-6,19),Color(0,0,0));
	mouthClosed5 = new Line2D(Point2D(-6,19),Point2D(5,24.5),Color(0,0,0));

	head = new Circle2D(Point2D(0,0),25,Color(1,0.937,0),true);

	// Adding the objects to the visual context
	DrawingWindow::addObject2D_to_Visual2D(mouthClosed1, visualContext);
	DrawingWindow::addObject2D_to_Visual2D(mouthClosed2, visualContext);
	DrawingWindow::addObject2D_to_Visual2D(mouthClosed3, visualContext);
	DrawingWindow::addObject2D_to_Visual2D(mouthClosed4, visualContext);
	DrawingWindow::addObject2D_to_Visual2D(mouthClosed5, visualContext);
	DrawingWindow::addObject2D_to_Visual2D(head, visualContext);
	
	// Translating the objects to the set position
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(470,30);
	Transform2D::applyTransform(head);

	Transform2D::applyTransform(mouthClosed1);
	Transform2D::applyTransform(mouthClosed2);
	Transform2D::applyTransform(mouthClosed3);
	Transform2D::applyTransform(mouthClosed4);
	Transform2D::applyTransform(mouthClosed5);

	shipCoordinates.x = 470;
	shipCoordinates.y = 30;
}

Player2D::~Player2D(){
}

void Player2D::openWide(Visual2D* visualContext){

	// Must remove head first because otherwise, the mouth will show up underneath
	DrawingWindow::removeObject2D_from_Visual2D(head, visualContext);

	// Creating the mouth
	mouthOpen = new Polygon2D(Color(0,0,0), true);
	mouthOpen->addPoint(Point2D(0,0));
	mouthOpen->addPoint(Point2D(25,25));
	mouthOpen->addPoint(Point2D(-25,25));

	// Adding back the head, but mouth first!
	DrawingWindow::addObject2D_to_Visual2D(mouthOpen, visualContext);
	DrawingWindow::addObject2D_to_Visual2D(head, visualContext);

	// Translate mouth to the current position
	Transform2D::loadIdentityMatrix();
	Transform2D::rotateMatrix(shipRotation);
	Transform2D::translateMatrix(shipCoordinates.x,shipCoordinates.y);
	Transform2D::applyTransform(mouthOpen);

	// Translate the head back where it was
	Transform2D::loadIdentityMatrix();
	Transform2D::rotateMatrix(shipRotation);
	Transform2D::translateMatrix(shipCoordinates.x,shipCoordinates.y);
	Transform2D::applyTransform(head);

	mouthIsOpen = true;
}

void Player2D::shutIt(Visual2D* visualContext){
	// Removing the mouth from the visual context
	DrawingWindow::removeObject2D_from_Visual2D(mouthOpen, visualContext);
	mouthIsOpen = false;
}

void Player2D::shipRespawn() {
	// I'll respawn the ship to a set location (corner bottom right)
	// For this, I make a simple translation
	shipRotation = 0;
	Transform2D::loadIdentityMatrix();
	Transform2D::translateMatrix(470,30);
	Transform2D::applyTransform(head);
	Transform2D::applyTransform(mouthClosed1);
	Transform2D::applyTransform(mouthClosed2);
	Transform2D::applyTransform(mouthClosed3);
	Transform2D::applyTransform(mouthClosed4);
	Transform2D::applyTransform(mouthClosed5);

	shipCoordinates.x = 470;
	shipCoordinates.y = 30;
}

bool Player2D::manageLives(Visual2D* visualContext) {
	// If I lose a life, I'll remove the circle representing it
	if (livesLeft == 2) {
		DrawingWindow::removeObject2D_from_Visual2D(lifeThree, visualContext);
	}
	if (livesLeft == 1) {
		DrawingWindow::removeObject2D_from_Visual2D(lifeTwo, visualContext);
	}
	if (livesLeft == 0) {
		// If I don't have any more lives, it's game over
		DrawingWindow::removeObject2D_from_Visual2D(lifeThree, visualContext);
		gameStatus = new Text("Game over!",Point2D(300,25),Color(1,1,1),BITMAP_TIMES_ROMAN_24);
		DrawingWindow::addText_to_Visual2D(gameStatus,visualContext);
		return true;
	}

	return false;
}

void Player2D::showScore(Visual2D* visualContext) {
	// Considering the score, I harcoded the text :D
	if (score == 7) {
		scoreTotal->text = "Score: 7";
	}
	if (score == 17) {
		scoreTotal->text = "Score: 17";
	}
	if (score == 23) {
		scoreTotal->text = "Score: 23";
	}
	if (score == 24) {
		scoreTotal->text = "Score: 24";
	}
	if (score == 30) {
		scoreTotal->text = "Score: 30";
	}
	if (score == 40) {
		scoreTotal->text = "Score: 40";
	}
	if (score == 47) {
		scoreTotal->text = "Score: 47";
	}
}

void Player2D::moveObjectUp(Object2D* object, int step){
	// I rotate the object because I want it to move and still mantain its rotation
	Transform2D::loadIdentityMatrix();
	Transform2D::rotateMatrix(shipRotation);
	Transform2D::translateMatrix(shipCoordinates.x,shipCoordinates.y);
	Transform2D::translateMatrix(-sin(shipRotation*PI/180)*step,cos(shipRotation*PI/180)*step);
	Transform2D::applyTransform(object);
}

void Player2D::moveObjectDown(Object2D* object, int step){
	// Same thing like moveObjectUp
	Transform2D::loadIdentityMatrix();
	Transform2D::rotateMatrix(shipRotation);
	Transform2D::translateMatrix(shipCoordinates.x,shipCoordinates.y);
	Transform2D::translateMatrix(sin(shipRotation*PI/180)*step,-cos(shipRotation*PI/180)*step);
	Transform2D::applyTransform(object);
}

void Player2D::rotateObject(Object2D* object){
	// Classic rotation
	// Because the object is created in (0,0), I don't have to translate back to origin
	Transform2D::loadIdentityMatrix();
	Transform2D::rotateMatrix(shipRotation);
	Transform2D::translateMatrix(shipCoordinates.x,shipCoordinates.y);
	Transform2D::applyTransform(object);
}

void Player2D::restrictBoundaries(){
	// If the ship wants to go out of the screen, I just put it back
	if (shipCoordinates.x >= 473)
		shipCoordinates.x = 473;

	if (shipCoordinates.x <= 27)
		shipCoordinates.x = 27;

	if (shipCoordinates.y >= 473)
		shipCoordinates.y = 473;

	if (shipCoordinates.y <= 27)
		shipCoordinates.y = 27;
}

void Player2D::moveUp(int step){
	// Using moveObjectUp, I move every object in the desired way
	moveObjectUp(head, step);
	moveObjectUp(mouthClosed1, step);
	moveObjectUp(mouthClosed2, step);
	moveObjectUp(mouthClosed3, step);
	moveObjectUp(mouthClosed4, step);
	moveObjectUp(mouthClosed5, step);

	// If mouth is open, I have to move that object too, otherwise no
	if (mouthIsOpen)
		moveObjectUp(mouthOpen, step);

	// Update object position (I only care about the center of my circle)
	shipCoordinates.x -= sin(shipRotation*PI/180)*step;
	shipCoordinates.y += cos(shipRotation*PI/180)*step;

	restrictBoundaries();
}

void Player2D::moveDown(int step){
	// Same thing like moveUp
	moveObjectDown(head, step);
	moveObjectDown(mouthClosed1, step);
	moveObjectDown(mouthClosed2, step);
	moveObjectDown(mouthClosed3, step);
	moveObjectDown(mouthClosed4, step);
	moveObjectDown(mouthClosed5, step);

	if (mouthIsOpen)
		moveObjectDown(mouthOpen, step); // Feature!

	// Update object position
	shipCoordinates.x += sin(shipRotation*PI/180)*step;
	shipCoordinates.y -= cos(shipRotation*PI/180)*step;

	restrictBoundaries();
}

void Player2D::rotate(){
	// Same thing, but with rotate
	rotateObject(head);
	rotateObject(mouthClosed1);
	rotateObject(mouthClosed2);
	rotateObject(mouthClosed3);
	rotateObject(mouthClosed4);
	rotateObject(mouthClosed5);

	if (mouthIsOpen)
		rotateObject(mouthOpen);
}

