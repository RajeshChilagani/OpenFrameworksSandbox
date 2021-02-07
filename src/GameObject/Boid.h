#pragma once
#include <vector>
#include "../Types.h"
class Boid
{
public:
	Boid();
	void setup();
	void update(float DeltaTime);
	void draw();
	Rigidbody m_Rigidbody;
	bool CircleMode=false;
private:
	void CircleScreen(float DeltaTime, const ofVec2f& TargetPositon);
	ofVec2f LastPositon;
	float Size;
	uint16_t CirclePosIndex=0;
	std::vector<ofVec2f> CirclePositions;
};

