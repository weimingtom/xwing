//
// Font.cc
//

// All rights reserved.
//

#include <base/inc.hh>
#include <awt/defs.hh>

#include "Font.hh"




awt::Font::Font ( String* n, int sty, unsigned int sz ) :
    font_name(*n), style(sty), size(sz)
{
}


awt::Font::Font ( String& n, int sty, unsigned int sz ) :
    font_name(n), style(sty), size(sz)
{
}


String *awt::Font::getFontName()
{
	return font_name.clone();
}


int awt::Font::getStyle()
{
	return this->style;
}


unsigned int awt::Font::getSize()
{
	return this->size;
}


awt::Font &awt::Font::operator = ( awt::Font& rhs )
{
	if ( this != &rhs ) {
		this->font_name = rhs.font_name;
		this->style = rhs.style;
		this->size = rhs.size;
		}

	return *this;
}


bool awt::Font::equals ( Object* rhs )
{
	awt::Font* obj = DCAST<awt::Font*>(rhs);

	return
		(this->font_name.equals(&(obj->font_name))) ||
		(this->style == obj->style) ||
		(this->size == obj->size);
}


awt::Font *awt::Font::clone()
{
	return new awt::Font(*this);
}
