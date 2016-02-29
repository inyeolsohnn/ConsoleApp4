#include "stdafx.h"
#include "AnimationManager.h"



AnimationManager::~AnimationManager()
{
}

void AnimationManager::addAnim(Animation & anim)
{
	this->animations.push_back(anim);
}

void AnimationManager::update(const float dt)
{
	if (currentAnim >= this->animations.size() || currentAnim < 0) {}
	else {
		float duration = this->animations[currentAnim].duration;

		if ((int(t + dt) / duration) > int(t / duration)){
			int currentFrame = ((t + dt) / duration);
			currentFrame %= this->animations[currentAnim].getLength();

			sf::IntRect rect = this->frameSize;
			rect.left = rect.width * currentFrame;
			rect.top = rect.height * this->currentAnim;
			this->bounds = rect;
		}
		this->t += dt;
		if (this->t > duration * this->animations[currentAnim].getLength())
		{
			this->t = 0.0f;
		}
	}
}

void AnimationManager::changeAnim(unsigned int anim)
{
	if (!(currentAnim == anim || anim >= this->animations.size()||anim<0)) {
		this->currentAnim = anim;
		sf::IntRect rect = this->frameSize; //copy constructor
		rect.top = rect.height*anim;
		this->bounds = rect;
		this->t = 0;

	}
	
}
