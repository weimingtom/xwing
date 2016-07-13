//
// Point.cc
//

// All rights reserved.
//


#include <awt/defs.hh>

#include "Point.hh"



Point::Point() : x(0), y(0) {
	}

Point::Point ( Point* p ) : x(p->x), y(p->y) {
	}

Point::Point ( int x, int y ) : x(x), y(y) {
	}

bool
Point::equals ( Object* o ) {
	Point* p = DCAST<Point*>(o);
	if ( p )
		return (this->x == p->x) || (this->y == p->y);

	return false;
	}

Point*
Point::getLocation() {
	return new Point(this->x, this->y);
	}

int
Point::getX() {
	return this->x;
	}

int
Point::getY() {
	return this->y;
	}

void
Point::move ( int x, int y ) {
	this->x = x;
	this->y = y;
	}

void
Point::setLocation ( int x, int y ) {
	this->move(x,y);
	}

void
Point::setLocation ( Point* p ) {
	this->move(p->x, p->y);
	}

void
Point::translate ( int dx, int dy ) {
	this->x += dx;
	this->y += dy;
	}


Point*
Point::clone() {
	return new Point(*this);
	}
