#include "ofApp.h"

#include <random>
//BoidOrientationInDeg += acos(DirectionVector.dot(ForwardVector)) * 180.f / 3.14f;
//BoidOrientationInDeg += (atan2f(DirectionVector.y, DirectionVector.x) - atan2f(ForwardVector.y, ForwardVector.x)) * 180.f / 3.14f;
static ofVec2f TargetPosition = ofVec2f::zero();

void Steer(float DeltTime, const ofVec2f& TargetPosition, ofVec2f& InOut_BoidPosition, float& Out_BoidRotation)
{
	float Speed = 200.f;
	ofVec2f Velocity = TargetPosition - InOut_BoidPosition;
	Out_BoidRotation = atan2(Velocity.y, Velocity.x) * 180.f / 3.14f;
	Velocity.normalize();
	Velocity *= Speed;
	InOut_BoidPosition += Velocity * DeltTime;
}

void Flee(float DeltTime, const ofVec2f& TargetPosition, ofVec2f& InOut_BoidPosition, float& Out_BoidRotation)
{
	float Speed = 200.f;
	ofVec2f Velocity = InOut_BoidPosition - TargetPosition;
	Out_BoidRotation = atan2(Velocity.x, -Velocity.y) * 180.f / 3.14f;
	Velocity.normalize();
	Velocity *= Speed;
	InOut_BoidPosition += Velocity * DeltTime;
}

void Arrive(float DeltTime, const ofVec2f& TargetPosition, ofVec2f& InOut_BoidPosition, float& Out_BoidRotation)
{
	float MaxSpeed = 200.f;
	float Radius = 2.f;
	ofVec2f Velocity = TargetPosition - InOut_BoidPosition;
	Out_BoidRotation = atan2(Velocity.x, -Velocity.y) * 180.f / 3.14f;
	if (Velocity.length() < Radius)
		return;
	Velocity /= 0.25f;
	if (Velocity.length() > MaxSpeed)
	{
		Velocity.normalize();
		Velocity *= MaxSpeed;
	}
	InOut_BoidPosition += Velocity * DeltTime;
}

void Wander(float DeltTime, const ofVec2f& ForwardVector, ofVec2f& InOut_BoidPosition, float& Out_BoidRotation)
{
	float MaxSpeed = 50.f;
	ofVec2f Velocity = ForwardVector * MaxSpeed;
	InOut_BoidPosition += Velocity * DeltTime;
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//// perform 4 trials, each succeeds 1 in 2 times
	//std::binomial_distribution<> d(4, 0.5);
	//Out_BoidRotation = d(gen) * 15.f;
	auto Rand = []() {
		float result;
		result = static_cast<float>(rand()) / (RAND_MAX/50.f);
		return result;
	};
	float RandomBinomial = Rand();
	Out_BoidRotation = RandomBinomial + 25.f + 90.f;
	ofLog(OF_LOG_NOTICE, "Rot:%f", Out_BoidRotation);
}

void UpdateTargetPositon()
{
	TargetPosition.x = ofRandom(20, 700);
	TargetPosition.y = ofRandom(20, 600);
	//TargetPosition.x = 100;
	//TargetPosition.y = 500;
}
ofApp::ofApp()
	:BoidPosition(ofVec2f::zero())
	, BoidOrientationInDeg(0.f)
	, ForwardVector(0, -1)
{
	CalForward();
}
//--------------------------------------------------------------
void ofApp::setup()
{
	Gui.setup("Movement Algorithms", "Settings.xml",700,10);
	Gui.add(AlgorithmField.setup("Algorithm", AlgorithmName));
	Gui.add(Toggle.setup("Circle"));
	UpdateTargetPositon();
	BoidPosition = ofVec2f(400, 300);
}

//--------------------------------------------------------------
void ofApp::update()
{
	double deltaTime = ofGetLastFrameTime();
	m_Boid.update(deltaTime);
	static float TimeElapsed = 0.0f;
	TimeElapsed += deltaTime;
	if (TimeElapsed > 2.f)
	{
		UpdateTargetPositon();
		TimeElapsed = 0.0f;
	}
	m_Boid.CircleMode = Toggle;
	AlgorithmName = AlgorithmField;
	if (AlgorithmName == "Seek")
	{
		Steer(deltaTime, TargetPosition, BoidPosition, BoidOrientationInDeg);
	}
	else if (AlgorithmName == "Flee")
	{
		Flee(deltaTime, TargetPosition, BoidPosition, BoidOrientationInDeg);
	}
	else if (AlgorithmName == "Arrive")
	{
		Arrive(deltaTime, TargetPosition, BoidPosition, BoidOrientationInDeg);
	}
	else if (AlgorithmName == "Wander")
	{
		CalForward();
		Wander(deltaTime, ForwardVector, BoidPosition, BoidOrientationInDeg);
	}
	ofLog Log(OF_LOG_NOTICE, "Angle:%f", BoidOrientationInDeg);
	CalForward();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient({ 147,165,207 }, { 228,239,233 }, OF_GRADIENT_LINEAR);
	ofFill();
	ofSetColor(255, 255, 255, 255);
	ofDrawCircle(TargetPosition.x, TargetPosition.y, 25);
	m_Boid.draw();
	Gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::CalForward()
{
	ForwardVector.x = sin(glm::radians(BoidOrientationInDeg));
	ForwardVector.y = -cos(glm::radians(BoidOrientationInDeg));
	/*ForwardVector.x = ForwardVector.x * cos(ofDegToRad(BoidOrientationInDeg)) - ForwardVector.y * sin(ofDegToRad(BoidOrientationInDeg));
	ForwardVector.y = ForwardVector.x * sin(ofDegToRad(BoidOrientationInDeg)) + ForwardVector.y * cos(ofDegToRad(BoidOrientationInDeg));*/
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
