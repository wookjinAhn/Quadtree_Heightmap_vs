#include "quadtree2.h"
#include <random>

int main() {
	//srand(time(NULL));
	std::random_device rng;
	std::uniform_real_distribution<double> range(0.0, 400.0);

	int WIDTH = 400;
	int HEIGHT = 400;
	int CAPACITY = 2;
	float MINSIZE = 200;
	QBox boundary(200, 200, 200, 200);
	//Quadtree qt(boundary, CAPACITY);
	//qt.SetMin(10);
	Quadtree qt(boundary, MINSIZE);

	//std::cout << boundary.GetX() << std::endl;
	//std::cout << qt.GetBoundary().GetX() << std::endl;
	std::cout << qt.GetMin() << std::endl;

	for (int i = 0; i < 3; i++) {
		//float x = range(rng);
		//float y = range(rng);
		//Point p(x, y);
		//std::cout << "point input | x : " << x << ", y : " << y << std::endl;
		float x = rand() % 400;
		float y = rand() % 400;
		float z = rand() % 400;		// z = height
		QPoint p(x, y, z);			
		std::cout << "point input | x : " << x << ", y : " << y << ", z : " << z << std::endl;
		qt.insert(p);
	}

	//std::pair<float, float> center;
	//std::vector<float> z;
	//std::vector<std::pair<std::pair<float, float>, std::vector<float>>> map;

	//float x = 1;
	//float y = 3;
	////float z = 8;
	//center = std::make_pair(x, y);
	//map.push_back({ center, z });


}

