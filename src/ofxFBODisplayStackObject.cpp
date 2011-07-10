/*
 *  ofxFboDisplayStackObject.cpp
 *  DisplayList
 *
 *  Created by Paulo Barcelos on 31/10/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */


#include "ofxFboDisplayStackObject.h"

////////////////////////////////////////////////////////////
// CONSTRUCTOR ---------------------------------------------
////////////////////////////////////////////////////////////
ofxFboDisplayStackObject::ofxFboDisplayStackObject() {
	_isFBOAllocated = false;
	ofxDisplayStackObject::ofxDisplayStackObject();
}	
////////////////////////////////////////////////////////////
// setup ------------------------------------------------
////////////////////////////////////////////////////////////
void ofxFboDisplayStackObject::setup(int w, int h){
	fbo.setup(w, h);
}
////////////////////////////////////////////////////////////
// drawInFBO -----------------------------------------------
////////////////////////////////////////////////////////////
void ofxFboDisplayStackObject::drawInFBO(){
	// and draw it inside the fbo, with the color trasformation
	fbo.begin();
	glPushAttrib(GL_CURRENT_BIT);
	ofEnableAlphaBlending();
	ofVec4f tintColor =  colorToGloabal(color);
	glColor4f(tintColor.x, tintColor.y, tintColor.z, tintColor.w);
	if(_baseObjectToBack){if(baseObject != NULL)baseObject->draw(0,0);}
	for (list<ofxDisplayStackObject*>::iterator it = childs.begin(); it!=childs.end(); ++it) (*it)->draw();
	if(!_baseObjectToBack){if(baseObject != NULL)baseObject->draw(0,0);}
	glPopAttrib();
	fbo.end();
	
}
////////////////////////////////////////////////////////////
// draw ----------------------------------------------------
////////////////////////////////////////////////////////////
void ofxFboDisplayStackObject::draw(bool autoDrawInFBO) {
	if(autoDrawInFBO) drawInFBO();
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glScalef(scale.x, scale.y, scale.z);
	// and now draw only fbo with no color transformation
	//ofDisableAlphaBlending(); // <- unfortunetly we have a lot of problems if we try to draw the fbo with alpha, see http://www.openframeworks.cc/forum/viewtopic.php?f=9&t=1643&hilit=fbo+alpha
	fbo.draw(0,0);
	glPopMatrix();
}