#include "quadtree4.h"

void Quadtree::subdivide() {
	float x = parent->mBoundary.GetX();
	float y = parent->mBoundary.GetY();
	float w = parent->mBoundary.GetW();
	float h = parent->mBoundary.GetH();

	QBox b_nw(x - w / 2, y + h / 2, w / 2, h / 2);
	QBox b_ne(x + w / 2, y + h / 2, w / 2, h / 2);
	QBox b_sw(x - w / 2, y - h / 2, w / 2, h / 2);
	QBox b_se(x + w / 2, y - h / 2, w / 2, h / 2);

	nw = new Quadtree(b_nw, parent->mDepth);
	ne = new Quadtree(b_ne, parent->mDepth);
	sw = new Quadtree(b_sw, parent->mDepth);
	se = new Quadtree(b_se, parent->mDepth);

}

QPoint* Quadtree::insert(QPoint *p, int depth) {		// NW | NE		1 | 2 
	parent = this;										// ---+---	   ---+---
														// SW | SE		3 | 4

	if (parent->mDepth <= depth)
		return p;

	if (parent->mDepth > depth) {
		subdivide();
		depth++;

		if (nw->mBoundary.constains(p)) {		// NW == 1
			parent = nw;
			p->SetPath(1);
			parent->insert(p, depth);
		}
		else if (ne->mBoundary.constains(p)) {	// NE == 2
			parent = ne;
			p->SetPath(2);
			parent->insert(p, depth);
		}
		else if (sw->mBoundary.constains(p)) {	// SW == 3
			parent = sw;
			p->SetPath(3);
			parent->insert(p, depth);
		}
		else if (se->mBoundary.constains(p)) {	// SE == 4
			parent = se;
			p->SetPath(4);
			parent->insert(p, depth);
		}
	}
}
