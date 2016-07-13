//
// Frame.cc
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
#include <awt/NativeGraphics.hh>

#include <awt/EventObject.hh>
#include <awt/AWTEvent.hh>
#include <awt/ComponentEvent.hh>
#include <awt/InputEvent.hh>
#include <awt/MouseEvent.hh>

#include <awt/EventListener.hh>
#include <awt/MouseListener.hh>

#include <awt/Component.hh>
#include <awt/LayoutManager.hh>
#include <awt/Container.hh>

#include <stdlib.h>
#include <stdio.h>

#include "Frame.hh"


////////////////////////////////////////

Frame::Frame() :
    isMapped(false),
    title("An Xwing App")
{
	this->init();
}

Frame::Frame ( String* s ) :
    isMapped(false),
    title(*s)
{
	this->init();
}

Frame::Frame ( String& s ) :
    isMapped(false),
    title(s)
{
	this->init();
}

void Frame::addNotify()
{
	Dimension* size = this->getSize();
	fprintf(stderr, ">>>>addNotify 1\n");
	this->width = size->width;
	this->height = size->height;
	fprintf(stderr, ">>>>addNotify 2\n");
	////////////////////////////////////////
	// Create window.
	////////////////////////////////////////

	if ( !this->isMapped )
	{
		glob::win =
			XCreateSimpleWindow(glob::display,
					    RootWindow(glob::display, glob::screen),
					    0, 0, this->width, this->height, 0,
					    WhitePixel(glob::display, glob::screen),
					    Color::gray->getRGB());
		this->isMapped = true;
	}
	fprintf(stderr, ">>>>addNotify 3\n");
	XTextProperty name;
	char* window_name = CCAST<char*>(this->title.c_str());
	XStringListToTextProperty(&window_name, 1, &name);
	XSetWMName(glob::display, glob::win, &name);
	fprintf(stderr, ">>>>addNotify 4\n");
	////////////////////////////////////////
	// Select events to listen for.
	////////////////////////////////////////
	fprintf(stderr, ">>>>addNotify 5\n");
	XSelectInput( glob::display, glob::win,
		      ExposureMask |
		      PointerMotionMask |
		      KeyPressMask |
		      ButtonPressMask |
		      ButtonReleaseMask |
		      ButtonMotionMask |
		      StructureNotifyMask );
	fprintf(stderr, ">>>>addNotify 6\n");
	////////////////////////////////////////
	// Map window to display.
	////////////////////////////////////////

	XMapWindow(glob::display, glob::win);
fprintf(stderr, ">>>>addNotify 7\n");
	this->native_graphics.initGC();

	////////////////////////////////////////
	// Validate components (containers).
	////////////////////////////////////////

	// this->validate();

	////////////////////////////////////////
	// Enter application Main Event Loop.
	////////////////////////////////////////
	
	XEvent report;
	bool alive = true;
	bool first = true;

	int mouse_x;
	int mouse_y;
	Component* old_comp_under_mouse = 0;
	Component* comp_under_mouse = 0;
	Component* comp_pressed = 0;
	bool generate_click = false;

	int mouse_event_type;
	unsigned long mouse_time;
	AWTEvent* awt_event = 0;
fprintf(stderr, ">>>>addNotify 8\n");
	do
	{
		XNextEvent(glob::display, &report);
fprintf(stderr, ">>>>addNotify 9\n");
		switch ( report.type )
		{
			////////////////////////////////////////
			//
			// Expose (paint)
			//
			////////////////////////////////////////

		    case Expose:
			    this->update(&(this->native_graphics));
			    break;

			    ////////////////////////////////////////
			    //
			    // ConfigureNotify (resize)
			    //
			    ////////////////////////////////////////

		    case ConfigureNotify:
			    this->setSize(report.xconfigure.width,
					 report.xconfigure.height);
			    break;

			    ////////////////////////////////////////
			    //
			    // MotionNotify (mouse movement)
			    //
			    ////////////////////////////////////////

		    case MotionNotify:
			    mouse_x = report.xmotion.x;
			    mouse_y = report.xmotion.y;
			    mouse_time = report.xmotion.time;

			    comp_under_mouse =
				    this->getComponentAt(mouse_x, mouse_y);

			    if ( comp_under_mouse != old_comp_under_mouse )
			    {

#ifdef DEBUG_MOUSE
				    out << push
					<< "Mouse from ["
					<< old_comp_under_mouse << "] --> ["
					<< comp_under_mouse << "]." << nl
					<< pop;
#endif // DEBUG_MOUSE

				    ////////////////////////////////////////
				    // This means that the pointer has changed
				    // component locations.  The old component
				    // is old_comp_under_mouse, and the new
				    // is comp_under_mouse.
				    //
				    // Send EXITED to old.
				    ////////////////////////////////////////

				    if ( old_comp_under_mouse )
				    {
					    mouse_event_type = MouseEvent::MOUSE_EXITED;
					    awt_event =
						    new MouseEvent(comp_under_mouse,
								   mouse_event_type,
								   mouse_time,
								   0,
								   mouse_x, mouse_y,
								   0);

					    old_comp_under_mouse->dispatchEvent(awt_event);
				    }

				    ////////////////////////////////////////
				    // Send ENTERED to new.
				    ////////////////////////////////////////

				    if ( comp_under_mouse )
				    {
					    mouse_event_type = MouseEvent::MOUSE_ENTERED;
					    awt_event =
						    new MouseEvent(comp_under_mouse,
								   mouse_event_type,
								   mouse_time,
								   0,
								   mouse_x, mouse_y,
								   0);

					    comp_under_mouse->dispatchEvent(awt_event);
				    } }

			    ////////////////////////////////////////
			    // Set old_comp = comp.
			    ////////////////////////////////////////

			    old_comp_under_mouse = comp_under_mouse;
			    break;

			    ////////////////////////////////////////
			    //
			    // Button??? (mouse button press)
			    //
			    ////////////////////////////////////////

		    case ButtonPress:
		    case ButtonRelease:
			    mouse_x = report.xbutton.x;
			    mouse_y = report.xbutton.y;
			    mouse_time = report.xbutton.time;

			    comp_under_mouse =
				    this->getComponentAt(mouse_x, mouse_y);

			    switch ( report.type )
			    {
				case ButtonPress:
					mouse_event_type = MouseEvent::MOUSE_PRESSED;
					if ( !comp_pressed )
						comp_pressed = comp_under_mouse;
					break;

				case ButtonRelease:
					mouse_event_type = MouseEvent::MOUSE_RELEASED;
					break;
			    }

			    awt_event =
				    new MouseEvent(comp_pressed,
						   mouse_event_type,
						   mouse_time,
						   0,
						   mouse_x, mouse_y,
						   0);

			    comp_pressed->dispatchEvent(awt_event);

			    if ( mouse_event_type == MouseEvent::MOUSE_RELEASED )
			    {
				    ////////////////////////////////////////
				    // If PRESS & RELEASE were in the same
				    // comp, then dispatch a CLICKED event.
				    ////////////////////////////////////////

				    if ( comp_under_mouse == comp_pressed )
				    {
					    awt_event =
						    new MouseEvent(comp_pressed,
								   MouseEvent::MOUSE_CLICKED,
								   mouse_time,
								   0,
								   mouse_x, mouse_y,
								   0);

					    comp_pressed->dispatchEvent(awt_event);
				    }

				    comp_pressed = 0;
			    }

			    break;

			    ////////////////////////////////////////
			    //
			    // KeyPress (key press)
			    //
			    ////////////////////////////////////////

		    case KeyPress:
			    cout << "KeyPress event, exiting." << endl;
			    alive = false;
			    break;
		}
	} while ( alive );
fprintf(stderr, ">>>>addNotify 10\n");
	this->removeNotify();
fprintf(stderr, ">>>>addNotify 11\n");
}

Component *Frame::getParent()
{
	return 0;
}

Graphics *Frame::getGraphics()
{
	return &(this->native_graphics);
}

Dimension *Frame::getPreferredSize()
{
	return this->getSize();
}

void Frame::removeNotify()
{
	this->awt::Container::removeNotify();

	XUnmapWindow(glob::display, glob::win);
	XCloseDisplay(glob::display);

	glob::display = 0;
}	

////////////////////////////////////////
//
// PRIVATE methods
//
////////////////////////////////////////

void Frame::init()
{
	glob::display = XOpenDisplay(0);

	if ( glob::display == 0 )
	{
		cerr << "Cannot connect to X server " << XDisplayName(0) << '.' << endl;
		exit(1);
	}

	glob::screen = DefaultScreen(glob::display);
	this->display_width = DisplayWidth(glob::display, glob::screen);
	this->display_height = DisplayHeight(glob::display, glob::screen);
}


Frame *Frame::clone()
{
	return new Frame(*this);
}
