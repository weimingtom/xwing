//
// Color.cc
//

// All rights reserved.
//


#include <base/inc.hh>
#include <awt/defs.hh>

#include "Color.hh"

Color* Color::black = new Color(0,0,0);
Color* Color::gray = new Color(204,204,204);
Color* Color::darkgray = new Color(153,153,153);
Color* Color::white = new Color(255,255,255);
Color* Color::lavender = new Color(102,102,153);



Color::Color ( unsigned int rgb ) :
    alpha(255),
    red((rgb & RED_MASK)),
    green((rgb & GREEN_MASK) >> 8),
    blue((rgb & BLUE_MASK) >> 16)
{
}


Color::Color ( unsigned int r, unsigned int g, unsigned int b ) :
    alpha(255), red(r), green(g), blue(b)
{
	if ( this->red > 255 )
		this->red %= 255;
	if ( this->green > 255 )
		this->green %= 255;
	if ( this->blue > 255 )
		this->blue %= 255;
}


Color* Color::clone()
{
	return new Color(*this);
}


unsigned int Color::getAlpha()
{
	return this->alpha;
}


unsigned int Color::getRed()
{
	return this->red;
}


unsigned int Color::getGreen()
{
	return this->green;
}


unsigned int Color::getBlue()
{
	return this->blue;
}


unsigned int Color::getRGB()
{
	return
		(this->alpha << 24) +
		(this->red << 16)   +
		(this->green << 8)  +
		(this->blue);
}

