//
// DefaultBoundedRangeModel.cc
//
// Native Swing C++ Library -- Xwing

//


#include "defs.hh"
#include "BoundedRangeModel.hh"

#include "DefaultBoundedRangeModel.hh"



DefaultBoundedRangeModel::DefaultBoundedRangeModel()
{
}

int DefaultBoundedRangeModel::getMinimum()
{
	return this->minimum;
}

int DefaultBoundedRangeModel::getValue()
{
	return this->value;
}

int DefaultBoundedRangeModel::getExtent()
{
	return this->extent;
}

int DefaultBoundedRangeModel::getMaximum()
{
	return this->maximum;
}

bool DefaultBoundedRangeModel::getValueIsAdjusting()
{
	return this->isAdjusting;
}

////////////////////////////////////////

void DefaultBoundedRangeModel::setMinimum ( int n )
{
	this->minimum = n;
	this->fireStateChanged();
}

void DefaultBoundedRangeModel::setValue ( int n )
{
	this->value = n;
	this->fireStateChanged();
}

void DefaultBoundedRangeModel::setExtent ( int n )
{
	this->extent = n;
	this->fireStateChanged();
}

void DefaultBoundedRangeModel::setMaximum ( int n )
{
	this->maximum = n;
	this->fireStateChanged();
}

void DefaultBoundedRangeModel::setValueIsAdjusting ( bool n )
{
	this->isAdjusting = n;
	this->fireStateChanged();
}

void DefaultBoundedRangeModel::setRangeProperties ( int max,
						    int min,
						    int val,
						    int ext,
						    bool isAdj )
{
	this->maximum = max;
	this->minimum = min;
	this->value = val;
	this->extent = ext;
	this->isAdjusting = isAdj;
	this->fireStateChanged();
}

void DefaultBoundedRangeModel::addChangeListener ( ChangeListener* cl )
{
	cls->add(cl);
}

////////////////////////////////////////
//
// PROTECTED methods
//
////////////////////////////////////////

void DefaultBoundedRangeModel::fireStateChanged()
{
}


DefaultBoundedRangeModel *DefaultBoundedRangeModel::clone()
{
	return new DefaultBoundedRangeModel(*this);
}
