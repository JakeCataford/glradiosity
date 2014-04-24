//
//  Patch.cpp
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/19/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#include "Patch.h"

Patch::Patch(Vertex a, Vertex b, Vertex c) {
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
}
