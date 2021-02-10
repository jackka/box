#include <iostream>

class Body {
public:
	virtual int area() = 0;
};

class Box : Body {
	int height{ 0 };
	int length{ 0 };
	int width{ 0 };
public:
	Box() {};
	Box(int h) :				height(h), length(0), width(0) {}
	Box(int h, int l) :			height(h), length(l), width(0) {}
	Box(int h, int l, int w) :	height(h), length(l), width(w) {}

	Box(const Box &obj): height(obj.height), length(obj.length), width(obj.width) {}

	int getH() { return height; }
	int getL() { return length; }
	int getW() { return width; }
	void setH(int h) { height = h; }
	void setL(int l) { length = l; }
	void setW(int w) { width = w; }
	int area();
	
	~Box() { std::cout << "beep! another Box destructed\n"; }
	
	Box& operator= (const Box& inBox);
	friend Box operator+ (const Box& lBox, const Box& rBox );

	const Box operator++(int);
	const Box operator--(int);
	const Box operator++();
	const Box operator--();
};

class WBox : Box {
	Box *p_box;
	int w_height{ 0 };
	int w_width{ 0 };
public:
	WBox( Box *b, int w_h, int w_w) : p_box(b), w_height(w_h), w_width(w_w) {}
	int area();
};

class HBox : Box {
	Box *p_box;
	int height{ 0 };
	int length{ 0 };
	int width{ 0 };
public:
	HBox(Box *b, int self_h) : p_box(b), height(self_h)  {
		length = b->getL();
		width = b->getL();
	}
	int area();
};

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

int Box::area() {// две * 			(высоты				*	(ширина + длина))	+		  дно
	return 2 *	(	2	*			height				*	 (length + width)	+	length * width		);  // выпук. ч. = вогнутой. ч. пов. (стенка 0 толщины) => умножаем на 2.
}

int WBox::area() {
	return p_box->area() - ( w_height * w_width ) * 2; // площадь за минусом окна, что скрадывает от поверхности две своих стороны 
}

int HBox::area() { 
	return		(	2	*	(p_box->getH() + height)	*	(length + width)	+ length * width)   +   // выпук. ч. обоих коробок без внутреней замкнутой поверхности.
				(	2	*			height				*	(length + width)	+ length + width);		// вог. ч. верхней коробки
}


int main() {
	Box box(1, 1, 1); // тестим создание оъекта
	Box box0 = box++; // тестим переопределение оператора ++ 
	Box box2 = box;   // с отложенным инкрентом
	Box box3 = box0 + box2; // перегруженный +
	WBox wbox(&box3,2,3); // объект с окном
	HBox hbox(&box3,5);	  // объект коробок с различной высотой
	
	// расчёт площадей
	std::cout << box3.area() <<"\n";
	std::cout << wbox.area() <<"\n";
	std::cout << hbox.area() <<"\n"; 
}
