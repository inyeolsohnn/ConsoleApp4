#pragma once
#include "Vector3D.h"
namespace Moo {
	class Vector4D :
		public Vector3D
	{
	public:
		Vector4D(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {
		}
		Vector4D(const Vector3D& vec3, float w): x(vec3.x), y(vec3.y), z(vec3.z), w(w) {
			
		}
		~Vector4D();

	public:
		float x;
		float y;
		float z;
		float w;
	};

}