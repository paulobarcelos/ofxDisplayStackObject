#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	image.loadImage("tdf_1972_poster.jpg");
	image.setAnchorPercent(0.5f,0.5f);
	
	dlo.setBaseObject((ofBaseDraws*)&image);
	
	dloChild.setBaseObject((ofBaseDraws*)&image);
	
	dloChildChild.setBaseObject((ofBaseDraws*)&image);
	
	dloChildChild2.setBaseObject((ofBaseDraws*)&image);
	
	dlo.pushChild(&dloChild);
	dloChild.pushChild(&dloChildChild);
	dloChild.pushChild(&dloChildChild2);
	
}

//--------------------------------------------------------------
void testApp::update(){
	dlo.position.x = ofGetWidth()/2 + sin(ofGetElapsedTimef())*200;
	dlo.position.y = ofGetHeight()/2+ cos(ofGetElapsedTimef())*200;
	dlo.scale.x = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;
	dlo.scale.y = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;	
	dlo.rotation.z = ofGetElapsedTimef()*100;	
	dlo.color.w = (sin(ofGetElapsedTimef()*3)+1)/2;	// as we store the color as a ofxVect4f, alpha = w
	
	dloChild.position.y = cos(ofGetElapsedTimef())*200;
	dloChild.position.x = sin(ofGetElapsedTimef())*200;	
	dloChild.scale.x = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;
	dloChild.scale.y = (sin(ofGetElapsedTimef())+1.0f)/2.0f*0.5f+0.5f;	
	dloChild.rotation.z = ofGetElapsedTimef()*100;
	dloChild.color.z = (sin(ofGetElapsedTimef())+1)/2; 	// as we store the color as a ofxVect4f, blue = z	
	
	dloChildChild.position.y = cos(ofGetElapsedTimef())*200;
	dloChildChild.position.x = sin(ofGetElapsedTimef())*200;
	dloChildChild.rotation.z = ofGetElapsedTimef()*100;
	
	globalizedPosition = dloChildChild.positionToGlobal(ofxVec4f(0,image.height/2,0));
	
	localizedPosition.x = 200 + sin(ofGetElapsedTimef())*100;
	localizedPosition.y = 200 + cos(ofGetElapsedTimef())*100;
	
	dloChildChild2.position = dloChild.positionToLocal(localizedPosition);	
}

//--------------------------------------------------------------
void testApp::draw(){
	//glPushMatrix();
	//glTranslatef(250, 250, 0);
	ofSetColor(255, 255, 255);
	dlo.draw();
	
	glPushMatrix();
	glTranslatef(globalizedPosition.x, globalizedPosition.y, globalizedPosition.z);
	ofSetColor(255, 255, 255);
	ofCircle(0,0,10);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(localizedPosition.x, localizedPosition.y, localizedPosition.z);
	ofSetColor(255, 0, 0);
	ofCircle(0,0,10);
	glPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	dlo.popChild(&dloChild);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	dlo.pushChild(&dloChild);
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

