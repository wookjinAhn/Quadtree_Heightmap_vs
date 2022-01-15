#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

class QPoint2D {
private:
	float mX, mY;

public:
	QPoint2D() : mX(0), mY(0) {}
	QPoint2D(float x, float y) : mX(x), mY(y) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }

	void SetX(float x) { this->mX = x; }
	void SetY(float y) { this->mY = y; }
};

class QPoint3D {	// z -> ≥Ù¿Ã!
private:
	float mX, mY, mZ;
	std::vector<int> mPath;
	std::string mStringPath;
	QPoint2D mEndNodeXY;

public:
	QPoint3D() : mX(0), mY(0), mZ(0) {}
	QPoint3D(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
	
	// Getter
	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetZ() const { return mZ; }
	std::vector<int> GetPath() const { return mPath; }
	QPoint2D GetEndNodeXY() const { return mEndNodeXY; }
	std::string GetStringPath() const { return mStringPath; }
	// Setter
	void SetX(float x) { this->mX = x; }
	void SetY(float y) { this->mY = y; }
	void SetZ(float z) { this->mZ = z; }	
	void SetXYZ(float x, float y, float z) {
		this->mX = x;
		this->mY = y;
		this->mZ = z;
	}
	void SetPath(int path) { this->mPath.push_back(path); }
	void SetStringPath(std::string path) { this->mStringPath.append(path); }
	void SetEndNodeXY(QPoint2D endNodeXY) { this->mEndNodeXY = endNodeXY; }
	void SetEndNodeXY(float x, float y) { 
		this->mEndNodeXY.SetX(x);
		this->mEndNodeXY.SetY(y);
	}
};

class QBoundary {
private:
	float mX, mY, mW, mH;

public:
	QBoundary() : mX(0), mY(0), mW(0), mH(0) {}
	QBoundary(float x, float y, float w, float h) : mX(x), mY(y), mW(w), mH(h) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetW() const { return mW; }
	float GetH() const { return mH; }

	bool constains(QPoint3D* p);
};

class QNode {	// boudnary, cap, 
private:
	QBoundary mBoundary;
	bool divided = false;
	float mMinsize = 0;
	int mDepth = 0;

	QNode* parent = this;
	QNode* nw = nullptr;
	QNode* ne = nullptr;
	QNode* sw = nullptr;
	QNode* se = nullptr;

	std::vector<QPoint3D*> mPoints;
	std::map<std::string, std::pair<float, int>> mMap;

public:
	QNode(QBoundary boundary, float minsize) : mBoundary(boundary), mMinsize(minsize) {}
	QNode(QBoundary boundary, int depth) : mBoundary(boundary), mDepth(depth) {}

	// Getter
	QBoundary GetBoundary() const { return mBoundary; }
	float GetMin() const { return mMinsize; }
	int GetDepth() const { return mDepth; }
	std::vector<QPoint3D*> GetPoints() const { return mPoints; }
	std::map<std::string, std::pair<float, int>> GetMap() const { return mMap; }
	// Setter
	void SetMin(float minsize) { this->mMinsize = minsize; }
	void SetDepth(int depth) { this->mDepth = depth; }

	void subdivide();
	QPoint3D* insert(QPoint3D* p, int depth);
	void findAverage(std::vector<QPoint3D*> points);
};
