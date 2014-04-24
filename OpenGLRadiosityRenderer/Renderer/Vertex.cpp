//
//  Vertex.cpp
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/19/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#include "Vertex.h"

Vertex::Vertex(Vec3 position, Vec3 normal, Vec2 uv) {
	this->position = position;
	this->normal = normal;
	this->uv = uv;
}