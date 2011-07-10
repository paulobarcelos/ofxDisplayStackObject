/*
 *  ofxFboDisplayStackObject.h
 *  DisplayList
 *
 *  Created by Paulo Barcelos on 31/10/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */


#pragma once

#include "ofxDisplayStackObject.h"
////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ofxFboDisplayStackObject : public ofxDisplayStackObject {
public:
	ofxFboDisplayStackObject();
	
	virtual void	setup(int w, int h);
	
	// We can can draw only the fbo to the screen (and don't change the fbo content), or draw inside the fbo first and subsequently draw it to the screen (default)
	virtual void	draw(bool autoDrawInFBO = true);
	// You can alsojust draw inside the fbo, without rendering it to the screen
	virtual void	drawInFBO();
	
	ofFbo			fbo;
						
private:
	bool			_isFBOAllocated;
};