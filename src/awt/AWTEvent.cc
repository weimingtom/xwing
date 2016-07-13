////////////////////////////////////////////////// -*- Mode: C++ -*-
//
// AWTEvent.cc
//

// All rights reserved.
//
//////////////////////////////////////////////////

#include <base/inc.hh>
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
#include "AWTEvent.hh"

#include <awt/ComponentEvent.hh>
#include <awt/InputEvent.hh>
#include <awt/MouseEvent.hh>
#include <awt/EventListener.hh>
#include <awt/MouseListener.hh>
#include <awt/Component.hh>


////////////////////////////////////////

AWTEvent::AWTEvent ( Object* s, int i ) : EventObject(s), id(i)
{
}

int
AWTEvent::getId()
{
	return this->id;
}

////////////////////////////////////////
//
// PROTECTED methods
//
////////////////////////////////////////

void
AWTEvent::consume()
{
	this->consumed = true;
}

bool
AWTEvent::isConsumed()
{
	return this->consumed;
}

////////////////////////////////////////
//
// REQUIRED methods
//
////////////////////////////////////////

AWTEvent*
AWTEvent::clone()
{
	return new AWTEvent(*this);
}

//////////////////////////////////////////////////
//

// Date:	16 July 1999
//
//////////////////////////////////////////////////
