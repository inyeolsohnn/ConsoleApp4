#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H
#include<vector>
#include "Animation.h"
#include <SFML/Graphics.hpp>
class AnimationManager
{
private:
	std::vector<Animation> animations;
	

	

public:

	sf::IntRect frameSize;
	sf::IntRect bounds;
	float t;
	int currentAnim;
	AnimationManager()
	{
		this->t = 0.0f;
		this->currentAnim = -1;
	}
	AnimationManager(const sf::IntRect& frameSize)
	{
		this->frameSize = frameSize;

		this->t = 0.0f;
		this->currentAnim = -1;
	}
	~AnimationManager();

	void addAnim(Animation& anim);
	void update(const float dt);
	void changeAnim(unsigned int anim);
};
#endif
