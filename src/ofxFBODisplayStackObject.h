/*
 *  ofxFBODisplayStackObject.h
 *  DisplayList
 *
 *  Created by Paulo Barcelos on 31/10/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */


#pragma once

#include "ofxDisplayStackObject.h" 
#include "ofxFBOTexture.h"
////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ofxFBODisplayStackObject : public ofxDisplayStackObject {
public:
	ofxFBODisplayStackObject();
	
	// We do not extend ofxFBOTexture, but we provide access to its public methods
	virtual void				allocate(int w, int h, int internalGlDataType = GL_RGBA, int numSamples = 0);
	virtual void				clear();
	virtual void				clear(float r, float g, float b, float a);	
	virtual void				bindAsTexture();	
	virtual void*				getPixels();	
	
	// We can can draw only the fbo to the screen (and don't change the fbo content), or draw inside the fbo first and subsequently draw it to the screen (default)
	virtual void				draw(bool autoDrawInFBO = true);
	// You can alsojust draw inside the fbo, without rendering it to the screen
	virtual void				drawInFBO();
	
	ofxFBOTexture				fbo;
						
private:
	bool						_isFBOAllocated;
};