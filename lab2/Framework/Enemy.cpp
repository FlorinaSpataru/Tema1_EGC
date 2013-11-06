#include "Enemy.h"


Enemy::Enemy(Visual2D* visualContext,int type) {
	// Considering the type, I create a different enemy
	if (type == 0) {
		// 2 rectangles
		enemyZeroPartOne = new Rectangle2D(Point2D(0,0),14,14,Color(1,1,1),false);
		enemyZeroPartTwo = new Rectangle2D(Point2D(9,9),14,14,Color(1,1,1),false);
		DrawingWindow::addObject2D_to_Visual2D(enemyZeroPartOne,visualContext);
		DrawingWindow::addObject2D_to_Visual2D(enemyZeroPartTwo,visualContext);
	}
	if (type == 1) {
		// original ship
		enemyOnePartOne = new Circle2D(Point2D(0,0),10,Color(1,1,1),false);
		enemyOnePartTwo = new Polygon2D(Color(1,1,1),false);
		enemyOnePartTwo->addPoint(Point2D(6,2.5));
		enemyOnePartTwo->addPoint(Point2D(0,7.5));
		enemyOnePartTwo->addPoint(Point2D(-7,0));
		enemyOnePartTwo->addPoint(Point2D(0,-7.5));
		enemyOnePartTwo->addPoint(Point2D(6,-2.5));
		enemyOnePartTwo->addPoint(Point2D(1,-4));
		enemyOnePartTwo->addPoint(Point2D(-2.5,0));
		enemyOnePartTwo->addPoint(Point2D(1,4));
		DrawingWindow::addObject2D_to_Visual2D(enemyOnePartOne,visualContext);
		DrawingWindow::addObject2D_to_Visual2D(enemyOnePartTwo,visualContext);

	}
	if (type == 2) {
		// rectangle with circle in the middle
		enemyTwoPartOne = new Rectangle2D(Point2D(0,0),16,16,Color(1,1,1),false);
		enemyTwoPartTwo = new Circle2D(Point2D(8,8),3,Color(1,1,1),false);
		DrawingWindow::addObject2D_to_Visual2D(enemyTwoPartOne,visualContext);
		DrawingWindow::addObject2D_to_Visual2D(enemyTwoPartTwo,visualContext);
	}
	
}

Enemy::~Enemy(void) {
}

void Enemy::restrictBoundaries(){
	// Same thing as restrict boudaries for ship
	// Don't think the enemy can go to those coords, but just to be safe
	if (enemyCoordinates.x >= 473)
		enemyCoordinates.x = 473;

	if (enemyCoordinates.x <= 27)
		enemyCoordinates.x = 27;

	if (enemyCoordinates.y >= 473)
		enemyCoordinates.y = 473;

	if (enemyCoordinates.y <= 27)
		enemyCoordinates.y = 27;
}

