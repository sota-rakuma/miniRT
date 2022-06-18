#include "Color.hpp"

Color::Color(void) : _trgb(0) {}

// in case of little endian
Color::Color(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
    : _trgb(*(int*)(unsigned char[4]){b, g, r, t}) {}

Color::Color(const Color& another) : _trgb(another._trgb) {}

Color::~Color(void) {}

Color& Color::operator=(const Color& another) {
	_trgb = another._trgb;
	return (*this);
}

unsigned char Color::getTransparency(void) {
	return (((unsigned char*)&_trgb)[3]);
}

unsigned char Color::getRed(void) { return (((unsigned char*)&_trgb)[2]); }

unsigned char Color::getGreen(void) { return (((unsigned char*)&_trgb)[1]); }

unsigned char Color::getBlue(void) { return (((unsigned char*)&_trgb)[0]); }

void Color::setTransparency(unsigned char t) { ((unsigned char*)_trgb)[3] = t; }
void Color::setRed(unsigned char r) { ((unsigned char*)_trgb)[2] = r; }

void Color::setGreen(unsigned char g) { ((unsigned char*)_trgb)[1] = g; }

void Color::setBlue(unsigned char b) { ((unsigned char*)_trgb)[0] = b; }

void Color::addShade(double distance) {
	((unsigned char*)&_trgb)[0] = (unsigned char)(0xff * distance);
}

int Color::getOpposite(void) { return (~_trgb); }