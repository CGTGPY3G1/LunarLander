#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"


bool CollisionManager::CheckCollision(GameObject * object1, GameObject * object2) {
	// set the return value to false, this will
	// only change if a collision is found
	bool toReturn = false;
	// get the positions of both objects from their transform components
	Transform * transform1 = object1->GetTransform(), *transform2 = object2->GetTransform();
	Vector2 position1 = transform1->GetPosition(), position2 = transform2->GetPosition();
	// get the colliders from each object and note the number of them
	std::vector<Shape*> object1Colliders = object1->GetColliders(), object2Colliders = object2->GetColliders();
	size_t collider1Count = object1Colliders.size(), collider2Count = object2Colliders.size();
	if (collider1Count == 0 || collider2Count == 0) return false;
	// compare all of the collisders on each object with the colliders 
	// on the other.  the loop exits when a collision is found or there
	// are no more collider pairs to check
	std::string name1 = object1->GetName(), name2 = object2->GetName();
	for(size_t i = 0; i < collider1Count && !toReturn; i++) {
		for(size_t j = 0; j < collider2Count && !toReturn; j++) {
			Shape * shape1 = object1Colliders[i], *shape2 = object2Colliders[j];
			// do a simple radius check to see if the objects are close enough to collide
			toReturn = CheckCircles(position1 + shape1->GetPosition(), shape1->GetRadius(), position2 + shape2->GetPosition(), shape2->GetRadius());
			if(toReturn) { // if they are close enough perform a more complex analysis
				// passes the transformed colliders for polygon collision detection
				toReturn = CheckConvexPoly(shape1->GetTransformed(position1, transform1->GetOrientation().AngleInRadians()), 
										   shape2->GetTransformed(position2, transform2->GetOrientation().AngleInRadians()));
			}	
		}
	}
	return toReturn;
}

bool CollisionManager::CheckCircles(const Vector2 & position1, const float & radius1, const Vector2 & position2, const float & radius2) {
	// get the squared distance between the objects
	Vector2 seperation = (position2 - position1);
	float sqrDistance = seperation.SquareMagnitude();
	// get the squared radius of the objects
	float sqrRadius = (radius1 * radius1) + (radius2 * radius2);
	// return true if distance is less than radius
	if(sqrDistance <= sqrRadius)
		return true;
	return false;
}



bool CollisionManager::CheckConvexPoly(std::vector<Vector2> & poly1, std::vector<Vector2> & poly2) {
	// for each vertex in the first polygon
	for(unsigned int i = 0; i < poly1.size(); i++) {
		unsigned int next = i + 1;
		// get the normal for the edge it and the next represent
		Vector2 normal = (poly1[next == poly1.size() ? 0 : next] - poly1[i]).Normalize().Flip90(true); 
		// project both axes onto the normal and check for a gap between them
		if(MinMaxGap(ProjectOnAxis(poly1, normal), ProjectOnAxis(poly2, normal)))
			return false; // if a gap is found the objects are not colliding
	}
	// same as above but for the second polygon
	for(unsigned int i = 0; i < poly2.size(); i++) {
		unsigned int next = i + 1;
		Vector2 normal = (poly2[next == poly2.size() ? 0 : next] - poly2[i]).Normalize().Flip90(true);
		if(MinMaxGap(ProjectOnAxis(poly1, normal), ProjectOnAxis(poly2, normal)))
			return false;
	}
	return true;
}

Vector2 CollisionManager::ProjectOnAxis(std::vector<Vector2> & poly, Vector2 & axis) {
	// project the first vertex and use
	// the result for both min and max
	float dot = axis.Dot(poly[0]);;
	Vector2 minMax = Vector2(dot, dot);
	// for every other vertex, if the projected position
	// is less that the min or max set the relevant value to it
	for(unsigned int i = 1; i < poly.size(); i++) {
		dot = poly[i].Dot(axis);
		if(dot < minMax.GetX())
			minMax.SetX(dot);
		else if(dot > minMax.GetY())
			minMax.SetY(dot);
	}
	return minMax;
}

bool CollisionManager::MinMaxGap(Vector2 & p1, Vector2 & p2) {
	// if there is a gap return true, else return false
	return (p1.GetX() > p2.GetY() || p1.GetY() <= p2.GetX());
}
