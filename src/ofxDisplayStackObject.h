/*
 *  ofxDisplayStackObject.h
 *  DisplayList
 *
 *  Created by Paulo Barcelos on 31/10/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

// Also check http://www.openframeworks.cc/forum/viewtopic.php?f=10&t=2292&hilit=displaylist

#pragma once

#include <iostream>
#include <list>
#include "ofMain.h"
//#include "ofVec4f.h"
////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ofxDisplayStackObject {
public:
	ofxDisplayStackObject();
	
	virtual void				setBaseObject(ofBaseDraws* baseObject);
	
	virtual void				draw();
	
	virtual float				getHeight(); // Will only return the dimesions of the baseObject;
	virtual float				getWidth(); // Will only return the dimesions of the baseObject;
	
	virtual void				pushChild(ofxDisplayStackObject* object);
	virtual bool				popChild(ofxDisplayStackObject* object);
	virtual bool				pushChildAt(ofxDisplayStackObject* object, int position);
	virtual bool				popChildAt(int position);
	
	virtual void				baseObjectToBack(); // will draw the base object BEHIND the display list (default behaviour)
	virtual void				baseObjectToFront(); //  will draw the base object IN FRONT OF the display list
	
	//virtual bool				contains(ofxDisplayStackObject* object); // TODO
	
	virtual ofVec4f			positionToGlobal	(ofVec4f inputPositon, ofxDisplayStackObject * relativeParent = NULL);
	virtual ofVec4f			positionToLocal		(ofVec4f inputPositon);
	//virtual ofVec4f			rotationToGlobal	(ofVec4f rotation);
	//virtual ofVec4f			rotationToLocal		(ofVec4f rotation);
	
	virtual ofVec4f			colorToGloabal(ofVec4f inputColor);
	
	ofBaseDraws*				baseObject;	
	ofVec4f					position;	
	ofVec4f					scale;
	ofVec4f					rotation;
	ofVec4f					color;
	
	ofxDisplayStackObject*		parent;
	list<ofxDisplayStackObject*> childs;
	
	// overloaded operators for std::list functions
	virtual ofxDisplayStackObject&	operator=(const ofxDisplayStackObject &rhs);
	virtual int						operator==(const ofxDisplayStackObject &rhs) const;

	bool						_baseObjectToBack;
};