#pragma once

#include <math.h>
#include <cmath>
#include <algorithm> 
#include "BoundingBox.h"

/**
@brief A collection of collision functions
*/
namespace Collision
{
	bool boxBoxCollision(BoundingBox *a, BoundingBox* b);


	const float PI = 3.14159265359;

}


