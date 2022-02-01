#include "quadtree1_1.h"
#include <random>

int main() {
	float MIN_X = -1;
	float MAX_X = 1;
	float Z = 2;
	int DEPTH = 6;
	QBoundary boundary((MAX_X + MIN_X) / 2, Z / 2, (MAX_X - MIN_X) / 2, Z / 2);	// (x, z, w, h)
	QNode qt(boundary, DEPTH);

	QNode QuadTree();
	QNode qtP(boundary, DEPTH);

	clock_t start;
	clock_t end;

	// ----- Read file -----
	std::cout << "Read PCD File : ";
	std::string inputPath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\stair_real_rotate.pcd";
	start = clock();

	std::vector<QPoint3D*> inputPoints = qt.readPCD(inputPath);

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- sampling -----
	std::cout << "Sampling : ";
	start = clock();

	int samplingNum = 10000;
	std::vector<QPoint3D*> samplingPoints = qt.samplingPoints(inputPoints, samplingNum);

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- Get Height -----
	std::cout << "Get Height PCD : ";
	start = clock();
	QHeightmap* heightmap = new QHeightmap();

	for (int i = 0; i < samplingPoints.size(); i++) {	//
		int depth = 0;

		qt.insert(samplingPoints[i], heightmap, depth);	//
	}
	//qt.findHeightXZ(samplingPoints);	//

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- Write file -----
	std::cout << "Write PCD File : ";
	start = clock();

	//qt.writePCD();
	heightmap->writePCD();

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;
}