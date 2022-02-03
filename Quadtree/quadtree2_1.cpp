#include "quadtree2_1.h"

void QNode::subdivide() {
	float x = mParent->mBoundary.GetX();
	float z = mParent->mBoundary.GetZ();
	float w = mParent->mBoundary.GetW();
	float h = mParent->mBoundary.GetH();

	QBoundary nw(x - w / 2, z + h / 2, w / 2, h / 2);
	QBoundary ne(x + w / 2, z + h / 2, w / 2, h / 2);
	QBoundary sw(x - w / 2, z - h / 2, w / 2, h / 2);
	QBoundary se(x + w / 2, z - h / 2, w / 2, h / 2);

	mNW = new QNode(nw, mDepth, mCapacity);
	mNE = new QNode(ne, mDepth, mCapacity);
	mSW = new QNode(sw, mDepth, mCapacity);
	mSE = new QNode(se, mDepth, mCapacity);

	mDivided = true;
}

void QNode::insert(QPoint3D* point, QHeightmap* heightmap, int depth) {		// NW | NE		1 | 2 
	mPoints.push(point);									// SW | SE		3 | 4

	if (mDepth == depth) {
		heightmap->makeHeightMap(point);
		return;
	}

	if (mCapacity < mPoints.size() && mDepth > depth) {
		subdivide();
	}

	if (mDivided) {
		while (!mPoints.empty()) {
			QPoint3D* qPoint = mPoints.front();
			mPoints.pop();
			if (mNW->mBoundary.constains(qPoint)) {		// NW == 1
				mParent = mNW;
				qPoint->SetEndNodeXZ(mParent->GetBoundary().GetX(), mParent->GetBoundary().GetZ());
				mParent->insert(qPoint, heightmap, ++depth);
			}
			else if (mNE->mBoundary.constains(qPoint)) {	// NE == 2
				mParent = mNE;
				qPoint->SetEndNodeXZ(mParent->GetBoundary().GetX(), mParent->GetBoundary().GetZ());
				mParent->insert(qPoint, heightmap, ++depth);
			}
			else if (mSW->mBoundary.constains(qPoint)) {	// SW == 3
				mParent = mSW;
				qPoint->SetEndNodeXZ(mParent->GetBoundary().GetX(), mParent->GetBoundary().GetZ());
				mParent->insert(qPoint, heightmap, ++depth);
			}
			else if (mSE->mBoundary.constains(qPoint)) {	// SE == 4
				mParent = mSE;
				qPoint->SetEndNodeXZ(mParent->GetBoundary().GetX(), mParent->GetBoundary().GetZ());
				mParent->insert(qPoint, heightmap, ++depth);
			}
		}
	}
}

std::vector<QPoint3D*> QNode::readPCDToVector(std::string inputPath) {
	std::ifstream fin;
	fin.open(inputPath);

	std::vector<QPoint3D*> inputPoints;
	std::string line;

	if (fin.is_open()) {
		int num = 1;
		while (!fin.eof()) {
			getline(fin, line);
			if (num > 10) {
				float x, y, z;
				QPoint3D* pointXYZ = new QPoint3D;
				std::istringstream iss(line);
				iss >> x >> y >> z;
				pointXYZ->SetXYZ(x, y, z);
				inputPoints.push_back(pointXYZ);
			}
			num++;
		}
	}
	fin.close();
	return inputPoints;
}

std::vector<QPoint3D*> QNode::samplingPoints(std::vector<QPoint3D*> inputPoints, int samplingNum) {
	std::vector<QPoint3D*> samplingPoints;

	std::random_device random;
	std::uniform_int_distribution<int> range(0, inputPoints.size() - 1);

	for (int i = 0; i < samplingNum; i++) {
		int randomIndex = range(random);
		samplingPoints.push_back(inputPoints[randomIndex]);
	}
	return samplingPoints;
}

// ----- Heightmap -----

void QHeightmap::makeHeightMap(QPoint3D* points) {	// { <x, z>, <y, dividNum> }
	if (mMapPair.find(std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ())) == mMapPair.end()) {	// exist
		int dividNum = 1;

		mMapPair.insert({ std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ()), std::make_pair(points->GetY(), dividNum) });
	}
	else {	// not exist
		mMapPair.find(std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ()))->second.first += points->GetY();
		mMapPair.find(std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ()))->second.second++;
	}
}

void QHeightmap::writeMapToPCD(std::string outputPath) {
	time_t t;
	struct tm* timeinfo;
	time(&t);
	timeinfo = localtime(&t);

	std::string hour, min;

	if (timeinfo->tm_hour < 10) hour = "0" + std::to_string(timeinfo->tm_hour);
	else hour = std::to_string(timeinfo->tm_hour);

	if (timeinfo->tm_min < 10) min = "0" + std::to_string(timeinfo->tm_min);
	else min = std::to_string(timeinfo->tm_min);

	std::string filePath = outputPath + hour + min + ".pcd";

	std::ofstream fout;
	fout.open(filePath);

	fout << "VERSION" << std::endl;
	fout << "FIELDS x y z" << std::endl;
	fout << "SIZE 4 4 4" << std::endl;
	fout << "TYPE F F F" << std::endl;
	fout << "COUNT 1 1 1" << std::endl;
	fout << "WIDTH 1" << std::endl;
	fout << "HEIGHT " << mMapPair.size() << std::endl;
	fout << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
	fout << "POINTS " << mMapPair.size() << std::endl;
	fout << "DATA ascii" << std::endl;

	std::cout << mMapPair.size() << std::endl;
	for (auto iter = mMapPair.begin(); iter != mMapPair.end(); ++iter) {
		fout << iter->first.first << " " << iter->second.first / iter->second.second << " " << iter->first.second << std::endl;	// x y | z
	}

	fout.close();
}