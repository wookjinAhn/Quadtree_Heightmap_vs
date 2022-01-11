#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

struct QPoint {	// z -> ≥Ù¿Ã!
private:
	float mX, mY, mZ;
	std::vector<int> path;

public:
	QPoint() : mX(0), mY(0), mZ(0) {}
	QPoint(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetZ() const { return mZ; }
	std::vector<int> GetPath() const { return path; }

	void SetPath(int path) { this->path.push_back(path); }
};

class QBox {
private:
	float mX, mY, mW, mH;

public:
	QBox() : mX(0), mY(0), mW(0), mH(0) {}
	QBox(float x, float y, float w, float h) : mX(x), mY(y), mW(w), mH(h) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetW() const { return mW; }
	float GetH() const { return mH; }

	bool constains(QPoint *p) {
		return (p->GetX() >= mX - mW && p->GetX() < mX + mW
			&& p->GetY() >= mY - mH && p->GetY() < mY + mH);
	}
};

class Quadtree {	// boudnary, cap, 
private:
	QBox mBoundary;
	int cap = 0;
	bool divided = false;
	float mMinsize = 0;
	int mDepth = 0;
	int check = 0;
	Quadtree* parent = this;
	Quadtree* nw = nullptr;
	Quadtree* ne = nullptr;
	Quadtree* sw = nullptr;
	Quadtree* se = nullptr;

public:
	//Quadtree(Box _boundary, int _cap) : boundary(_boundary), cap(_cap) {}
	Quadtree(QBox boundary, float minsize) : mBoundary(boundary), mMinsize(minsize) {}
	Quadtree(QBox boundary, int depth) : mBoundary(boundary), mDepth(depth) {}

	QBox GetBoundary() const { return mBoundary; }
	float GetMin() const { return mMinsize; }
	int GetDepth() const { return mDepth; }

	void SetMin(float minsize) { this->mMinsize = minsize; }
	void SetDepth(int depth) { this->mDepth = depth; }

	void subdivide();
	QPoint* insert(QPoint *p, int depth);
};