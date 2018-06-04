#include "Graph.h"
#ifndef _UNDIRECTEDGRAPH_H
#define MAX 100
#define NON_BRIDGE -1
#define BRIDGE 0
#define DONE 1
#define NOT_DONE 0
#define HAS_EULER_PATH 0
#define HAS_EULER_CYCLE 1
#define NOT_HAS_EULER_PATH -1
#pragma once

class CUndirectedGraph
{
private:
	int* idxPlace; // Danh sách chỉ số các địa điểm
	int nV; //số đỉnh của đồ thị
	int** adjencyMatrix; //ma trận trọng số
public:
	// Hàm khởi tạo ma trận rỗng
	CUndirectedGraph();
	// Hàm khởi tạo đồ thị từ ma trận trọng số
	CUndirectedGraph(int n, int** A);
	// Hàm tạo mảng chỉ số các địa điểm
	void createIdxPlace(int* a, int n);
	// Hàm xác định bậc của một đỉnh
	unsigned int getVertexDeg(int v);
	// Hàm thêm cạnh (i, j)
	bool addEdge(int i, int j);
	// Hàm xóa cạnh (i, j)
	bool removeEdge(int i, int j);
	// Hàm lấy cạnh (i, j)
	int getEdge(int i, int j);
	// Hàm kiểm tra cạnh (i, j) có phải là cầu hay không
	int bridgeDetection(int i, int j);
	// Hàm duyệt dfs (theo chiều sâu), có xác định cầu
	int dfsSearch(int u,int v, static int dfsNum[], static int & curNum, 
	static int num_p, static int startV);
	// Hàm tính số lượng cạnh của đồ thị
	int getNumEdge();
	// Hàm đọc ma trận từ file
	void readMatrix();
	// Hàm xuất ma trận
	void outputMatrix();
	// Hàm xuất chu trình Euler vào file
	void writeFile(CGRAPH &g, int eulerPath[], int nVer);
	// Hàm tìm chỉ số tương ứng của địa điểm
	int findIdxPlace(int idx);
	// Hàm Fleury
	int runFleury(CGRAPH &g, int eulerPath[], int &nVer, int start, int end, int* &prev1, int* &prev2, int u[]);
	// Hàm hủy
	~CUndirectedGraph();
};

#endif