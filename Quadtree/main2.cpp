#include "quadtree2.h"

int main() {
	float MIN_X = -1;
	float MAX_X = 1;
	float Z = 2;
	int DEPTH = 6;
	int CAPACITY = 20;
	QBoundary boundary((MAX_X + MIN_X) / 2, Z / 2, (MAX_X - MIN_X) / 2, Z / 2);	// (x, z, w, h)
	QNode qt(boundary, DEPTH, CAPACITY);

	clock_t start;
	clock_t end;

	// ----- Read PCD file -----
	std::cout << "Read PCD File : ";

	//std::string inputPath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\real_data\\143826.pcd";
	//std::string inputPath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\test_output\\1920.pcd";	// rotation file
	std::string inputPath = "C:\\Users\\WOOKJIN\\Desktop\\testPCD_khnp\\stair_real_rotate.pcd";
	start = clock();

	std::vector<QPoint3D*> inputPoints = qt.readPCD(inputPath);

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
	
	QHeightmap* heightmap = new QHeightmap();
	start = clock();

	for (int i = 0; i < samplingPoints.size(); i++) {	//
		int depth = 0;

		qt.insert(samplingPoints[i], heightmap, depth);	//
	}
	//qt.findHeightXZ(samplingPoints);	//

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	//// ----- Write PCD file -----
	//std::cout << "Write PCD File : ";
	//start = clock();

	//qt.writePCD();

	//end = clock();
	//std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

	// ----- Write XYZ file -----
	std::cout << "Write PCD File : ";
	start = clock();

	heightmap->writeXYZ();

	end = clock();
	std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

}