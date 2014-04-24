//
//  main.cpp
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/19/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//


#include "OpenGLRadiosityRenderer.h"

static const char * kDoNotClearBackground		= "-b";
static const char * kDoNotClearBackgroundLong	= "-background";

const char * RadiosityRenderer::cmdName = "RadiosityRender";

MStatus initializePlugin( MObject obj )
{
	MFnPlugin	plugin( obj, PLUGIN_COMPANY, "4.5" );
	MStatus		stat;
	stat = plugin.registerCommand(	RadiosityRenderer::cmdName,
								  RadiosityRenderer::creator,
								  RadiosityRenderer::newSyntax);
	if ( !stat )
		stat.perror( "registerCommand" );
	return stat;
}

//
// Description:
//		unregister the command
//
MStatus uninitializePlugin( MObject obj )
{
	MFnPlugin	plugin( obj );
	MStatus		stat;
	stat = plugin.deregisterCommand( RadiosityRenderer::cmdName );
	if ( !stat )
		stat.perror( "deregisterCommand" );
	return stat;
}


void* RadiosityRenderer::creator()
{
	return new RadiosityRenderer;
}

MSyntax RadiosityRenderer::newSyntax()
{
	MStatus status;
	MSyntax syntax;
	syntax.addFlag( kDoNotClearBackground, kDoNotClearBackgroundLong );
	CHECK_MSTATUS_AND_RETURN(status, syntax);
	return syntax;
}

MStatus RadiosityRenderer::parseSyntax (MArgDatabase &argData)
{
	// Get the flag values, otherwise the default values are used.
	doNotClearBackground = argData.isFlagSet( kDoNotClearBackground );
	
	return MS::kSuccess;
}


MStatus RadiosityRenderer::doIt(const MArgList &args)
{
	this->args = args;
	windowWidth = 640;
	windowHeight = 480;
	
	SDL_Window *window = SDL_CreateWindow( "Radiosity Renderer Viewport", 0, 0, 640, 480,
										   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	
		
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	M3dView curView = M3dView::active3dView();
	MDagPath camDagPath;
	curView.getCamera( camDagPath );
	
	IterateThroughDag();
	//Pass DAG to renderer, let renderer render scene...
	
	SDL_GL_MakeCurrent(window, glcontext);
	GLRenderer renderer = GLRenderer(640,480);
	renderer.RenderToScreen();
	
	SDL_GL_SwapWindow(window);
	
	//Write pixels to render window...
	
	prepareRenderView();
	SDL_GL_MakeCurrent(window, glcontext);
	renderBufferToRenderView();

	sleep(1);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return MS::kSuccess;
}

MStatus RadiosityRenderer::IterateThroughDag() {
	MStatus status;
	MItDag::TraversalType traversalType = MItDag::kDepthFirst;
	MFn::Type filter = MFn::kMesh;
	MItDag dagIterator( traversalType, filter, &status);
	
	for ( ; !dagIterator.isDone(); dagIterator.next() ) {
        MDagPath dagPath;
        status = dagIterator.getPath(dagPath);
        if ( !status ) {
            status.perror("MItDag::getPath");
            continue;
        }
		
		MFnDagNode dagNode(dagPath, &status);
        if ( !status ) {
            status.perror("MFnDagNode constructor");
            continue;
        }

        //objectCount += 1;
        if (dagPath.hasFn(MFn::kMesh)) {
			MFnMesh shape (dagPath, &status);
			printTransformData(dagPath);
		}
	}
	return status;
}

MStatus RadiosityRenderer::prepareRenderView() {
	
	if (!MRenderView::doesRenderEditorExist())
	{
		setResult( "Cannot renderViewRender in batch render mode. "
				  "Please run in interactive mode, "
				  "so that the render editor exists." );
		return MS::kFailure;
	}
	else
	{
		printf("Past doesRenderEditorExist()");
	}
	
	// get optional flags
	MArgDatabase	argData( syntax(), args );
	parseSyntax( argData );
	
	M3dView curView = M3dView::active3dView();
	MDagPath camDagPath;
	curView.getCamera( camDagPath );
	printf("Rendering camera: %s", camDagPath.fullPathName().asChar());
	
	if( MRenderView::setCurrentCamera( camDagPath ) != MS::kSuccess )
	{
		setResult( "renderViewRender: error occurred in setCurrentCamera." );
		return MS::kFailure;
	}
	
	if (MRenderView::startRender( windowWidth, windowHeight, doNotClearBackground) != MS::kSuccess)
	{
		setResult( "renderViewRender: error occured in startRender." );
		return MS::kFailure;
	}
	
	return MS::kSuccess;
}

MStatus RadiosityRenderer::renderBufferToRenderView() {
	
	RV_PIXEL* pixels = new RV_PIXEL[windowWidth * windowHeight];
	GLubyte *glPixels = new GLubyte[4 * windowWidth * windowHeight]; //4 RGBA
	
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, glPixels);
	
	int index = 0;
	int staggered_index = 0;
	for (int i = 0; i < windowWidth; i++) {
		for (int j = 0; j < windowHeight; j++) {
			pixels[index].r = glPixels[staggered_index];
			staggered_index ++;
			pixels[index].g = glPixels[staggered_index];
			staggered_index ++;
			pixels[index].b = glPixels[staggered_index];
			staggered_index ++;
			pixels[index].a = glPixels[staggered_index];
			staggered_index ++;
			index++;
		}
	}
	
	delete [] glPixels;
	
	if (MRenderView::updatePixels(0, windowWidth, 0, windowHeight, pixels) != MS::kSuccess)
	{
		setResult( "renderViewRender: error occured in updatePixels." );
		delete [] pixels;
		return MS::kFailure;
	}
	
	if (MRenderView::refresh(0, windowWidth, 0, windowHeight) != MS::kSuccess)
	{
		setResult( "renderViewRender: error occured in refresh." );
		return MS::kFailure;
	}
	
	if (MRenderView::endRender() != MS::kSuccess)
	{
		setResult( "renderViewRender: error occured in render." );
		return MS::kFailure;
	}
	
	delete [] pixels;
	return MS::kSuccess;
}

void RadiosityRenderer::printTransformData(const MDagPath& dagPath)
{
    printf("got");
	
	
	//This method simply determines the transformation information on the DAG node and prints it out.
    MStatus status;
    MObject transformNode = dagPath.transform(&status);
    // This node has no transform - i.e., it’s the world node
    if (!status && status.statusCode () == MStatus::kInvalidParameter)
        return;
    MFnDagNode transform (transformNode, &status);
    if (!status) {
        status.perror("MFnDagNode constructor");
        return;
    }
    MTransformationMatrix matrix (transform.transformationMatrix());
	//cout << " translation: " << matrix.translation(MSpace::kWorld)
	//<< endl;
    double threeDoubles[3];
    MTransformationMatrix::RotationOrder rOrder;
    matrix.getRotation (threeDoubles, rOrder, MSpace::kWorld);
	
	cout << " rotation: ["
	<< threeDoubles[0] << ", "
	<< threeDoubles[1] << ", "
	<< threeDoubles[2] << "]\n";
    matrix.getScale (threeDoubles, MSpace::kWorld);
	
	cout << " scale: ["
	<< threeDoubles[0] << ", "
	<< threeDoubles[1] << ", "
	<< threeDoubles[2] << "]\n";
	
}

