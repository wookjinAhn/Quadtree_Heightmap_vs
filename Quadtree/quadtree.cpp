#include "quadtree.h"

bool QBoundary::constains(QPoint3D* p) {
	return (p->GetX() >= mX - mW && p->GetX() < mX + mW
		&& p->GetZ() >= mZ - mH && p->GetZ() < mZ + mH);
}

void QNode::subdivide() {
	float x = parent->mBoundary.GetX();
	float z = parent->mBoundary.GetZ();
	float w = parent->mBoundary.GetW();
	float h = parent->mBoundary.GetH();

	QBoundary b_nw(x - w / 2, z + h / 2, w / 2, h / 2);
	QBoundary b_ne(x + w / 2, z + h / 2, w / 2, h / 2);
	QBoundary b_sw(x - w / 2, z - h / 2, w / 2, h / 2);
	QBoundary b_se(x + w / 2, z - h / 2, w / 2, h / 2);

	nw = new QNode(b_nw, parent->mDepth);
	ne = new QNode(b_ne, parent->mDepth);
	sw = new QNode(b_sw, parent->mDepth);
	se = new QNode(b_se, parent->mDepth);
}

QPoint3D* QNode::insert(QPoint3D* p, int depth) {		// NW | NE		1 | 2 
	parent = this;										// ---+---	   ---+---
														// SW | SE		3 | 4
	if (parent->mDepth <= depth) {
		//mPoints.push_back(p);
		p->SetEndNodeXZ(parent->GetBoundary().GetX(), parent->GetBoundary().GetZ());
		return p;
	}

	if (parent->mDepth > depth) {
		subdivide();
		depth++;

		if (nw->mBoundary.constains(p)) {		// NW == 1
			parent = nw;
			p->SetStringPath("1");
			parent->insert(p, depth);
		}
		else if (ne->mBoundary.constains(p)) {	// NE == 2
			parent = ne;
			p->SetStringPath("2");
			parent->insert(p, depth);
		}
		else if (sw->mBoundary.constains(p)) {	// SW == 3
			parent = sw;
			p->SetStringPath("3");
			parent->insert(p, depth);
		}
		else if (se->mBoundary.constains(p)) {	// SE == 4
			parent = se;
			p->SetStringPath("4");
			parent->insert(p, depth);
		}
	}
}

std::vector<QPoint3D*> QNode::readPCD(std::string inputPath) {
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

void QNode::findHeightPath(std::vector<QPoint3D*> points) {
	for (int i = 0; i < points.size(); i++) {
		if (mMapString.find(points[i]->GetStringPath()) == mMapString.end()) {	// ���� ��
			int dividNum = 1;
			mMapString.insert({ points[i]->GetStringPath(), std::make_pair(points[i]->GetY(), dividNum) });
		}
		else {	// ���� ��.
			mMapString.find(points[i]->GetStringPath())->second.first += points[i]->GetY();
			mMapString.find(points[i]->GetStringPath())->second.second++;
		}
	}
	// print
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Key\t\t | \tZ Value" << std::endl;
	for (auto iter = mMapString.begin(); iter != mMapString.end(); ++iter) {
		std::cout << iter->first << "\t\t | \t" << iter->second.first / iter->second.second << std::endl;	// path | z
	}
}

void QNode::findHeightXZ(std::vector<QPoint3D*> points) {	// { <x, z>, <y, dividNum> }
	for (int i = 0; i < points.size(); i++) {
		if (mMapPair.find(std::make_pair(points[i]->GetEndNodeXZ().GetX(), points[i]->GetEndNodeXZ().GetZ())) == mMapPair.end()) {	// ���� ��
			int dividNum = 1;
			mMapPair.insert({ std::make_pair(points[i]->GetEndNodeXZ().GetX(), points[i]->GetEndNodeXZ().GetZ()), std::make_pair(points[i]->GetY(), dividNum) });
		}
		else {	// ���� ��.
			mMapPair.find(std::make_pair(points[i]->GetEndNodeXZ().GetX(), points[i]->GetEndNodeXZ().GetZ()))->second.first += points[i]->GetY();
			mMapPair.find(std::make_pair(points[i]->GetEndNodeXZ().GetX(), points[i]->GetEndNodeXZ().GetZ()))->second.second++;
		}
	}

	//// ��忡 10�� �̸��̸� ������
	//for (auto iter = mMapPair.begin(); iter != mMapPair.end();) {
	//	if (iter->second.second < 2) {
	//		mMapPair.erase(iter++);
	//	}
	//	else {
	//		++iter;
	//	}
	//}
}

void QNode::writePCD() {
	time_t t;
	struct tm* timeinfo;
	time(&t);
	timeinfo = localtime(&t);

	std::string hour, min;

	if (timeinfo->tm_hour < 10) hour = "0" + std::to_string(timeinfo->tm_hour);
	else hour = std::to_string(timeinfo->tm_hour);

	if (timeinfo->tm_min < 10) min = "0" + std::to_string(timeinfo->tm_min);
	else min = std::to_string(timeinfo->tm_min);

	std::string filePath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\test_output\\" + hour + min + ".pcd";

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

	for (auto iter = mMapPair.begin(); iter != mMapPair.end(); ++iter) {
		fout << iter->first.first << " " << iter->second.first / iter->second.second << " " << iter->first.second << std::endl;	// x y | z
	}

	fout.close();
}