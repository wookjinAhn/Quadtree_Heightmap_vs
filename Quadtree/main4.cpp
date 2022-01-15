#include "quadtree4.h"
#include <random>

int main() {
	float WIDTH = 400;
	float HEIGHT = 400;
	int CAPACITY = 2;
	float MINSIZE = 200;
	int DEPTH = 2;
	QBoundary boundary(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);	// (x, y, w, h)
	QNode qt(boundary, DEPTH);
	std::cout << "----------------------------------------" << std::endl;

	std::ifstream fin;
	fin.open("C:\\Users\\WOOKJIN\\Desktop\\pointtest\\20.txt");

	std::vector<QPoint3D*> filePoints;
	std::string line;

	if (fin.is_open()) {
		while (!fin.eof()) {
			float x, y, z;
			QPoint3D* coordinate = new QPoint3D;
			getline(fin, line);
			std::istringstream iss(line);
			iss >> x >> y >> z;
			coordinate->SetXYZ(x, y, z);
			filePoints.push_back(coordinate);
		}
	}
	fin.close();

	for (int i = 0; i < filePoints.size(); i++) {
		std::cout << filePoints[i]->GetX() << " " << filePoints[i]->GetY() << " " << filePoints[i]->GetZ() << std::endl;
	}

	for (int i = 0; i < filePoints.size(); i++) {
		int depth = 0;
		qt.insert(filePoints[i], depth);
	}

	for (int i = 0; i < filePoints.size(); i++) {
		std::cout << "Point Path : ";
		std::cout << filePoints[i]->GetStringPath() << std::endl;
	}

	qt.findAverage(filePoints);
}