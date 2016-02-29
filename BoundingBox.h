#pragma once
#include "Vector3D.h"


namespace Moo {
	//axis aligned 3d box
	class BoundingSphere;
	enum ContainmentType { Disjoint=0, Intersect=1, Contain=2 };

	class BoundingBox
	{
	public:
		
		Vector3D min;
		Vector3D max;
		Vector3D cent;

		BoundingBox() {}
		BoundingBox(Vector3D min, Vector3D max): min(min), max(max) {
			setCenter();
		}
		~BoundingBox();

		Vector3D getCorner001() {
			return Vector3D(min.x, min.y, max.z);
		}

		Vector3D getCorner010() {
			return Vector3D(min.x, max.y, min.z);
		}

		Vector3D getCorner011() {
			return Vector3D(min.x, max.y, max.z);
		}

		Vector3D getCorner100() {
			return Vector3D(max.x, min.y, min.z);
		}

		Vector3D getCorner101() {
			return Vector3D(max.x, min.y, max.z);
		}

		Vector3D getCorner110() {
			return Vector3D(max.x, max.y, min.z);
		}

		Vector3D getCorner111() {
			return Vector3D(max.x, max.y, max.z);
		}

		bool isValid() {
			return min.x < max.x && min.y < max.y && min.z < max.z;
		}

		void setCenter() {
			this->cent.x = (max.x + min.x) / 2;
			this->cent.y = (max.y + min.y) / 2;
			this->cent.z = (max.z + min.z) / 2;
		}
		

		ContainmentType contains(BoundingBox bBox);
		ContainmentType contains(BoundingSphere bSphere);
		ContainmentType contains(Vector3D vector);
		bool intersects(BoundingBox bBox);
		
	};

}