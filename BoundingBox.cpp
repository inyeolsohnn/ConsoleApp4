#include "stdafx.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include <iostream>
using namespace Moo;




BoundingBox::~BoundingBox()
{
}

//needs to be updated
ContainmentType BoundingBox::contains(BoundingBox box)
{

	if (box.max.x < min.x
		|| box.min.x > max.x
		|| box.max.y < min.y
		|| box.min.y > max.y
		|| box.max.z < min.z
		|| box.min.z > max.z)
		return ContainmentType::Disjoint;


	if (box.min.x >= min.x
		&& box.max.x <= max.x
		&& box.min.y >= min.y
		&& box.max.y <= max.y
		&& box.min.z >= min.z
		&& box.max.z <= max.z)
		return ContainmentType::Contain;

	return ContainmentType::Intersect;
}

ContainmentType BoundingBox::contains(Moo::BoundingSphere bSphere)
{

	return ContainmentType();
}

ContainmentType BoundingBox::contains(Vector3D point)
{
	if (point.x < min.x
		|| point.x > max.x
		|| point.y < min.y
		|| point.y > max.y
		|| point.z < min.z
		|| point.z > max.z)
	{
		return Disjoint;
	}//or if point is on box because coordonate of point is lesser or equal
	else if (point.x == min.x
		|| point.x == max.x
		|| point.y == min.y
		|| point.y == max.y
		|| point.z == min.z
		|| point.z == max.z)
		return Intersect;
	else
		return Contain;

	
}

bool BoundingBox::intersects(BoundingBox bBox)
{
	return(this->max.x >= bBox.min.x &&
		this->min.x <= bBox.max.x &&
		this->max.y >= bBox.min.y &&
		this->min.y <= bBox.max.y &&
		this->max.z >= bBox.min.z &&
		this->min.z <= bBox.max.z);
}

