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
		mPoints.push_back(p);
		return p;
	}

	if (parent->mDepth > depth) {
		subdivide();
		depth++;

		if (nw->mBoundary.constains(p)) {		// NW == 1
			parent = nw;
			p->SetPath(1);
			p->SetStringPath("1");
			p->SetEndNodeXY(nw->GetBoundary().GetX(), nw->GetBoundary().GetY());
			parent->insert(p, depth);
		}
		else if (ne->mBoundary.constains(p)) {	// NE == 2
			parent = ne;
			p->SetPath(2);
			p->SetStringPath("2");
			p->SetEndNodeXY(ne->GetBoundary().GetX(), ne->GetBoundary().GetY());
			parent->insert(p, depth);
		}
		else if (sw->mBoundary.constains(p)) {	// SW == 3
			parent = sw;
			p->SetPath(3);
			p->SetStringPath("3");
			p->SetEndNodeXY(sw->GetBoundary().GetX(), sw->GetBoundary().GetY());
			parent->insert(p, depth);
		}
		else if (se->mBoundary.constains(p)) {	// SE == 4
			parent = se;
			p->SetPath(4);
			p->SetStringPath("4");
			p->SetEndNodeXY(se->GetBoundary().GetX(), se->GetBoundary().GetY());
			parent->insert(p, depth);
		}
	}
}

void QNode::findAverage(std::vector<QPoint3D*> points) {
	for (int i = 0; i < points.size(); i++) {
		if (mMap.find(points[i]->GetStringPath()) == mMap.end()) {	// 없을 때
			int dividNum = 1;
			mMap.insert({points[i]->GetStringPath(), std::make_pair(points[i]->GetZ(), dividNum) });
		}
		else {	// 있을 때.
			mMap.find(points[i]->GetStringPath())->second.first += points[i]->GetZ();
			mMap.find(points[i]->GetStringPath())->second.second++;
		}
	}

	for (auto iter = mMap.begin(); iter != mMap.end(); ++iter) {
		std::cout << "key : " << iter->first << " value : " << iter->second.first / iter->second.second << std::endl;
	}
}
