#pragma once
#include"Vector3D.h"
namespace Moo {
	class Particle
	{
		//variables
	private:
	protected:
	public:
		Vector3D position;
		Vector3D velocity;
		Vector3D acceleration;
		//functions
	public:
		Particle();
		~Particle();
	};
}

