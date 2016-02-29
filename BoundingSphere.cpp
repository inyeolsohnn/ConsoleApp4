#include "stdafx.h"
#include "BoundingSphere.h"
#include "Vector3D.h"
using namespace Moo;



Moo::BoundingSphere::~BoundingSphere()
{
}

ContainmentType Moo::BoundingSphere::contains(Vector3D vector)
{
	return ContainmentType();
}

ContainmentType Moo::BoundingSphere::contains(BoundingBox bBox)
{
	return ContainmentType();
}

ContainmentType Moo::BoundingSphere::contains(BoundingSphere bSphere)
{
	return ContainmentType();
}

