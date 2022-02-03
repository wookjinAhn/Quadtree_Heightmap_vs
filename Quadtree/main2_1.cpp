#include "quadtree2_1.h"

int main() {
	float MIN_X = -1;
	float MAX_X = 1;
	float Z = 2;
	int DEPTH = 6;
	int CAPACITY = 1;
	//QBoundary boundary((MAX_X + MIN_X) / 2, Z / 2, (MAX_X - MIN_X) / 2, Z / 2);	// (x, z, w, h)
	QBoundary boundary(MAX_X, MIN_X, Z);
	QNode qt(boundary, DEPTH, CAPACITY);
	QHeightmap* heightmap = new QHeightmap();

	clock_t start;
	clock_t end;

	// ----- Read PCD file -----
	std::cout << "Read PCD File : ";

	std::string inputPath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\stair_real_rotate.pcd";
	start = clock();

	std::vector<QPoint3D*> inputPoints = qt.readPCDToVector(inputPath);

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- sampling -----
	std::cout << "Sampling : ";
	start = clock();

	std::vector<QPoint3D*> samplingPoints = qt.samplingPoints(inputPoints, 5000);

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- Get Height -----
	std::cout << "Get Height PCD : ";

	start = clock();

	for (int i = 0; i < samplingPoints.size(); i++) {	//
		int depth = 0;

		qt.insert(samplingPoints[i], heightmap, depth);	//
	}

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- Write PCD file -----
	std::cout << "Write PCD File : ";

	std::string outputPath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\test_output\\";
	start = clock();

	heightmap->writeMapToPCD(outputPath);

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;
}