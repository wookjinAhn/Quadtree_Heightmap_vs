#include "quadtree.h"


void Quadtree::subdivide() {
	float x = parent->boundary.GetX();
	float y = parent->boundary.GetY();
	float w = parent->boundary.GetW();
	float h = parent->boundary.GetH();

	center = std::make_pair(x, y);

	QBox b_nw(x - w / 2, y + h / 2, w / 2, h / 2);
	QBox b_ne(x + w / 2, y + h / 2, w / 2, h / 2);
	QBox b_sw(x - w / 2, y - h / 2, w / 2, h / 2);
	QBox b_se(x + w / 2, y - h / 2, w / 2, h / 2);
	
	nw = new Quadtree(b_nw, parent->minsize);
	ne = new Quadtree(b_ne, parent->minsize);
	sw = new Quadtree(b_sw, parent->minsize);
	se = new Quadtree(b_se, parent->minsize);
}

void Quadtree::insert(QPoint p) {
	parent = this;
	if (parent->boundary.GetW() >= (parent->minsize) / 2) {
		subdivide();
		//std::cout << "--- start ---" << std::endl;
		//std::cout << "this   : " << this << " | " << this->boundary.GetX() << ", " << this->boundary.GetY() << ", " << this->boundary.GetH() << std::endl;
		//std::cout << "parent : " << parent << " | " << parent->boundary.GetX() << ", " << parent->boundary.GetY() << ", " << parent->boundary.GetH() << std::endl;
		//std::cout << "nw     : " << nw << " | " << nw->boundary.GetX() << ", " << nw->boundary.GetY() << ", " << nw->boundary.GetH() << std::endl;
		//std::cout << "ne     : " << ne << " | " << ne->boundary.GetX() << ", " << ne->boundary.GetY() << ", " << ne->boundary.GetH() << std::endl;
		//std::cout << "sw     : " << sw << " | " << sw->boundary.GetX() << ", " << sw->boundary.GetY() << ", " << sw->boundary.GetH() << std::endl;
		//std::cout << "se     : " << se << " | " << se->boundary.GetX() << ", " << se->boundary.GetY() << ", " << se->boundary.GetH() << std::endl;

		if (nw->boundary.constains(p)) {
			parent = nw;
			//std::cout << "parent : " << parent << " | " << parent->boundary.GetX() << ", " << parent->boundary.GetY() << ", " << parent->boundary.GetH() << std::endl;
			//std::cout << "this   : " << this << " | " << this->boundary.GetX() << ", " << this->boundary.GetY() << ", " << this->boundary.GetH() << std::endl;
			//std::cout << "insert ! " << std::endl;
			parent->insert(p);
		}
		else if (ne->boundary.constains(p)) {
			parent = ne;
			//std::cout << "parent : " << parent << " | " << parent->boundary.GetX() << ", " << parent->boundary.GetY() << ", " << parent->boundary.GetH() << std::endl;
			//std::cout << "this   : " << this << " | " << this->boundary.GetX() << ", " << this->boundary.GetY() << ", " << this->boundary.GetH() << std::endl;
			//std::cout << "insert ! " << std::endl;
			parent->insert(p);
		}
		else if (sw->boundary.constains(p)) {
			parent = sw;
			//std::cout << "parent : " << parent << " | " << parent->boundary.GetX() << ", " << parent->boundary.GetY() << ", " << parent->boundary.GetH() << std::endl;
			//std::cout << "this   : " << this << " | " << this->boundary.GetX() << ", " << this->boundary.GetY() << ", " << this->boundary.GetH() << std::endl;
			//std::cout << "insert ! " << std::endl;
			parent->insert(p);
		}
		else if (se->boundary.constains(p)) {
			parent = se;
			//std::cout << "parent : " << parent << " | " << parent->boundary.GetX() << ", " << parent->boundary.GetY() << ", " << parent->boundary.GetH() << std::endl;
			//std::cout << "this   : " << this << " | " << this->boundary.GetX() << ", " << this->boundary.GetY() << ", " << this->boundary.GetH() << std::endl;
			//std::cout << "insert ! " << std::endl;
			parent->insert(p);
		}
		//std::cout << "--- end ---" << std::endl;
	}
}
