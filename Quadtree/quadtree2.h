#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

struct QPoint {	// z -> ≥Ù¿Ã!
private:
	float x, y, z;
	std::vector<int> path;

public:
	QPoint() : x(0), y(0), z(0) {}
	QPoint(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }
	std::vector<int> GetPath() const { return path; }

	void SetPath(int path) { this->path.push_back(path); }
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
private:
	QBox boundary;
	int cap = 0;
	bool divided = false;
	float minsize = 0;
	int depth = 0;
	int dcheck = 0;
	Quadtree* parent = this;
	Quadtree* nw = nullptr;
	Quadtree* ne = nullptr;
	Quadtree* sw = nullptr;
	Quadtree* se = nullptr;


public:
	//Quadtree(Box _boundary, int _cap) : boundary(_boundary), cap(_cap) {}
	Quadtree(QBox _boundary, float _minsize) : boundary(_boundary), minsize(_minsize) {}
	Quadtree(QBox _boundary, int _depth) : boundary(_boundary), depth(_depth) {}

	QBox GetBoundary() const { return boundary; }
	float GetMin() const { return minsize; }
	int GetDepth() const { return depth; }

	void SetMin(float min) { this->minsize = min; }
	void SetDepth(int depth) { this->depth = depth; }

	void subdivide();
	void insert(QPoint p, int depth);
};