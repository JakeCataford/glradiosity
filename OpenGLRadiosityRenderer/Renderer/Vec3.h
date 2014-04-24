//
//  Vec3.h
//  RadiosityRenderer
//
//  Created by Jake Cataford on 4/19/14.
//  Copyright (c) 2014 Carleton University. All rights reserved.
//

#ifndef __RadiosityRenderer__Vec__
#define __RadiosityRenderer__Vec__

#include <iostream>

class Vec3 {
	public:
	float x;
	float y;
	float z;
	Vec3() : x(0),y(0),z(0) {}
	~Vec3() {}
};

#endif /* defined(__RadiosityRenderer__Vec__) */
