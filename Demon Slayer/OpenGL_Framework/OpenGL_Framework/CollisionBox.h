#pragma once
#include "Vector.h"

class CollisionBox
{
public:
	CollisionBox(vec3, vec3);			//param constructor (needs 2 vec3 xyz values, position & size/scale)
	CollisionBox() {}					//default constructor
	~CollisionBox() {}					//destructor
	bool collisionAABB(CollisionBox);	//collision check function, returns true upon collision

private:
	vec3 bodyPos, bodySize;	//position & size variables
};
