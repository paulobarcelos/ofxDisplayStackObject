/*
 *  ofxDisplayStackObject.cpp
 *  DisplayList
 *
 *  Created by Paulo Barcelos on 31/10/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */


#include "ofxDisplayStackObject.h"

////////////////////////////////////////////////////////////
// CONSTRUCTOR ---------------------------------------------
////////////////////////////////////////////////////////////
ofxDisplayStackObject::ofxDisplayStackObject() {
	this->baseObject = NULL;
	position = 0;
	scale = 1.0f;
	rotation = 0;
	color = 1.0f;
	parent = NULL;
	_baseObjectToBack = true;
}	
////////////////////////////////////////////////////////////
// setBaseObject -------------------------------------------
////////////////////////////////////////////////////////////
void ofxDisplayStackObject::setBaseObject(ofBaseDraws* baseObject) {
	this->baseObject = baseObject;
}
////////////////////////////////////////////////////////////
// pushChild -----------------------------------------------
////////////////////////////////////////////////////////////
void ofxDisplayStackObject::pushChild(ofxDisplayStackObject* child){
	child->parent = this;
	childs.push_back(child);
}
////////////////////////////////////////////////////////////
// pushChildAt ---------------------------------------------
////////////////////////////////////////////////////////////
bool ofxDisplayStackObject::pushChildAt(ofxDisplayStackObject* child, int position){
	if (position > childs.size()) return false;
	
	list<ofxDisplayStackObject*>::iterator it = childs.begin();
	for (int i=0; i<position-1; i++ ) it++;	
	
	child->parent = this;
	childs.insert(it, child);
	return true;
}
////////////////////////////////////////////////////////////
// popChild ------------------------------------------------
////////////////////////////////////////////////////////////
bool ofxDisplayStackObject::popChild(ofxDisplayStackObject* child){
	for (list<ofxDisplayStackObject*>::iterator it = childs.begin(); it!=childs.end(); ++it){
		if (child == *it) {
			(*it)->parent = NULL;
			childs.erase(it);
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////
// popChildAt ----------------------------------------------
////////////////////////////////////////////////////////////
bool ofxDisplayStackObject::popChildAt(int position){
	if (position > childs.size()) return false;
	
	list<ofxDisplayStackObject*>::iterator it = childs.begin();
	for (int i=0; i<position-1; i++ ) it++;
	
	(*it)->parent = NULL;
	childs.erase(it);
	return true;
}
////////////////////////////////////////////////////////////
// baseObjectToBack ----------------------------------------
////////////////////////////////////////////////////////////
void ofxDisplayStackObject::baseObjectToBack(){
	_baseObjectToBack = true;
}
////////////////////////////////////////////////////////////
// baseObjectToFront ---------------------------------------
////////////////////////////////////////////////////////////
void ofxDisplayStackObject::baseObjectToFront(){
	_baseObjectToBack = false;
}
////////////////////////////////////////////////////////////
// positionToGlobal ----------------------------------------
////////////////////////////////////////////////////////////
ofxVec4f ofxDisplayStackObject::positionToGlobal(ofxVec4f inputPositon, ofxDisplayStackObject * relativeParent){
	inputPositon *= scale;

	float dist = sqrt(inputPositon.x * inputPositon.x + inputPositon.y * inputPositon.y);
	float angle = atan2(inputPositon.y, inputPositon.x);
		
	ofxVec4f outputPositon = this->position;
	outputPositon.x += dist * cosf(angle + rotation.z*DEG_TO_RAD);
	outputPositon.y += dist * sinf(angle + rotation.z*DEG_TO_RAD);
	
	if(parent != relativeParent && parent != NULL) outputPositon = parent->positionToGlobal(outputPositon, relativeParent);	
	return outputPositon;
}
////////////////////////////////////////////////////////////
// positionToLocal -----------------------------------------
////////////////////////////////////////////////////////////
ofxVec4f ofxDisplayStackObject::positionToLocal(ofxVec4f inputPositon){
	//http://www.vbforums.com/showthread.php?t=527338
	if(parent != NULL) inputPositon = parent->positionToLocal(inputPositon);
	
	inputPositon -= this->position;
	inputPositon /= scale;
	
	ofxVec4f outputPositon;
	float radRotation = -rotation.z * DEG_TO_RAD;
	outputPositon.x = inputPositon.x * cosf(radRotation) - inputPositon.y * sinf(radRotation);
	outputPositon.y = inputPositon.x * sinf(radRotation) + inputPositon.y * cosf(radRotation);
	
	return outputPositon;
}
////////////////////////////////////////////////////////////
// colorToGloabal ------------------------------------------
////////////////////////////////////////////////////////////
ofxVec4f ofxDisplayStackObject::colorToGloabal(ofxVec4f inputColor) {
	if(parent!=NULL)
	{
		ofxVec4f outputColor = inputColor;
			
		// clamp the color to the parents value
		outputColor.x = ofClamp(outputColor.x, outputColor.x, parent->color.x);
		outputColor.y = ofClamp(outputColor.y, outputColor.y, parent->color.y);
		outputColor.z = ofClamp(outputColor.z, outputColor.z, parent->color.z);
		outputColor.w = ofClamp(outputColor.w, outputColor.w, parent->color.w);
		
		// and recursively do the same for all parents above
		outputColor = parent->colorToGloabal(outputColor);
		
		return outputColor;
	}
	else return inputColor;
}
////////////////////////////////////////////////////////////
// getHeight -----------------------------------------------
////////////////////////////////////////////////////////////
float ofxDisplayStackObject::getHeight() {
	if(baseObject!=NULL) return baseObject->getHeight();
	else return 0.f;
}
////////////////////////////////////////////////////////////
// getWidth ------------------------------------------------
////////////////////////////////////////////////////////////
float ofxDisplayStackObject::getWidth() {
	if(baseObject!=NULL) return baseObject->getWidth();
	else return 0.f;
}
////////////////////////////////////////////////////////////
// draw ----------------------------------------------------
////////////////////////////////////////////////////////////
void ofxDisplayStackObject::draw() {
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glScalef(scale.x, scale.y, scale.z);
		glPushAttrib(GL_CURRENT_BIT);
			// apply the color transformation from the parents
			ofEnableAlphaBlending();
			ofxVec4f tintColor =  colorToGloabal(color);
			glColor4f(tintColor.x, tintColor.y, tintColor.z, tintColor.w);
			if(_baseObjectToBack){if(baseObject != NULL)baseObject->draw(0,0);}
			for (list<ofxDisplayStackObject*>::iterator it = childs.begin(); it!=childs.end(); ++it) (*it)->draw();
			if(!_baseObjectToBack){if(baseObject != NULL)baseObject->draw(0,0);}
		glPopAttrib();
	glPopMatrix();
}

////////////////////////////////////////////////////////////
// overloaded operators ------------------------------------
////////////////////////////////////////////////////////////
ofxDisplayStackObject& ofxDisplayStackObject::operator=(const ofxDisplayStackObject &rhs)
{
	if(this != &rhs)
	{
		this->baseObject =	rhs.baseObject;
		/*this->position =	rhs.position;
		this->scale =		rhs.scale;
		this->rotation =	rhs.rotation;
		this->color.r =		rhs.color.r;
		this->color.g =		rhs.color.g;
		this->color.b =		rhs.color.b;
		this->color.a =		rhs.color.a;*/
	}
	return *this;
}


int ofxDisplayStackObject::operator==(const ofxDisplayStackObject &rhs) const
{
	if(this->baseObject !=	rhs.baseObject)	return 0;
	/*if(this->position.x	!=	rhs.position.x)	return 0;
	if(this->position.y	!=	rhs.position.y)	return 0;
	if(this->position.z	!=	rhs.position.z)	return 0;
	if(this->scale.x	!=	rhs.scale.x)		return 0;
	if(this->scale.y	!=	rhs.scale.y)		return 0;
	if(this->scale.z	!=	rhs.scale.z)		return 0;
	if(this->rotation.x	!=	rhs.rotation.x)	return 0;
	if(this->rotation.y	!=	rhs.rotation.y)	return 0;
	if(this->rotation.z	!=	rhs.rotation.z)	return 0;*/
	return 1;
}