void Enemy::followShip(Player2D *ship,float enemyStep,int type){

	if (type == 0) {
		// I have to transform to int because it would be impossible to make
		// == between float numbers
		if ((int)enemyCoordinates.x == (int)ship->shipCoordinates.x){
			if (enemyCoordinates.y < ship->shipCoordinates.y){
				// I translate the enemy towards the player
				// For this, I check x and y of player
				Transform2D::translateMatrix(0,enemyStep);
				Transform2D::applyTransform(enemyZeroPartOne);
				Transform2D::applyTransform(enemyZeroPartTwo);
			 
				enemyCoordinates.y += enemyStep;
				restrictBoundaries();
			}
			else {
				Transform2D::translateMatrix(0,-enemyStep);
				Transform2D::applyTransform(enemyZeroPartOne);
				Transform2D::applyTransform(enemyZeroPartTwo);
				enemyCoordinates.y -= enemyStep;
				restrictBoundaries();
			}
		}
		else if ((int)enemyCoordinates.y == (int)ship->shipCoordinates.y){
			if (enemyCoordinates.x < ship->shipCoordinates.x){
				Transform2D::translateMatrix(enemyStep,0);
				Transform2D::applyTransform(enemyZeroPartOne);
				Transform2D::applyTransform(enemyZeroPartTwo);
			
				enemyCoordinates.x += enemyStep;
				restrictBoundaries();
			}
			else {
				Transform2D::translateMatrix(-enemyStep,0);
				Transform2D::applyTransform(enemyZeroPartOne);
				Transform2D::applyTransform(enemyZeroPartTwo);
				enemyCoordinates.x -= enemyStep;
				restrictBoundaries();
			}
		}
		else {
			if (enemyCoordinates.x < ship->shipCoordinates.x){
				if (enemyCoordinates.y < ship->shipCoordinates.y){
					Transform2D::translateMatrix(enemyStep,enemyStep);
					Transform2D::applyTransform(enemyZeroPartOne);
					Transform2D::applyTransform(enemyZeroPartTwo);
			
					enemyCoordinates.x += enemyStep;
					enemyCoordinates.y += enemyStep;
					restrictBoundaries();
				}
				else {
					Transform2D::translateMatrix(enemyStep,-enemyStep);
					Transform2D::applyTransform(enemyZeroPartOne);
					Transform2D::applyTransform(enemyZeroPartTwo);
			
					enemyCoordinates.x += enemyStep;
					enemyCoordinates.y -= enemyStep;
					restrictBoundaries();
				}
			}
			else {
				if (enemyCoordinates.y < ship->shipCoordinates.y){
					Transform2D::translateMatrix(-enemyStep,enemyStep);
					Transform2D::applyTransform(enemyZeroPartOne);
					Transform2D::applyTransform(enemyZeroPartTwo);
			
					enemyCoordinates.x -= enemyStep;
					enemyCoordinates.y += enemyStep;
					restrictBoundaries();
				}
				else {
					Transform2D::translateMatrix(-enemyStep,-enemyStep);
					Transform2D::applyTransform(enemyZeroPartOne);
					Transform2D::applyTransform(enemyZeroPartTwo);
			
					enemyCoordinates.x -= enemyStep;
					enemyCoordinates.y -= enemyStep;
					restrictBoundaries();
				}
			}
		}
	}

	if (type == 1) {
		if ((int)enemyCoordinates.x == (int)ship->shipCoordinates.x){
			if (enemyCoordinates.y < ship->shipCoordinates.y){
				Transform2D::translateMatrix(0,enemyStep);
				Transform2D::applyTransform(enemyOnePartOne);
				Transform2D::applyTransform(enemyOnePartTwo);
			 
				enemyCoordinates.y += enemyStep;
				restrictBoundaries();
			}
			else {
				Transform2D::translateMatrix(0,-enemyStep);
				Transform2D::applyTransform(enemyOnePartOne);
				Transform2D::applyTransform(enemyOnePartTwo);
				enemyCoordinates.y -= enemyStep;
				restrictBoundaries();
			}
		}
		else if ((int)enemyCoordinates.y == (int)ship->shipCoordinates.y){
			if (enemyCoordinates.x < ship->shipCoordinates.x){
				Transform2D::translateMatrix(enemyStep,0);
				Transform2D::applyTransform(enemyOnePartOne);
				Transform2D::applyTransform(enemyOnePartTwo);
			
				enemyCoordinates.x += enemyStep;
				restrictBoundaries();
			}
			else {
				Transform2D::translateMatrix(-enemyStep,0);
				Transform2D::applyTransform(enemyOnePartOne);
				Transform2D::applyTransform(enemyOnePartTwo);
				enemyCoordinates.x -= enemyStep;
				restrictBoundaries();
			}
		}
		else {
			if (enemyCoordinates.x < ship->shipCoordinates.x){
				if (enemyCoordinates.y < ship->shipCoordinates.y){
					Transform2D::translateMatrix(enemyStep,enemyStep);
					Transform2D::applyTransform(enemyOnePartOne);
					Transform2D::applyTransform(enemyOnePartTwo);
			
					enemyCoordinates.x += enemyStep;
					enemyCoordinates.y += enemyStep;
					restrictBoundaries();
				}
				else {
					Transform2D::translateMatrix(enemyStep,-enemyStep);
					Transform2D::applyTransform(enemyOnePartOne);
					Transform2D::applyTransform(enemyOnePartTwo);
			
					enemyCoordinates.x += enemyStep;
					enemyCoordinates.y -= enemyStep;
					restrictBoundaries();
				}
			}
			else {
				if (enemyCoordinates.y < ship->shipCoordinates.y){
					Transform2D::translateMatrix(-enemyStep,enemyStep);
					Transform2D::applyTransform(enemyOnePartOne);
					Transform2D::applyTransform(enemyOnePartTwo);
			
					enemyCoordinates.x -= enemyStep;
					enemyCoordinates.y += enemyStep;
					restrictBoundaries();
				}
				else {
					Transform2D::translateMatrix(-enemyStep,-enemyStep);
					Transform2D::applyTransform(enemyOnePartOne);
					Transform2D::applyTransform(enemyOnePartTwo);
			
					enemyCoordinates.x -= enemyStep;
					enemyCoordinates.y -= enemyStep;
					restrictBoundaries();
				}
			}
		}
	}

	if (type == 2) {
		if ((int)enemyCoordinates.x == (int)ship->shipCoordinates.x){
			if (enemyCoordinates.y < ship->shipCoordinates.y){
				Transform2D::translateMatrix(0,enemyStep);
				Transform2D::applyTransform(enemyTwoPartOne);
				Transform2D::applyTransform(enemyTwoPartTwo);
			 
				enemyCoordinates.y += enemyStep;
				restrictBoundaries();
			}
			else {
				Transform2D::translateMatrix(0,-enemyStep);
				Transform2D::applyTransform(enemyTwoPartOne);
				Transform2D::applyTransform(enemyTwoPartTwo);
				enemyCoordinates.y -= enemyStep;
				restrictBoundaries();
			}
		}
		else if ((int)enemyCoordinates.y == (int)ship->shipCoordinates.y){
			if (enemyCoordinates.x < ship->shipCoordinates.x){
				Transform2D::translateMatrix(enemyStep,0);
				Transform2D::applyTransform(enemyTwoPartOne);
				Transform2D::applyTransform(enemyTwoPartTwo);
			
				enemyCoordinates.x += enemyStep;
				restrictBoundaries();
			}
			else {
				Transform2D::translateMatrix(-enemyStep,0);
				Transform2D::applyTransform(enemyTwoPartOne);
				Transform2D::applyTransform(enemyTwoPartTwo);
				enemyCoordinates.x -= enemyStep;
				restrictBoundaries();
			}
		}
		else {
			if (enemyCoordinates.x < ship->shipCoordinates.x){
				if (enemyCoordinates.y < ship->shipCoordinates.y){
					Transform2D::translateMatrix(enemyStep,enemyStep);
					Transform2D::applyTransform(enemyTwoPartOne);
					Transform2D::applyTransform(enemyTwoPartTwo);
			
					enemyCoordinates.x += enemyStep;
					enemyCoordinates.y += enemyStep;
					restrictBoundaries();
				}
				else {
					Transform2D::translateMatrix(enemyStep,-enemyStep);
					Transform2D::applyTransform(enemyTwoPartOne);
					Transform2D::applyTransform(enemyTwoPartTwo);
			
					enemyCoordinates.x += enemyStep;
					enemyCoordinates.y -= enemyStep;
					restrictBoundaries();
				}
			}
			else {
				if (enemyCoordinates.y < ship->shipCoordinates.y){
					Transform2D::translateMatrix(-enemyStep,enemyStep);
					Transform2D::applyTransform(enemyTwoPartOne);
					Transform2D::applyTransform(enemyTwoPartTwo);
			
					enemyCoordinates.x -= enemyStep;
					enemyCoordinates.y += enemyStep;
					restrictBoundaries();
				}
				else {
					Transform2D::translateMatrix(-enemyStep,-enemyStep);
					Transform2D::applyTransform(enemyTwoPartOne);
					Transform2D::applyTransform(enemyTwoPartTwo);
			
					enemyCoordinates.x -= enemyStep;
					enemyCoordinates.y -= enemyStep;
					restrictBoundaries();
				}
			}
		}
	}

}

