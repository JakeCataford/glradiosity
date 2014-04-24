//
//  plugin.cpp
//  OpenGLRadiosityRenderer
//
//  Created by Jake Cataford on 4/20/14.
//    Copyright (c) 2014 Carleton University. All rights reserved.
//

//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "RadiosityRenderer.h"
#include <maya/MSimple.h>

DeclareSimpleCommand(GLRadiosityRenderer, "Carleton University", "0.0.1");

MStatus GLRadiosityRenderer::doIt(const MArgList& args) {
	MStatus status = MS::kSuccess;
	RadiosityRenderer renderer = RadiosityRenderer();
	status = renderer.render();
	return status;
}