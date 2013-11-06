#pragma once
#include "Visual2D.h"
#include "Object2D.h"
#include "Transform2D.h"
#include "Circle2D.h"
#include "Rectangle2d.h"
#include "Line2D.h"
#include "Polygon2D.h"
#include "DrawingWindow.h"
#include "Player2D.h"

#define PI 3.14159265358979323846

class Enemy {

public:

	Rectangle2D *enemyZeroPartOne;
	Rectangle2D *enemyZeroPartTwo;

	Circle2D *enemyOnePartOne;
	Polygon2D *enemyOnePartTwo;

	Rectangle2D *enemyTwoPartOne;
	Circle2D * enemyTwoPartTwo;

	Enemy();
	Enemy(Visual2D* visualContext,int type);
	~Enemy(void);

	Point2D enemyCoordinates; 
	void restrictBoundaries();
	void followShip(Player2D *ship,float enemyStep,int type);
	bool collision(Visual2D* visualContext,Player2D *ship,int type,Visual2D* visualContextScore);

};

