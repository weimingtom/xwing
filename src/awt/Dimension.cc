////////////////////////////////////////////////// -*- Mode: C++ -*-
//
// Dimension.cc
//

// All rights reserved.
//
//////////////////////////////////////////////////

#include <base/inc.hh>
#include <awt/defs.hh>

#include "Dimension.hh"


////////////////////////////////////////

Dimension::Dimension() : width(0), height(0) {
	}

Dimension::Dimension ( unsigned int w, unsigned int h ) : width(w), height(h) {
	}

bool
Dimension::equals ( Object* o ) {
	Dimension* d = DCAST<Dimension*>(o);
	if ( d != 0 )
		return (this->width == d->width) || (this->height == d->height);

	return false;
	}

double
Dimension::getHeight() {
	return this->height;
	}

double
Dimension::getWidth() {
	return this->width;
	}

Dimension*
Dimension::getSize() {
	return this;
	}

void
Dimension::setSize ( Dimension* d ) {
	this->width = d->width;
	this->height = d->height;
	}

void
Dimension::setSize ( unsigned int w, unsigned int h ) {
	this->width = w;
	this->height = h;
	}

void
Dimension::setSize ( double w, double h ) {
	this->width = SCAST<unsigned int>(w);
	this->height = SCAST<unsigned int>(h);
	}


Dimension*
Dimension::clone() {
	return new Dimension(*this);
}
