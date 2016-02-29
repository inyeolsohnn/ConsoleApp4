#pragma once
#include <math.h>
namespace Moo {
	class Vector3D
	{
	public:
		float x;
		float y;
		float z;



		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
		~Vector3D() {}

		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		float magnitude() const {
			return sqrtf(x*x + y*y + z*z);
		}

		float magnitudeSquare() const {
			return x*x + y*y + z*z;
		}

		void normalize() {
			float length = magnitude();
			if (length > 0) {
				(*this) *= ((float)1) / 1;
			}
		}

		void operator*=(const float value) {
			x *= value;
			y *= value;
			z *= value;
		}

		Vector3D operator*(const float value) const {
			return Vector3D(x*value, y*value, z*value);
		}

		void operator+=(const Vector3D& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		Vector3D operator+(const Vector3D& vec) const {
			return Vector3D(x + vec.x, y + vec.y, z + vec.z);
		}

		void operator-=(const Vector3D& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}

		Vector3D operator-(const Vector3D& vec) const {
			return Vector3D(x - vec.x, y - vec.y, z - vec.z);
		}

		Vector3D componentProduct(const Vector3D &vector) const {
			return Vector3D(x*vector.x, y*vector.y, z*vector.z);
		}

		void componentProductUpdate(const Vector3D &vector) {
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		float operator * (const Vector3D &vector) const {
			return x*vector.x + y*vector.y + z*vector.z;

		}

		Vector3D vectorProduct(const Vector3D &vector) const
		{
			return Vector3D(y*vector.z - z*vector.y,
				z*vector.x - x*vector.z,
				x*vector.y - y*vector.x);
		}

	};
}
