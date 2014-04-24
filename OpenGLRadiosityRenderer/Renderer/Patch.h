//
//  Patch.h
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/19/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#ifndef __RadiosityRenderer__Patch__
#define __RadiosityRenderer__Patch__

#include <iostream>
#include "Vertex.h"
#include "Vec3.h"

class Patch {
public:
	Vertex vertices[3];
	Vec3 emission;
	Vec3 incidentLight;
	Vec3 excidentLight;

	Patch(Vertex, Vertex, Vertex);
	~Patch();
};

#endif /* defined(__RadiosityRenderer__Patch__) */
