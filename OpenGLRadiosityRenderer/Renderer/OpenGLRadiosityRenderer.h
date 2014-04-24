//
//  RadiosityRenderer.h
//  OpenGLRadiosityRenderer
//
//  Created by Jake Cataford on 4/20/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#ifndef OpenGLRadiosityRenderer_RadiosityRenderer_h
#define OpenGLRadiosityRenderer_RadiosityRenderer_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "GLRenderer.h"
#include "Vec3.h"
#include "Vertex.h"
#include "StdAfx.h"
#include <maya/MFnPlugin.h>

class RadiosityRenderer : public MPxCommand {
public:
	RadiosityRenderer() {}
	~RadiosityRenderer() {}
	MStatus prepareRenderView();
	MStatus render();
	MStatus	doIt ( const MArgList& );
	
	static void* creator();
	
	static MSyntax	newSyntax();
	MStatus parseSyntax (MArgDatabase &argData);
	MStatus renderBufferToRenderView();
	MStatus IterateThroughDag();
	void printTransformData(const MDagPath&);
	
	static const char * cmdName;
	MArgList args;
	
	int windowWidth;
	int windowHeight;
	
private:
	bool doNotClearBackground;
};

#endif
