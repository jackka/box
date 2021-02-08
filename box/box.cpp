//#include "pch.h"
#include <iostream>

class Box {
	int height{0};
	int length{0};
	int width{0};
public:
	Box() {};
	Box(int h) :				height(h), length(0), width(0) {}
	Box(int h, int l):			height(h), length(l), width(0) {}
	Box(int h, int l, int w):	height(h), length(l), width(w) {}

	Box(const Box &obj): height(obj.height), length(obj.length), width(obj.width) {}

	int getH() { return height; }
	int getL() { return length; }
	int getW() { return width; }
	void setH(int h) { height = h; }
	void setL(int l) { length = l; }
	void setW(int w) { width = w; }
	int area();
	
	~Box() { std::cout << "beep! - it's a Box destructor\n"; }
	
	Box& operator= (const Box &inBox);

	Box operator++(int);
	Box operator--(int);

	Box& operator++();
	Box& operator--(); 
};

Box& Box::operator= (const Box &inBox) {
	height = inBox.height;
	length = inBox.length;
	width = inBox.width;
	return *this;
}

Box Box::operator++(int) {
	height++;
	length++;
	width++;
	return *this;
}

Box Box::operator--(int) {
	height--;
	length--;
	width--;
	return *this;
}

Box& Box::operator++() {
	++height;
	++length;
	++width;
	return *this;
}

Box& Box::operator--() {
	--height;
	--length;
	--width;
	return *this;
}

int Box::area() {
	return height * length * width * 5 * 2;
}


int main()
{
	Box box(1, 1, 1);
	box++;
	Box box2 = box;
	Box box3;
	box3 = box2;

	//box2.setW(4);
	std::cout << box3.area() <<"\n";
}