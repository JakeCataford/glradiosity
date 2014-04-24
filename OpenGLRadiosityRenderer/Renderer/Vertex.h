//
//  Vertex.h
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/19/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#ifndef __RadiosityRenderer__Vertex__
#define __RadiosityRenderer__Vertex__

#include <iostream>
#include "Vec3.h"
#include "Vec2.h"

class Vertex {
public:
	Vec3 position;
	Vec3 normal;
	Vec2 uv;
	
	Vertex(Vec3, Vec3, Vec2);
	Vertex() : position(Vec3()), normal(Vec3()), uv(Vec2()) {}
	~Vertex() {}
};

#endif /* defined(__RadiosityRenderer__Vertex__) */
