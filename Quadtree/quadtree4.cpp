#include "quadtree4.h"

bool QBoundary::constains(QPoint3D* p) {
	return (p->GetX() >= mX - mW && p->GetX() < mX + mW
		&& p->GetY() >= mY - mH && p->GetY() < mY + mH);
}

void QNode::subdivide() {
	float x = parent->mBoundary.GetX();
	float y = parent->mBoundary.GetY();
	float w = parent->mBoundary.GetW();
	float h = parent->mBoundary.GetH();

	QBoundary b_nw(x - w / 2, y + h / 2, w / 2, h / 2);
	QBoundary b_ne(x + w / 2, y + h / 2, w / 2, h / 2);
	QBoundary b_sw(x - w / 2, y - h / 2, w / 2, h / 2);
	QBoundary b_se(x + w / 2, y - h / 2, w / 2, h / 2);

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
		p->SetEndNodeXY(parent->GetBoundary().GetX(), parent->GetBoundary().GetY());
		return p;
	}

	if (parent->mDepth > depth) {
		subdivide();
		depth++;

		if (nw->mBoundary.constains(p)) {		// NW == 1
			parent = nw;
			//p->SetPath(1);
			p->SetStringPath("1");
			parent->insert(p, depth);
		}
		else if (ne->mBoundary.constains(p)) {	// NE == 2
			parent = ne;
			//p->SetPath(2);
			p->SetStringPath("2");
			parent->insert(p, depth);
		}
		else if (sw->mBoundary.constains(p)) {	// SW == 3
			parent = sw;
			//p->SetPath(3);
			p->SetStringPath("3");
			parent->insert(p, depth);
		}
		else if (se->mBoundary.constains(p)) {	// SE == 4
			parent = se;
			//p->SetPath(4);
			p->SetStringPath("4");
			parent->insert(p, depth);
		}
	}
}

void QNode::findAveragePath(std::vector<QPoint3D*> points) {
	for (int i = 0; i < points.size(); i++) {
		if (mMapString.find(points[i]->GetStringPath()) == mMapString.end()) {	// 없을 때
			int dividNum = 1;
			mMapString.insert({ points[i]->GetStringPath(), std::make_pair(points[i]->GetZ(), dividNum) });
		}
		else {	// 있을 때.
			mMapString.find(points[i]->GetStringPath())->second.first += points[i]->GetZ();
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

void QNode::findAverageEndXY(std::vector<QPoint3D*> points) {
	for (int i = 0; i < points.size(); i++) {
		if (mMapPair.find(std::make_pair(points[i]->GetEndNodeXY().GetX(), points[i]->GetEndNodeXY().GetY())) == mMapPair.end()) {	// 없을 때
			int dividNum = 1;
			mMapPair.insert({ std::make_pair(points[i]->GetEndNodeXY().GetX(), points[i]->GetEndNodeXY().GetY()), std::make_pair(points[i]->GetZ(), dividNum) });
		}
		else {	// 있을 때.
			mMapPair.find(std::make_pair(points[i]->GetEndNodeXY().GetX(), points[i]->GetEndNodeXY().GetY()))->second.first += points[i]->GetZ();
			mMapPair.find(std::make_pair(points[i]->GetEndNodeXY().GetX(), points[i]->GetEndNodeXY().GetY()))->second.second++;
		}
	}
	// print 
	//std::cout << "-------------------------------------" << std::endl;
	//std::cout << "Key\t\t | \tZ Value" << std::endl;
	//for (auto iter = mMapPair.begin(); iter != mMapPair.end(); ++iter) {
	//	std::cout << iter->first.first << "\t" << iter->first.second << "\t | \t" << iter->second.first / iter->second.second << std::endl;	// x y | z
	//}
	QNode::makeHeightMap();
}

void QNode::makeHeightMap() {
	std::ofstream fout;
	fout.open("C:\\Users\\WOOKJIN\\Desktop\\pointtest\\output\\test.pcd");
	
	for (auto iter = mMapPair.begin(); iter != mMapPair.end(); ++iter) {
		fout << iter->first.first << " " << iter->first.second << " " << iter->second.first / iter->second.second << std::endl;	// x y | z
	}

	fout.close();
}