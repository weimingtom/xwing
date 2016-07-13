//
// XButton.cc
//

// All rights reserved.
//


#include <xwing/defs.hh>
#include <xwing/XComponent.hh>
#include <xwing/AbstractButton.hh>
#include <xwing/XButton.hh>



XButton::XButton() : psize(new Dimension())
{
	this->init();
}

XButton::XButton ( String* s ) :
    AbstractButton(),
    MouseAdapter(),
    label(s->clone()),
    psize(new Dimension())
{

	this->init();
}

XButton::XButton ( String& s ) :
    AbstractButton(),
    MouseAdapter(),
    label(s.clone()),
    psize(new Dimension())
{

	this->init();
}

Dimension*
XButton::getPreferredSize()
{
	unsigned int pwidth, pheight;
	FontMetrics* m = this->getFontMetrics(this->getFont());

	if ( m )
	{
		pwidth = m->stringWidth(this->label);
		pheight = m->getHeight();

		pwidth += pwidth >> 2;
		pheight *= 2;

		delete m;

		this->psize = new Dimension(pwidth, pheight);
	}

	return this->psize;
}

void
XButton::setText ( String& s )
{
	this->label = s.clone();
	this->repaint();
}



void
XButton::paint ( Graphics* g )
{
	////////////////////////////////////////
	// Colors if button pressed.
	////////////////////////////////////////

	if ( this->isMousePressed && this->isMouseInside )
		this->setBackground(Color::darkgray->clone());
	else
		this->setBackground(Color::gray->clone());
		
	Dimension* size = this->getSize();

	g->setColor(this->getBackground());
	g->fill3DRect(0, 0, size->width, size->height);

	////////////////////////////////////////
	// Draw comp boundary.
	////////////////////////////////////////

	// g->draw3DRect(0, 0, size->width, size->height);

	////////////////////////////////////////
	// Draw label.
	////////////////////////////////////////

	if ( this->label->length() )
	{
		g->setColor(this->getForeground());

		FontMetrics* m = g->getFontMetrics();
		unsigned int sw = m->stringWidth(this->label);
		unsigned int sh = m->getHeight();
		unsigned int x = (size->width - sw) / 2;
		unsigned int y = (size->height - sh) / 2;

		delete m;

		g->drawString(this->label, x, y);
	}

	////////////////////////////////////////
	// Restore original color.
	////////////////////////////////////////
}

void
XButton::mouseEntered ( MouseEvent* evt )
{
	if ( this->isMouseInside == false )
	{
		this->isMouseInside = true;

		if (this->isMousePressed == true)
		{
			this->repaint();
		} }
}

void
XButton::mouseExited ( MouseEvent* evt )
{
	if ( this->isMouseInside == true )
	{
		this->isMouseInside = false;

		if ( this->isMousePressed == true )
		{
			repaint();
		} }
}

void
XButton::mousePressed ( MouseEvent* evt )
{
#ifdef DEBUG_MOUSE
	out << "XButton::mousePressed()." << nl;
#endif // DEBUG_MOUSE

	this->isMousePressed = true;
	repaint();
}

void
XButton::mouseReleased ( MouseEvent* evt )
{
#ifdef DEBUG_MOUSE
	out << "XButton::mouseReleased() -- PAIR." << nl;
#endif // DEBUG_MOUSE

	this->isMousePressed = false;
	if ( this->isMouseInside == true )
		repaint();
}

void
XButton::mouseClicked ( MouseEvent* evt )
{
#ifdef DEBUG_MOUSE
	out << "XButton::mouseClicked()!" << nl;
#endif // DEBUG_MOUSE

	this->fireActionPerformed(new ActionEvent(this, this->label));
}

void
XButton::init()
{
	this->setForeground(Color::black->clone());
	this->addMouseListener(this);
}


XButton*
XButton::clone()
{
	return new XButton(*this);
}
