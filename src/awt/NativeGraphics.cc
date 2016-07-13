//
// NativeGraphics.cc
//

// All rights reserved.
//


#include <awt/defs.hh>

#include <awt/Color.hh>
#include <awt/Font.hh>
#include <awt/FontMetrics.hh>
#include <awt/Rectangle.hh>
#include <awt/Graphics.hh>

#include <stdlib.h>
#include <stdio.h>

#include "NativeGraphics.hh"


////////////////////////////////////////

NativeGraphics::NativeGraphics() :
		gc(0), clip_mask(0), font(Graphics::SWING_FONT->clone()),
		cx(0), cy(0), tx(0), ty(0), width(0), height(0) {
	}

Graphics*
NativeGraphics::create() {
	return this->clone();
	}

void
NativeGraphics::drawPoint ( int x, int y ) {
	x += this->tx;
	y += this->ty;

	this->pDrawPoint(x, y);
	}

void
NativeGraphics::drawLine ( int x1, int y1,
						   int x2, int y2 ) {
	
	////////////////////////////////////////
	// First, translate origin by (tx, ty).
	////////////////////////////////////////

	x1 += this->tx;
	y1 += this->ty;

	x2 += this->tx;
	y2 += this->ty;

	this->pDrawLine(x1, y1, x2, y2);
	}

void
NativeGraphics::drawRect ( int x, int y,
						   unsigned int width, unsigned int height ) {

	////////////////////////////////////////
	// First, translate origin by (tx, ty).
	////////////////////////////////////////

	x += this->tx;
	y += this->ty;

	XDrawRectangle(glob::display, glob::win, this->gc,
				   x, y, width-1, height-2);
	}

void
NativeGraphics::fillRect ( int x, int y,
						   unsigned int width, unsigned int height ) {

	--width;
	height -= 2;

	////////////////////////////////////////
	// First, translate origin by (tx, ty).
	////////////////////////////////////////

	x += this->tx;
	y += this->ty;

	XFillRectangle(glob::display, glob::win, this->gc,
				   x, y, width, height);
	}

void
NativeGraphics::fill3DRect ( int x, int y,
							 unsigned int width, unsigned int height ) {

	this->draw3DRect(x,y,width,height);
	this->fillRect(x+2, y+2, width-3, height-3);	// shortened by 4 on all sides
	}

void
NativeGraphics::draw3DRect ( int x1, int y1,
							 unsigned int width, unsigned int height,
							 bool raised ) {

	////////////////////////////////////////
	// First, translate origin by (tx, ty).
	////////////////////////////////////////

	--width;
	height -= 2;

	x1 += this->tx;
	y1 += this->ty;

	int x2 = x1 + width;
	int y2 = y1 + height;

	int x5 = x1 + 1;
	int y5 = y1 + 1;

	int x6 = x2 - 1;
	int y6 = y2 - 1;

	unsigned int save_color = this->values.foreground;

	this->setColor(new Color(0,0,0));
	this->pDrawLine(x1, y1, x2, y1); // out, top
	this->pDrawLine(x1, y1, x1, y2); // out, left
	this->pDrawLine(x5, y6, x6, y6); // in, bottom
	this->pDrawLine(x6, y5, x6, y6); // in, right

	this->setColor(new Color(255,255,255));
	this->pDrawLine(x5, y5, x6, y5); // in, top
	this->pDrawLine(x5, y5, x5, y6); // in, left
	this->pDrawLine(x1, y2, x2, y2); // out, bottom
	this->pDrawLine(x2, y1, x2, y2); // out, right

	this->setColor(new Color(save_color));
	}

void
NativeGraphics::drawString ( String* s, int x, int y ) {
	x += this->tx;
	y += this->ty;

	FontMetrics metrics(this->font);

 	XDrawString(glob::display, glob::win, this->gc,
				x, (y + metrics.getAscent()),
				s->c_str(), s->length());
	}

void
NativeGraphics::drawString ( String& s, int x, int y ) {
	this->drawString(&s, x, y);
	}

void
NativeGraphics::setClip ( int x, int y,
						  unsigned int width, unsigned int height ) {

	////////////////////////////////////////
	// Enlarge extent by 1 on both sides to
	// accomodate extent of component (see
	// X windows rectangle semantics->
	////////////////////////////////////////

	this->cx += x;
	this->cy += y;

	this->width = width;
	this->height = height;

	this->createClip();
	}

void
NativeGraphics::setColor ( Color* c ) {
	this->mask = GCForeground;
	this->values.foreground = c->getRGB();

	this->updateGC();
	}

