#include "CollisionBox.h"

//constructor
CollisionBox::CollisionBox(vec3 pos, vec3 size) {
	bodyPos = pos, bodySize = size;	//assign new vec3 values to position and size/scale
}


//Axis-Aligned Bounding Box (AABB) collision
//returns bool, true upon collision
bool CollisionBox::collisionAABB(CollisionBox otherBody) {
	return(
		//x axis
		(bodyPos.x + bodySize.x) >= otherBody.bodyPos.x &&
		(otherBody.bodyPos.x + otherBody.bodySize.x) >= bodyPos.x &&
		//y axis
		(bodyPos.y + bodySize.y) >= otherBody.bodyPos.y &&
		(otherBody.bodyPos.y + otherBody.bodySize.y) >= bodyPos.y &&
		//z axis
		(bodyPos.z + bodySize.z) >= otherBody.bodyPos.z &&
		(otherBody.bodyPos.z + otherBody.bodySize.z) >= bodyPos.z
	);
}