//
// AbstractButton.cc
//

// All rights reserved.
//


#include <awt/inc.hh>

#include <xwing/XComponent.hh>
#include "AbstractButton.hh"



AbstractButton::AbstractButton() :
    al(new PtrList<ActionListener>())
{
}


void AbstractButton::addActionListener ( ActionListener* l )
{
	this->al->add(l);
}


void AbstractButton::fireActionPerformed ( ActionEvent* e )
{
	unsigned int count = this->al->size();

	for ( int i = 0; i < count; ++i )
		this->al->getPtr(i)->actionPerformed(e);
}
