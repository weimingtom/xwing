//
// FontMetrics.cc
//

// All rights reserved.
//

#include <base/inc.hh>
#include <awt/defs.hh>

#include <awt/Font.hh>
#include "FontMetrics.hh"



FontMetrics::FontMetrics ( awt::Font* f ) :
		font_info(XLoadQueryFont(glob::display, f->getFontName()->c_str())) {
	}

unsigned int
FontMetrics::getAscent() {
	return this->font_info->max_bounds.ascent;
	}

unsigned int
FontMetrics::getHeight() {
	return
		this->font_info->max_bounds.ascent +	this->font_info->max_bounds.descent;
	}

unsigned int
FontMetrics::stringWidth ( String* string ) {
	return XTextWidth(this->font_info, string->c_str(), string->length());
	}

unsigned int
FontMetrics::stringWidth ( String& string ) {
	return this->stringWidth(&string);
	}


FontMetrics*
FontMetrics::clone() {
	return new FontMetrics(*this);
	}
