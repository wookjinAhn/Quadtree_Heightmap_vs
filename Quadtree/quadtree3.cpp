#include "quadtree4.h"

void Quadtree::subdivide() {
	float x = parent->boundary.GetX();
	float y = parent->boundary.GetY();
	float w = parent->boundary.GetW();
	float h = parent->boundary.GetH();

	QBox b_nw(x - w / 2, y + h / 2, w / 2, h / 2);
	QBox b_ne(x + w / 2, y + h / 2, w / 2, h / 2);
	QBox b_sw(x - w / 2, y - h / 2, w / 2, h / 2);
	QBox b_se(x + w / 2, y - h / 2, w / 2, h / 2);

	nw = new Quadtree(b_nw, parent->depth);
	ne = new Quadtree(b_ne, parent->depth);
	sw = new Quadtree(b_sw, parent->depth);
	se = new Quadtree(b_se, parent->depth);

}

void Quadtree::insert(QPoint p, int depth) {		// NW | NE		1 | 2 
	parent = this;								// ---+---	   ---+---
												// SW | SE		3 | 4
	if (parent->depth <= depth)
		return;

	if (parent->depth > depth) {
		subdivide();
		depth++;

		if (nw->boundary.constains(p)) {		// NW == 1
			parent = nw;
			p.SetPath(1);
			parent->insert(p, depth); 
		}
		else if (ne->boundary.constains(p)) {	// NE == 2
			parent = ne;
			p.SetPath(2);
			parent->insert(p, depth);
		}
		else if (sw->boundary.constains(p)) {	// SW == 3
			parent = sw;
			p.SetPath(3);
			parent->insert(p, depth);
		}
		else if (se->boundary.constains(p)) {	// SE == 4
			parent = se;
			p.SetPath(4);
			parent->insert(p, depth);
		}
	}
}