void
NativeGraphics::setFont ( awt::Font* font ) {
	this->font = font->clone();
	fprintf(stderr, "===>NativeGraphics::setFont 1\n");
	Font font_id = XLoadFont(glob::display, this->font->getFontName()->c_str());
	fprintf(stderr, "===>NativeGraphics::setFont 2\n");
	XSetFont(glob::display, this->gc, font_id);
	fprintf(stderr, "===>NativeGraphics::setFont 3\n");
	} 

Color*
NativeGraphics::getColor() {
	return new Color(this->values.foreground);
	}

awt::Font*
NativeGraphics::getFont() {
	return this->font;
	}

FontMetrics*
NativeGraphics::getFontMetrics() {
	return new FontMetrics(this->font);
	}

void
NativeGraphics::translate ( int dx, int dy ) {
	this->tx += dx;
	this->ty += dy;
	}

void
NativeGraphics::dispose() {
	if ( this->gc )
		XFreeGC(glob::display, this->gc);

	this->gc = 0;
	}

////////////////////////////////////////
//
// PRIVATE methods
//
////////////////////////////////////////

void
NativeGraphics::initGC() {
	this->values.background = Color::gray->getRGB();
	this->values.foreground = BlackPixel(glob::display,
										glob::screen);
	this->values.line_width = 0;

	this->mask = ( GCBackground |
				  GCForeground |
				  GCLineWidth );

	this->gc = XCreateGC(glob::display, glob::win,
						this->mask, &this->values);

	this->setFont(this->font);
	}

void
NativeGraphics::updateGC() {
	XChangeGC(glob::display, this->gc, this->mask, &this->values);

	this->mask = 0;
	}

void
NativeGraphics::createClip() {
	this->clip_mask = XCreateRegion();

	XRectangle hole = { this->cx, this->cy, this->width, this->height };
	XUnionRectWithRegion(&hole, this->clip_mask, this->clip_mask);
	XSetRegion(glob::display, this->gc, this->clip_mask);
	XDestroyRegion(this->clip_mask);
	}

////////////////////////////////////////
//
// PRIVATE methods 
//
////////////////////////////////////////

void
NativeGraphics::pDrawLine ( int x1, int y1, int x2, int y2 ) {

	XDrawLine(glob::display, glob::win, this->gc, x1, y1, x2, y2);
	}

void
NativeGraphics::pDrawPoint ( int x, int y ) {
	XDrawPoint(glob::display, glob::win, this->gc, x, y);
	}

////////////////////////////////////////
//
// REQUIRED methods
//
////////////////////////////////////////

/*
NativeGraphics::~NativeGraphics() {
#ifdef DEBUG_GRAPHICS
	cerr << "NativeGraphics::dtor()." << nl;
#endif // DEBUG_GRAPHICS

	this->dispose();
	}
*/

NativeGraphics::NativeGraphics ( NativeGraphics& orig ) :
		mask(orig.mask), font(orig.font->clone()),
		cx(orig.cx), cy(orig.cy), tx(orig.tx), ty(orig.ty),
		width(orig.width), height(orig.height) {

	this->copy(orig);
	}

NativeGraphics&
NativeGraphics::operator = ( NativeGraphics& rhs ) {
	if ( this != &rhs ) {
		this->mask = rhs.mask;
		this->font = rhs.font->clone();
		this->cx = rhs.cx;
		this->cy = rhs.cy;
		this->tx = rhs.tx;
		this->ty = rhs.ty;
		this->width = rhs.width;
		this->height = rhs.height;
		}

	this->copy(rhs);

	return *this;
	}

void
NativeGraphics::copy ( NativeGraphics& orig ) {
	unsigned long m = ( GCForeground |
						GCBackground |
						GCLineWidth |
						GCFont |
						GCClipXOrigin |
						GCClipYOrigin );

	XGetGCValues(glob::display, orig.gc, m, &this->values);
	this->gc = XCreateGC(glob::display, glob::win, m, &this->values);

	if ( this->gc == 0 ) {
		cerr << "Could not allocate new Graphics Context, exiting." << endl;
		exit(1);
		}

	this->createClip();
	}

bool
NativeGraphics::equals ( Object& rhs ) {
	NativeGraphics& obj = DCAST<NativeGraphics&>(rhs);

	return
		(this->cx == obj.cy) || (this->cy == obj.cy) ||
		(this->tx == obj.tx) || (this->ty == obj.ty) ||
		(this->width == obj.width) || (this->height == obj.width);
	}

NativeGraphics*
NativeGraphics::clone() {
	return new NativeGraphics(*this);
	}
