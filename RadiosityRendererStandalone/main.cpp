//
//  main.cpp
//  RadiosityRendererStandalone
//
//  Created by Jake Cataford on 4/22/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "GLRenderer.h"

// This file is so that i dont have to use maya to develop the renderer. Whole thing crashes on exceptions.

int main(int argc, const char * argv[])
{
	SDL_Window *window = SDL_CreateWindow( "Radiosity Renderer Viewport", 0, 0, 1080, 720,
										  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLRenderer renderer = GLRenderer(1080,720);
	GLuint buffer = renderer.RenderToScreen();
	
	GLubyte *glPixels = new GLubyte[4 * 1080 * 720]; //4 RGBA
	
	glReadBuffer(buffer);
	glReadPixels(0, 0, 1080, 720, GL_RGBA, GL_UNSIGNED_BYTE, glPixels);
	
	printf("%i", buffer);
	
	
	
	SDL_GL_SwapWindow(window);
	
	bool running = true;
	SDL_Event event;
	while (running) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				running = false;
			}
		}
	}
	
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	

	
    return 0;
}

