#pragma once

#include <math.h>
#include <cmath>
#include <algorithm> 
#include "BoundingBox.h"

struct FaceQuery {
	float largDist;
	int faceIndex;
};

struct EdgeQuery {

};

/**
@brief A collection of collision functions
*/
namespace Collision
{
	bool boxBoxCollision(BoundingBox *a, BoundingBox* b);

	bool SATOverlap(BoundingBox *a, BoundingBox* b);

	bool SATIntersection(BoundingBox *a, BoundingBox* b);

	FaceQuery QueryFaceDirs(BoundingBox *a, BoundingBox* b);
	float QueryEdgeDirs(BoundingBox *a, BoundingBox *b);

	float compareIntervals(Interval i1, Interval i2);

	const float PI = 3.14159265359;


	float distanceFaceVec(Face* a, glm::vec3 b);
}


