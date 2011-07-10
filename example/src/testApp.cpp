#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	image.loadImage("tdf_1972_poster.jpg");
	image.setAnchorPercent(0.5f,0.5f);
	
	// set the same baseObject for everyone
	parent.setBaseObject((ofBaseDraws*)&image);	
	childA.setBaseObject((ofBaseDraws*)&image);
	childB.setBaseObject((ofBaseDraws*)&image);
	
	// add the childs to parent's display stack
	parent.pushChild(&childA);
	parent.pushChild(&childB);	
}

//--------------------------------------------------------------
void testApp::update(){
	parent.position.x = ofGetWidth()/2 + sin(ofGetElapsedTimef())*200;
	parent.position.y = ofGetHeight()/2+ cos(ofGetElapsedTimef())*200;
	parent.scale.x = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;
	parent.scale.y = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;	
	parent.rotation.z = ofGetElapsedTimef()*100;	
	parent.color.w = (sin(ofGetElapsedTimef()*3)+1)/2;	// as we store the color as a ofxVect4f, alpha = w	
	
	childA.position.y = cos(ofGetElapsedTimef())*200;
	childA.position.x = sin(ofGetElapsedTimef())*200;	
	childA.scale.x = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;
	childA.scale.y = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;	
	childA.rotation.z = ofGetElapsedTimef()*100;
	childA.color.z = (sin(ofGetElapsedTimef())+1)/2; 	// as we store the color as a ofxVect4f, blue = z	
	
	// convert and store the center position of the childA to a "gobal" position
	globalizedPosition = childA.positionToGlobal(ofVec4f(0,0,0,0));
	
	// positon childB from a "global" coordinate, converted to a "local" coordindate em relation to the parent
	localizedPosition.x = 100;
	localizedPosition.y = 100;
	
	childB.position = parent.positionToLocal(localizedPosition);	
}

//--------------------------------------------------------------
void testApp::draw(){
	// we just draw the parent, and subsequently both children willb e drawn
	parent.draw();
	
	// draw a circle matching the childA, we can know exactly where it is evethough we are out from the coordinate system
	glPushMatrix();
		glTranslatef(globalizedPosition.x, globalizedPosition.y, globalizedPosition.z);
		ofSetColor(255, 0, 0);
		ofCircle(0,0,10);
	glPopMatrix();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'a') parent.popChild(&childA);
	if (key == 'b') parent.popChild(&childB);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if (key == 'a') parent.pushChild(&childA);
	if (key == 'b') parent.pushChild(&childB);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

