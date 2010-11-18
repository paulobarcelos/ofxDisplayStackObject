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
#include "ofxVec4f.h"
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
	
	virtual ofxVec4f			positionToGlobal	(ofxVec4f inputPositon, ofxDisplayStackObject * relativeParent = NULL);
	virtual ofxVec4f			positionToLocal		(ofxVec4f inputPositon);
	//virtual ofxVec4f			rotationToGlobal	(ofxVec4f rotation);
	//virtual ofxVec4f			rotationToLocal		(ofxVec4f rotation);
	
	virtual ofxVec4f			colorToGloabal(ofxVec4f inputColor);
	
	ofBaseDraws*				baseObject;	
	ofxVec4f					position;	
	ofxVec4f					scale;
	ofxVec4f					rotation;
	ofxVec4f					color;
	
	ofxDisplayStackObject*		parent;
	list<ofxDisplayStackObject*> childs;
	
	// overloaded operators for std::list functions
	virtual ofxDisplayStackObject&	operator=(const ofxDisplayStackObject &rhs);
	virtual int						operator==(const ofxDisplayStackObject &rhs) const;

	bool						_baseObjectToBack;
};