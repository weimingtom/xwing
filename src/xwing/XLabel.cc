//
// XLabel.cc
//

// All rights reserved.
//


#include <xwing/defs.hh>
#include <xwing/XComponent.hh>
#include "XLabel.hh"




XLabel::XLabel() : psize(new Dimension()) {
	this->setForeground(Color::lavender->clone());
	}

XLabel::XLabel ( String* s ) : label(s->clone()), psize(new Dimension()) {
	this->setForeground(Color::lavender->clone());
	}

Dimension*
XLabel::getPreferredSize() {
	unsigned int pwidth, pheight;
	FontMetrics* m = this->getFontMetrics(this->getFont());

	if ( m ) {
		pwidth = m->stringWidth(this->label);
		pheight = m->getHeight() << 1;

		delete m;

		this->psize = new Dimension(pwidth, pheight);
		}

	return this->psize;
	}

void
XLabel::setText ( String& text )
{
	this->label = text.clone();
	this->repaint();
}


void
XLabel::setText ( String *text )
{
	this->label = text->clone();
	this->repaint();
}


void
XLabel::paint ( Graphics* g ) {
	if ( this->label->length() ) {
		Dimension* size = this->getSize();

		FontMetrics* m = g->getFontMetrics();
		unsigned int x = (size->width - m->stringWidth(this->label)) / 2;
		unsigned int y = (size->height - m->getHeight()) / 2;

		delete m;

		g->drawString(this->label, 0, y);
		}
	}


XLabel*
XLabel::clone() {
	return new XLabel(*this);
	}
