#include "Boid.h"
void Seek(float DeltTime, const ofVec2f& TargetPosition, ofVec2f& InOut_BoidPosition, float& Out_BoidRotation)
{
	float Speed = 200.f;
	ofVec2f Velocity = TargetPosition - InOut_BoidPosition;
	Out_BoidRotation = atan2(Velocity.y, Velocity.x) * 180.f / 3.14f;
	Velocity.normalize();
	Velocity *= Speed;
	InOut_BoidPosition += Velocity * DeltTime;
}
static void DrawOwnMesh()
{
	ofNoFill();
	ofDrawRectangle({ 0,0 }, 50.f, 50.f);
	ofDrawArrow({ 25,25,0 }, { 25,-10,0 }, 10);
	ofFill();
	ofDrawCircle(25, 25, 10);
}

static void DrawBoid(float Size)
{
	ofFill();
	ofSetColor(0,0,0,255);
	ofDrawCircle(0, 0, Size);
	ofNoFill();
	//ofSetColor(50, 100, 150, 255);
	ofDrawTriangle({ 0,Size }, { 2*Size,0 }, {0,-Size});
}


Boid::Boid()
	:m_Rigidbody{ofVec2f(25,25),0.f}
	,Size(25)
	,LastPositon(m_Rigidbody.Positon)
{
	CirclePositions = { ofVec2f(Size,Size),ofVec2f(Size,ofGetWindowHeight()-Size),ofVec2f(ofGetWindowWidth()-Size,ofGetWindowHeight()-Size),ofVec2f(ofGetWindowWidth()-Size,Size) };
}

void Boid::setup()
{

}

void Boid::update(float DeltaTime)
{
	if (CircleMode)
	{
		switch (CirclePosIndex)
		{
		case 0:
			CircleScreen(DeltaTime,CirclePositions[0]);
			break;
		case 1:
			CircleScreen(DeltaTime,CirclePositions[1]);
			break;
		case 2:
			CircleScreen(DeltaTime, CirclePositions[2]);
			break;
		case 3:
			CircleScreen(DeltaTime,CirclePositions[3]);
			break;
		default:
			break;
		}
	}
}

void Boid::draw() 
{
	ofPushMatrix();
	ofTranslate(m_Rigidbody.Positon.x, m_Rigidbody.Positon.y, 0.f);
	ofRotateDeg(m_Rigidbody.Orientation);
	DrawBoid(Size);
	ofPopMatrix();
}

void Boid::CircleScreen(float DeltaTime, const ofVec2f& TargetPositon)
{
	Seek(DeltaTime,TargetPositon,m_Rigidbody.Positon,m_Rigidbody.Orientation);
	float Distance = (TargetPositon - m_Rigidbody.Positon).length();
	if (Distance < 2.f)
	{
		CirclePosIndex++;
		if (CirclePosIndex >= CirclePositions.size())
		{
			CirclePosIndex = 0;
		}
	}
}
