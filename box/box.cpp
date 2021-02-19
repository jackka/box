#include <iostream>

class Body {
public:
	virtual int area() const = 0;
};
//=============   ����� ������� 
class Box : public Body {
	int height{ 0 };
	int length{ 0 };
	int width{ 0 };
public:
	Box() {};
	Box(int h) :				height(h), length(0), width(0) {}
	Box(int h, int l) :			height(h), length(l), width(0) {}
	Box(int h, int l, int w) :	height(h), length(l), width(w) {}

	Box(const Box &obj): height(obj.height), length(obj.length), width(obj.width) {}

	int getH() const { return height; }
	int getL() const { return length; }
	int getW() const { return width; }
	
	void setH(int h) { 
		if (h < 0) throw h;
		height = h; 
	}
	
	void setL(int l) { 
		if (l < 0) throw l;
		length = l; 
	}

	void setW(int w) {
		if (w < 0) throw w;
		width = w; 
	}

	virtual int area() const;
	
	~Box() { std::cout << "~Box\n"; }
	
	Box& operator= (const Box& inBox);
	friend Box operator+ (const Box& lBox, const Box& rBox);

	const Box operator++(int);
	const Box operator--(int);
	const Box operator++();
	const Box operator--();
};

//=============   ����� � ������� 
class WBox : public virtual Box {
	int w_height{ 0 };
	int w_width{ 0 };
public:
	WBox( Box* b, int w_h, int w_w )				: Box(b->getH(), b->getL(), b->getW()),		w_height(w_h),		w_width(w_w)	{}
	~WBox() { std::cout << "~WBox\n"; }
	virtual int area() const;
};

//=============   ����� c �������� �� ������ 
class HBox : public virtual Box {
	int s_height{ 0 };
public:
	HBox( Box* b, int self_h )						: Box(b->getH(), b->getL(), b->getW()),		s_height(self_h)	{}
	~HBox() { std::cout << "~HBox\n"; }
	virtual int area() const;
};

//=============   ����� � ������� + ������� �� ������
class WHBox : public WBox, public HBox {

public:
	WHBox( Box* b, int w_h, int w_w, int self_h )	: Box(b->getH(), b->getL(), b->getW()),		WBox(b, w_h, w_w),		HBox(b, self_h)		{}
	~WHBox() { std::cout << "~WHBox\n"; }
	virtual int area() const;

};

//=============   ����� "����"
template <class T> class Stack {
	T* st;
	int top;
public:

	Stack() {
		top = 0;
		st = new T[3];
	}

	~Stack() {
		delete[] st;
		std::cout << "~Stack\n";
	}

	void push(T val) {
		if (top == 1) throw "---- stack full";	
		st[top] = val;
		top++;
	};

	int pop() {
		if (top == 0) throw "---- stack empty";
		top--;
		return st[top];
	};
};

int WHBox::area() const{
	return (HBox::area() - Box::area() + WBox::area());
}

Box& Box::operator= (const Box& inBox) {
	height = inBox.height;
	length = inBox.length;
	width = inBox.width;
	return *this;
}

Box operator+ (const Box &lBox, const Box &rBox) {
	Box res{ lBox };
	res.height += rBox.height;
	res.length += rBox.length;
	res.width += rBox.width;
	return res;
}

const Box Box::operator++(int) {
	Box temp(height, length, width);
	++height;
	++length;
	++width;
	return temp;
}

const Box Box::operator--(int) {
	Box temp(height, length, width);
	--height;
	--length;
	--width;
	return temp;
}

const Box Box::operator++() {
	++height;
	++length;
	++width;
	Box temp(height, length, width);
	return temp;
}

const Box Box::operator--() {
	--height;
	--length;
	--width;
	Box temp(height, length, width);
	return temp;
}

int Box::area() const {// ��� * 			(������				*	(������ + �����))	+		  ���
	return			2 *	(	2	*			height				*	 (length + width)	+	length * width		);  // �����. �. = ��������. �. ���. (������ 0 �������) => �������� �� 2.
}

int WBox::area() const {
	return Box::area() - ( w_height * w_width ) * 2; // ������� �� ������� ����, ��� ���������� �� ����������� ��� ����� ������� 
}

int HBox::area() const { 
	return		(	2	*	(getH() + s_height)	*	(getL() + getW())	+ getL() * getW())   +  // �����. �. ����� ������� ��� ��������� ��������� �����������.
				(	2	*		s_height		*	(getL() + getW())	+ getL() * getW());		// ���. �. ������� �������
}


//==========   Main
int main() {
	int b_height = 1, b_length = b_height, b_width = b_height, // ������� 1, 1, 1
		w_height = 3,	// ��� ����
		w_width  = 5,	// ��� ����
		s_height = 7;	// ��� 2-�� �������
	
	Box box;		// ����: ������ - ��������
	
	try {			// ���������� ��������� ����������
		box.setH(b_height);
		box.setL(b_length);
		box.setW(b_width);
	}
	catch ( int e) {
		std::cerr << "Unacceptable value \"" << e << "\" for Box\n";
		exit(-1);
	}
	
	Box box0 = box++;		// ����: ������������� ++ 
	Box box2 = box;			// � ���������� ���������
	Box box3 = box0 + box2;	// ������������� +

	WBox	wbox(&box3, w_height, w_width);			// ������ � �����
	HBox	hbox(&box3, s_height);					// ������ 2-x ������� ������ ������
	WHBox	whbox(&box3, w_height, w_width, s_height); // mix object

	// ������ ��������
	std::cout << " box3.area:\t"	<< box3.area()	<<	"\n";
	std::cout << " wbox.area:\t"	<< wbox.area()	<<	"\n";
	std::cout << " hbox.area:\t"	<< hbox.area()	<<	"\n";
	std::cout << " whbox.area:\t"	<< whbox.area()	<<	"\n";
	
	Stack <int>		ist;
	Stack <double>	dst;

	
	try {
		ist.push(1);
	//	ist.push(1);
		
		ist.pop();
		ist.pop();
	
	}
	catch (const char* e){
		std::cout << e;
		exit(-1);
	}
	

	
	dst.push(0.1);
	

}
