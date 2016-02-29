#pragma once
#include "Vector3D.h"
#include "BoundingBox.h"
namespace Moo {
	class BoundingSphere
	{

	public:
		Moo::Vector3D center;
		float radius;
		BoundingSphere() :center(Moo::Vector3D()), radius(0.f) {}
		BoundingSphere(Moo::Vector3D vector, float radius) :center(vector), radius(radius) {}
		~BoundingSphere();

		Moo::ContainmentType contains(Vector3D vector);
		Moo::ContainmentType contains(BoundingBox bBox);
		Moo::ContainmentType contains(BoundingSphere bSphere);
	};

}