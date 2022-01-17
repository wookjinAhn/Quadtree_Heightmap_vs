#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class QPoint2D {
public:
	QPoint2D() : mX(0), mZ(0) {}
	QPoint2D(float x, float z) : mX(x), mZ(z) {}

	float GetX() const { return mX; }
	float GetZ() const { return mZ; }

	void SetX(float x) { this->mX = x; }
	void SetZ(float z) { this->mZ = z; }

private:
	float mX, mZ;
};

class QPoint3D {
public:
	QPoint3D() : mX(0), mY(0), mZ(0) {}
	QPoint3D(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

	float GetX() const { return mX; }
	float GetY() const { return mY; }
	float GetZ() const { return mZ; }
	std::vector<int> GetPath() const { return mPath; }
	QPoint2D GetEndNodeXZ() const { return mEndNodeXZ; }
	std::string GetStringPath() const { return mStringPath; }

	void SetX(float x) { this->mX = x; }
	void SetY(float y) { this->mY = y; }
	void SetZ(float z) { this->mZ = z; }
	void SetXYZ(float x, float y, float z) { this->mX = x; this->mY = y; this->mZ = z; }
	void SetPath(int path) { this->mPath.push_back(path); }
	void SetStringPath(std::string path) { this->mStringPath.append(path); }
	void SetEndNodeXZ(QPoint2D endNodeXZ) { this->mEndNodeXZ = endNodeXZ; }
	void SetEndNodeXZ(float x, float z) { this->mEndNodeXZ.SetX(x); this->mEndNodeXZ.SetZ(z); }

private:
	float mX, mY, mZ;
	std::vector<int> mPath;
	std::string mStringPath;
	QPoint2D mEndNodeXZ;
};

class QBoundary {
public:
	QBoundary() : mX(0), mZ(0), mW(0), mH(0) {}
	QBoundary(float x, float z, float w, float h) : mX(x), mZ(z), mW(w), mH(h) {}

	float GetX() const { return mX; }
	float GetZ() const { return mZ; }
	float GetW() const { return mW; }
	float GetH() const { return mH; }

	bool constains(QPoint3D* p);

private:
	float mX, mZ, mW, mH;
};

class QNode {
public:
	QNode(QBoundary boundary, float minsize) : mBoundary(boundary), mMinsize(minsize) {}
	QNode(QBoundary boundary, int depth) : mBoundary(boundary), mDepth(depth) {}

	QBoundary GetBoundary() const { return mBoundary; }
	float GetMin() const { return mMinsize; }
	int GetDepth() const { return mDepth; }
	std::vector<QPoint3D*> GetPoints() const { return mPoints; }
	std::map<std::string, std::pair<float, int>> GetMapString() const { return mMapString; }

	void SetMin(float minsize) { this->mMinsize = minsize; }
	void SetDepth(int depth) { this->mDepth = depth; }

	void subdivide();
	QPoint3D* insert(QPoint3D* p, int depth);

	std::vector<QPoint3D*> readPCD(std::string inputPath);
	std::vector<QPoint3D*> samplingPoints(std::vector<QPoint3D*> inputPoints, int samplingNum);
	void findHeightPath(std::vector<QPoint3D*> points);
	void findHeightXZ(std::vector<QPoint3D*> points);
	void writePCD();

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

	std::vector<QPoint3D*> mPoints;	// not use yet
	std::map<std::string, std::pair<float, int>> mMapString;
	std::map<std::pair<float, float>, std::pair<float, int>> mMapPair;
};
