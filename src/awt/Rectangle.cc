//
// Rectangle.cc
//

// All rights reserved.
//


#include <base/inc.hh>
#include <awt/defs.hh>

#include "Rectangle.hh"


Rectangle::Rectangle ( unsigned int width, unsigned int height ) :
		width(width), height(height) {
	}

Rectangle::Rectangle ( int x, int y, unsigned int width, unsigned int height) :
		x(x), y(y), width(width), height(height) {
	}

bool
Rectangle::contains ( int x, int y ) {
	return
		(x > this->x) && (y > this->y) &&
		(x < (this->x + this->width)) && (y < (this->y + this->height));
	}


Rectangle*
Rectangle::clone() {
	return new Rectangle(*this);
	}
