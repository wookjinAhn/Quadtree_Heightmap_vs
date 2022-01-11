#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

struct QPoint {
private:
	float x, y;

public:
	QPoint() : x(0), y(0) {}
	QPoint(float _x, float _y) : x(_x), y(_y) {}

	float GetX() const { return x; }
	float GetY() const { return y; }
};

class QBox {
private:
	float x, y, w, h;

public:
	QBox() : x(0), y(0), w(0), h(0) {}
	QBox(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) {}

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetW() const { return w; }
	float GetH() const { return h; }

	bool constains(QPoint p) {
		return (p.GetX() >= x - w && p.GetX() < x + w
			&& p.GetY() >= y - h && p.GetY() < y + h);
	}
};

class Quadtree {	// boudnary, cap, 
private :
	QBox boundary;
	int cap = 0;
	bool divided = false;
	float minsize = 0;

	Quadtree* parent = this;
	Quadtree* nw = nullptr;
	Quadtree* ne = nullptr;
	Quadtree* sw = nullptr;
	Quadtree* se = nullptr;
	

public:
	Quadtree(Box _boundary, int _cap) : boundary(_boundary), cap(_cap) {}
	Quadtree(Box _boundary, float _minsize) : boundary(_boundary), minsize(_minsize) {}

	QBox GetBoundary() const { return boundary; }
	float GetMin() const { return minsize; }

	void SetMin(float min) { this->minsize = min; }

	void subdivide();
	void insert(Point p);

	std::pair<float, float> center;	// (x, y)
	std::vector<float> h;			// (x, y) boundary 내 점들의 height
	std::vector<std::pair<float, float>, std::vector<float>> map;	// (x, y), h
};