bool Enemy::collision(Visual2D* visualContext,Player2D *ship,int type,Visual2D* visualContextScore){
	float distance;

	if (ship->mouthIsOpen == false) { // If mouth is closed -- I'm in trouble!
		// Checking collision for every enemy type - different radiuses
		if (type == 0) {
			// I calculate the distance between the center point of the circle surrounding the enemy
			// and the center point of the ship
			distance = sqrt((ship->shipCoordinates.x - enemyCoordinates.x - 11.5)*(ship->shipCoordinates.x - enemyCoordinates.x - 11.5) +
				(ship->shipCoordinates.y - enemyCoordinates.y - 11.5)*(ship->shipCoordinates.y - enemyCoordinates.y - 11.5));

			// If that distance is smaller than the sum of the 2 radiuses, we have collision
			if (distance <= 39) {		// R1 = 25, R2 = 14 --- we haz collision
				ship->livesLeft -= 1;	// Decrement my lives
				ship->shipRespawn();	// Respawn the ship to a set location
			}
		}

		if (type == 1) {
			distance = sqrt((ship->shipCoordinates.x - enemyCoordinates.x)*(ship->shipCoordinates.x - enemyCoordinates.x) +
				(ship->shipCoordinates.y - enemyCoordinates.y)*(ship->shipCoordinates.y - enemyCoordinates.y));

			if (distance <= 35) {		// R1 = 25, R2 = 10
				ship->livesLeft -= 1;
				ship->shipRespawn();
			}
		}

		if (type == 2) {
			distance = sqrt((ship->shipCoordinates.x - enemyCoordinates.x - 8)*(ship->shipCoordinates.x - enemyCoordinates.x - 8) +
				(ship->shipCoordinates.y - enemyCoordinates.y - 8)*(ship->shipCoordinates.y - enemyCoordinates.y - 8));

			if (distance <= 33.5) {		// R1 = 25, R2 = 8.5
				ship->livesLeft -= 1;
				ship->shipRespawn();
			}
		}
	}

	else { // If mouth is open -- nom nom time!
		// Same thing, different collision for every type
		if (type == 0) {
			// I will consider a smaller circle in the middle of the mouth triangle
			// Now, I will use the same idea like above, but I have to calculate the center of that smaller circle
			// X_small_circle = R*cos(ship_rotation + PI) + ship_coordinates
			// Y_small_circle = R*sin(ship_rotation + PI) + ship_coordinates
			// I multiply with PI/180 because ship_rotation is in degrees
			distance = sqrt((23*cos((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.x - enemyCoordinates.x)*
							(23*cos((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.x - enemyCoordinates.x) +
							(23*sin((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.y - enemyCoordinates.y)*
							(23*sin((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.y - enemyCoordinates.y));
			// Again, I check the sum of radiuses
			if (distance <= 35){ // 23 + 12
				ship->score += 17;
				ship->showScore(visualContextScore);
				DrawingWindow::removeObject2D_from_Visual2D(enemyZeroPartOne,visualContext);
				DrawingWindow::removeObject2D_from_Visual2D(enemyZeroPartTwo,visualContext);
				return true;
			}
			else { // To see if the enemy is sneaking behind my back!
				distance = sqrt((ship->shipCoordinates.x - enemyCoordinates.x - 11.5)*(ship->shipCoordinates.x - enemyCoordinates.x - 11.5) +
				(ship->shipCoordinates.y - enemyCoordinates.y - 11.5)*(ship->shipCoordinates.y - enemyCoordinates.y - 11.5));

				if (distance <= 39) { 
					ship->livesLeft -= 1; // We haz collision
					ship->shipRespawn();
					ship->shutIt(visualContext); // I'll respawn with a closed mouth
				}
			}
		}

		if (type == 1) {
			distance = sqrt((23*cos((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.x - enemyCoordinates.x)*
							(23*cos((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.x - enemyCoordinates.x) +
							(23*sin((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.y - enemyCoordinates.y)*
							(23*sin((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.y - enemyCoordinates.y));

			if (distance <= 33){ // 23 + 10 
				ship->score += 23;
				ship->showScore(visualContextScore);
				DrawingWindow::removeObject2D_from_Visual2D(enemyOnePartOne,visualContext);
				DrawingWindow::removeObject2D_from_Visual2D(enemyOnePartTwo,visualContext);
				return true;
			}
			else {
				distance = sqrt((ship->shipCoordinates.x - enemyCoordinates.x)*(ship->shipCoordinates.x - enemyCoordinates.x) +
				(ship->shipCoordinates.y - enemyCoordinates.y)*(ship->shipCoordinates.y - enemyCoordinates.y));

				if (distance <= 35) { // 35 = R_ship + R_enemy1
					ship->livesLeft -= 1;
					ship->shipRespawn();
					ship->shutIt(visualContext);
				}
			}
		}

		if (type == 2) {
			distance = sqrt((23*cos((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.x - enemyCoordinates.x)*
							(23*cos((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.x - enemyCoordinates.x) +
							(23*sin((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.y - enemyCoordinates.y)*
							(23*sin((ship->shipRotation + 90)*PI/180) + ship->shipCoordinates.y - enemyCoordinates.y));

			if (distance <= 33.5){ // 23 + 11.5
				ship->score += 7;
				ship->showScore(visualContextScore);
				DrawingWindow::removeObject2D_from_Visual2D(enemyTwoPartOne,visualContext);
				DrawingWindow::removeObject2D_from_Visual2D(enemyTwoPartTwo,visualContext);
				return true;
			}
			else { 
				distance = sqrt((ship->shipCoordinates.x - enemyCoordinates.x - 8)*(ship->shipCoordinates.x - enemyCoordinates.x - 8) +
				(ship->shipCoordinates.y - enemyCoordinates.y - 8)*(ship->shipCoordinates.y - enemyCoordinates.y - 8));

				if (distance <= 33.5) { 
					ship->livesLeft -= 1;
					ship->shipRespawn();
					ship->shutIt(visualContext);
				}
			}
		}		
	}

	return false;

}