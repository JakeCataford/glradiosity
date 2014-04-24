//
//  GLRenderer.h
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/20/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#ifndef __RadiosityRenderer__GLRenderer__
#define __RadiosityRenderer__GLRenderer__

#include <iostream>
#include <vector>
#include <OpenGL/gl3.h>
#include "Patch.h"

class GLRenderer {
public:
	//std::vector <Patch> patches;
	GLRenderer(int, int);
	~GLRenderer() {}
	GLuint RenderToScreen();
	GLuint RenderToBuffer();
	int width;
	int height;
	GLuint FramebufferName;

private:
	GLuint frameBuffer;
	GLuint Render();
	bool initializeRenderTexture();
};

#endif /* defined(__RadiosityRenderer__GLRenderer__) */
