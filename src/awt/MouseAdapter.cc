//
// MouseAdapter.cc
//

// All rights reserved.
//


#include <awt/defs.hh>

#include <awt/EventObject.hh>
#include <awt/AWTEvent.hh>
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

#include <awt/Component.hh>

#include "MouseAdapter.hh"




MouseAdapter::MouseAdapter()
{
}


void MouseAdapter::mouseEntered ( MouseEvent* )
{
}


void MouseAdapter::mouseExited ( MouseEvent* )
{
}


void MouseAdapter::mousePressed ( MouseEvent* )
{
}


void MouseAdapter::mouseReleased ( MouseEvent* )
{
}


void MouseAdapter::mouseClicked ( MouseEvent* )
{
}


MouseAdapter* MouseAdapter::clone()
{
	return new MouseAdapter(that);
}
