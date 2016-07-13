//
// XScrollBar.cc
//
// Native Swing C++ Library -- Xwing

//


#include <xwing/defs.hh>
#include <xwing/BoundedRangeModel.hh>
#include <xwing/DefaultBoundedRangeModel.hh>
#include <xwing/Adjustable.hh>
#include <xwing/XComponent.hh>
#include <xwing/XScrollBar.hh>



XScrollBar::XScrollBar() : model(new DefaultBoundedRangeModel()) {
	}

int
XScrollBar::getBlockIncrement() {
	return this->blockIncrement;
	}

int
XScrollBar::getMaximum() {
	return this->model->getMaximum();
	}

int
XScrollBar::getMinimum() {
	return this->model->getMinimum();
	}

int
XScrollBar::getOrientation() {
	return this->orientation;
	}

int
XScrollBar::getUnitIncrement() {
	return this->unitIncrement;
	}

int
XScrollBar::getValue() {
	return this->model->getValue();
	}

int
XScrollBar::getVisibleAmount() {
	return this->visibleAmount;
	}

void
XScrollBar::setBlockIncrement ( int n ) {
	this->blockIncrement = n;
	}

void
XScrollBar::setMaximum ( int n ) {
	this->model->setMaximum(n);
	}

void
XScrollBar::setMinimum ( int n ) {
	this->model->setMinimum(n);
	}

void
XScrollBar::setOrientation ( int n ) {
	this->orientation = n;
	}

void
XScrollBar::setUnitIncrement ( int n ) {
	this->unitIncrement = n;
	}

void
XScrollBar::setValue ( int n ) {
	this->model->setValue(n);
	}

void
XScrollBar::setVisibleAmount ( int n ) {
	this->visibleAmount = n;
	}

void
XScrollBar::paint ( Graphics* g ) {
	
	}


XScrollBar*
XScrollBar::clone()
{
	return new XScrollBar(*this);
}
