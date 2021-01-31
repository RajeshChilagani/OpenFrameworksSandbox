#include "ofApp.h"

static ofVec2f TargetPosition = ofVec2f::zero();
bool CalRot = false;
void UpdateTargetPositon()
{
	TargetPosition.x = ofRandom(20, 700);
	TargetPosition.y = ofRandom(20, 600);
	/*TargetPosition.x = 400;
	TargetPosition.y = 500;*/
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
	UpdateTargetPositon();
	BoidPosition = ofVec2f(100, 100);
}

//--------------------------------------------------------------
void ofApp::update()
{
	double deltaTime = ofGetLastFrameTime();
	ofVec2f DirectionVector =  TargetPosition - BoidPosition;
	DirectionVector.normalize();
	//BoidOrientationInDeg += acos(DirectionVector.dot(ForwardVector)) * 180.f / 3.14f;
	BoidOrientationInDeg += (atan2f(DirectionVector.y, DirectionVector.x) - atan2f(ForwardVector.y, ForwardVector.x)) * 180.f / 3.14f;
	ofLog Log(OF_LOG_NOTICE, "Angle:%f", BoidOrientationInDeg);
	CalForward();
	BoidPosition += (DirectionVector * deltaTime * 75.f);
	static float TimeElapsed = 0.0f;
	TimeElapsed += deltaTime;
	if (TimeElapsed> 2.f)
	{
		UpdateTargetPositon();
		CalRot = true;
		TimeElapsed = 0.0f;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient({ 255,0,0 }, { 0,0,255 }, OF_GRADIENT_LINEAR);
	ofDrawCircle(TargetPosition.x,TargetPosition.y,25);
	ofTranslate(BoidPosition.x, BoidPosition.y, 0);
	ofRotateDeg(BoidOrientationInDeg);
	ofNoFill();
	ofDrawRectangle({ 0,0 }, 50.f, 50.f);
	ofDrawArrow({ 25,25,0 }, {25,-10,0}, 10);
	ofFill();
	ofDrawCircle(25, 25, 10);
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
