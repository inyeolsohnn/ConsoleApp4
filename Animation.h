#ifndef ANIMATION_H
#define ANIMATION_H
class Animation
{
public:
	unsigned int startFrame;
	unsigned int endFrame;

	float duration;
	Animation(unsigned int startFrame, unsigned int endframe, float duration);
	~Animation();
	unsigned int getLength() {
		return this->endFrame - this->startFrame + 1;
	}
};
#endif
