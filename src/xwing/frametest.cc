//////////////////////////////////////////////////
//
// Project homepage:
//   <github page>
//
//////////////////////////////////////////////////

#include <xwing/inc.hh>
#include <stdio.h>


class MyLabel : public XLabel, public ActionListener
{
    public:
	MyLabel() :
	    pre(new String("Number of button clicks: "))
	{
		StringBuffer *label = new StringBuffer();

		label->append(pre);
		label->append("0    ");

		this->setText(label->toString());
	}

	virtual void actionPerformed ( ActionEvent* )
	{
		StringBuffer *label = new StringBuffer();

		label->append(pre);
		label->append(new String(++counter));

		this->setText(label->toString());
	}

	////////////////////////////////////////
	// Ugliness that can be auto-generated.
	////////////////////////////////////////

	INLINE_GC_OPERATORS;
	virtual MyLabel* clone() { return new MyLabel(*this); }

    private:
	unsigned int counter;
	String *pre;
};



int main()
{
	fprintf(stderr, "main 1\n");
	XFrame* frame = new XFrame(new String("Xwing App"));
	fprintf(stderr, "main 2\n");
	XPanel* panel = new XPanel();
	XButton* swing_button = new XButton(new String("I'm an Xwing button!"));
	MyLabel* swing_label = new MyLabel();
	fprintf(stderr, "main 3\n");
	swing_button->addActionListener(swing_label);
	fprintf(stderr, "main 4\n");
	panel->setLayout(new GridLayout(2,1));
	panel->setBorder(new EmptyBorder(30,30,10,30));
	panel->add(swing_button);
	panel->add(swing_label);
	fprintf(stderr, "main 5\n");
	frame->setSize(300,110);
	fprintf(stderr, "main 6\n");
	awt::Container* c = frame->getContentPane();
	c->setLayout(new GridLayout(1,1));
	c->add(panel);
	fprintf(stderr, "main 7\n");
	frame->setVisible(true);
	fprintf(stderr, "main 8\n");

	return 0;
}
