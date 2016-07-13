//
// XFrame.cc
//

// All rights reserved.
//


#include <xwing/defs.hh>
#include <xwing/XComponent.hh>
#include <xwing/XPanel.hh>
#include "XFrame.hh"


XFrame::XFrame() {
	}

XFrame::XFrame ( String* title ) : Frame(title->clone()) {
	}

XFrame::XFrame ( String& title ) : Frame(title.clone()) {
	}

awt::Container*
XFrame::getContentPane() {
	return &(this->content_pane);
	}

Component*
XFrame::getComponentAt ( int x, int y ) {
	return this->content_pane.getComponentAt(x,y);
	}

void
XFrame::setBorder ( Border* border ) {
	this->Component::setBorder(border);
	this->content_pane.setBorder(border);
	}

void
XFrame::setSize ( unsigned int width, unsigned int height ) {
	this->Component::setSize(width, height);
	this->content_pane.setSize(width, height);
	}

void
XFrame::setVisible ( bool val ) {
	if ( val == true )
		this->addNotify();
	else
		this->removeNotify();
	}

void
XFrame::paint ( Graphics* g ) {
	this->content_pane.paint(g);
	}

void
XFrame::paintAll ( Graphics* g ) {
	this->content_pane.paintAll(g);
	}

void
XFrame::paintComponents ( Graphics* g ) {
	this->content_pane.paintComponents(g);
	}

void
XFrame::update ( Graphics* g ) {
	this->content_pane.update(g);
	}


XFrame*
XFrame::clone() {
	return new XFrame(*this);
	}
