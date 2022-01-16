#include "quadtree4.h"
#include <random>
#include <ctime>
int main() {
	//float WIDTH = 400;
	//float HEIGHT = 400;
	float WIDTH = 1;
	float HEIGHT = 1;
	int DEPTH = 5;
	QBoundary boundary(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);	// (x, y, w, h)
	QNode qt(boundary, DEPTH);
	std::cout << "----------------------------------------" << std::endl;

	std::ifstream fin;
	//fin.open("C:\\Users\\WOOKJIN\\Desktop\\pointtest\\input\\100.txt");
	fin.open("C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\stair_only_data.pcd");

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

	//for (int i = 0; i < filePoints.size(); i++) {
	//	std::cout << filePoints[i]->GetX() << " " << filePoints[i]->GetY() << " " << filePoints[i]->GetZ() << std::endl;
	//}

	clock_t start = clock();

	for (int i = 0; i < filePoints.size(); i++) {
		int depth = 0;
		qt.insert(filePoints[i], depth);
	}

	//std::cout << "-------------------------------------" << std::endl;
	//std::cout << "Points\t\t | \tEnd Node XY" << std::endl;
	//for (int i = 0; i < filePoints.size(); i++) {
	//	std::cout << filePoints[i]->GetX() << "\t" << filePoints[i]->GetY() << "\t | \t";
	//	std::cout << filePoints[i]->GetEndNodeXY().GetX() << "\t" << filePoints[i]->GetEndNodeXY().GetX() << std::endl;
	//}

	//qt.findAveragePath(filePoints);
	qt.findAverageEndXY(filePoints);

	clock_t end = clock();
	std::cout << "Run Time : " << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;
}