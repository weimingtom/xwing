//
// Component.cc
//

// All rights reserved.
//


#include <awt/defs.hh>

#include <awt/Color.hh>
#include <awt/Font.hh>
#include <awt/FontMetrics.hh>
#include <awt/Dimension.hh>
#include <awt/Rectangle.hh>
#include <awt/Insets.hh>
#include <awt/Border.hh>
#include <awt/Graphics.hh>

#include <awt/EventObject.hh>
#include <awt/AWTEvent.hh>
#include <awt/ComponentEvent.hh>
#include <awt/InputEvent.hh>
#include <awt/MouseEvent.hh>

#include <awt/EventListener.hh>
#include <awt/MouseListener.hh>

#include "Component.hh"


Component::Component() :
    parent(0), graphics(0),
    x(0), y(0), width(0), height(0), border(0),
    font(Graphics::SWING_FONT->clone()),
    //foreground(Color::black->clone()),
    //background(Color::gray->clone())
    ml_list(new PtrList<MouseListener>())
{
	// font = Graphics::SWING_FONT->clone();
	foreground = Color::black->clone();
	background = Color::gray->clone();
}


Border* Component::getBorder()
{
	return this->border;
}


Dimension* Component::getSize()
{
	return new Dimension(this->width, this->height);
}


Rectangle* Component::getBounds()
{
	return new Rectangle(this->x, this->y, this->width, this->height);
}


int Component::getX()
{
	return this->x;
}


int Component::getY()
{
	return this->y;
}


Component *Component::getParent()
{
	return CCAST<Component*>(this->parent);
}


Graphics *Component::getGraphics()
{
	return this->graphics;
}


awt::Font *Component::getFont()
{
	return this->font;
}


FontMetrics *Component::getFontMetrics ( awt::Font *font )
{
	return new FontMetrics(font);
}


Color *Component::getForeground()
{
	return this->foreground;
}


Color *Component::getBackground()
{
	return this->background;
}


Component *Component::getComponentAt ( int x, int y )
{
	if ( this->getBounds()->contains(x,y) )
		return this;

	return 0;
}


void Component::setBorder ( Border* border )
{
	if ( this->border != border )
		this->border = border->clone();
}


void Component::setFont ( awt::Font* font )
{
	this->font = font->clone();
}


void Component::setForeground ( Color* c )
{
	this->foreground = c->clone();
}


void Component::setBackground ( Color* c )
{
	this->background = c->clone();
}


void Component::setSize ( Dimension* d )
{
	this->setSize(d->width, d->height);
}


void Component::setSize ( unsigned int w, unsigned int h )
{
	this->width = w;
	this->height = h;
}


void Component::setLocation ( unsigned int x, unsigned int y )
{
	this->x = x;
	this->y = y;
}


void Component::paint ( Graphics* g )
{
	////////////////////////////////////////
	// Paint border.
	////////////////////////////////////////

	if ( this->border )
		this->border->paintBorder(this, g, this->x, this->y,
					 this->width, this->height);
}


void Component::paintAll ( Graphics* g )
{
	if ( g )
		this->paint(g);
}


void Component::repaint()
{
	if ( this->graphics )
		this->update(this->graphics);
}


void Component::update ( Graphics* g )
{
	////////////////////////////////////////
	// Copy GC to component.
	////////////////////////////////////////

	if ( g )
	{
		if ( this->graphics != g )
		{
			if ( this->graphics )
				this->graphics->dispose();
			this->graphics = g->create();
		}

		////////////////////////////////////////
		// Fill background with color.
		////////////////////////////////////////

		this->graphics->setColor(this->background);
		this->graphics->fillRect(0, 0, this->width, this->height);

		////////////////////////////////////////
		// Paint myself.
		////////////////////////////////////////

		this->graphics->setColor(this->foreground);
		this->paint(this->graphics);
	}
}


void Component::validate()
{
	Dimension* psize;

	psize = this->getPreferredSize();
	cout << "psize: " << *psize << endl;
}


void Component::removeNotify()
{
	if ( this->graphics )
		this->graphics->dispose();
	this->graphics = 0;
}


void Component::addMouseListener ( MouseListener* l )
{
	this->ml_list->add(l);
}


void Component::dispatchEvent ( AWTEvent* evt )
{
	this->processEvent(evt);
}


void Component::processEvent ( AWTEvent* evt )
{
	Component* parent = this->getParent();
	if ( parent )
		parent->processEvent(evt);

	unsigned int count = this->ml_list->size();

	if ( count )
	{
		MouseEvent* mouse_event = DCAST<MouseEvent*>(evt);
		if ( mouse_event )
		{
			this->processMouseEvent(mouse_event);
		}
	}
}


void Component::processMouseEvent ( MouseEvent* evt )
{
	MouseListener* l;
	unsigned int count = this->ml_list->size();

	for ( int i = 0; i < count; ++i )
	{
		l = this->ml_list->getPtr(i);

		switch ( evt->getId() )
		{
		    case MouseEvent::MOUSE_PRESSED:
			    l->mousePressed(evt);
			    break;

		    case MouseEvent::MOUSE_RELEASED:
			    l->mouseReleased(evt);
			    break;

		    case MouseEvent::MOUSE_ENTERED:
			    l->mouseEntered(evt);
			    break;

		    case MouseEvent::MOUSE_EXITED:
			    l->mouseExited(evt);
			    break;

		    case MouseEvent::MOUSE_CLICKED:
			    l->mouseClicked(evt);
			    break;
		}
	}
}
