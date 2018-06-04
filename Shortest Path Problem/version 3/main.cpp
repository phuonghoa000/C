#pragma warning(disable: 4996)
#include "UndirectedGraph.h"

void quickSort(int* a, int left, int right);

void quickSort(int* a, int left, int right)
{
	int i = left;
	int j = right;
	int key = a[(i + j) / 2];

	while (i <= j)
	{
		while (a[i] < key)
			i++;
		while (a[j] > key)
			j--;
		if (i <= j)
		{
			if (i < j)
				swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if (left < j)
		quickSort(a, left, j);
	if (i < right)
		quickSort(a, i, right);
}

// Hàm chính
int main(int argc, char* argv[])
{
	CGRAPH g1;
	CUndirectedGraph g2;
	int nVer;
	int ret;
	int eulerPath[MAX];
	int* a;
	int n = 0;
	
	freopen(argv[2], "rt", stdin);
	g1.readFileStreet();
	cin.clear();
	
	freopen(argv[1], "rt", stdin);
	g1.readFilePlace();
	cin.clear();
	
	freopen(argv[5], "rt", stdin);
	g1.readFileStreetToVisit(a, n);
	quickSort(a, 0, n - 1);
	cin.clear();
	
	freopen(argv[3], "rt", stdin);
	g1.readFileGPSS();
	cin.clear();

	freopen(argv[5], "rt", stdin);
	g2.createIdxPlace(a, n);
	g2.readMatrix();
	
	int start = atoi(argv[4]);
	int end = atoi(argv[6]);
	int* prev1 = NULL;
	int* prev2 = NULL;
	int u[3];

	ret = g2.runFleury(g1, eulerPath, nVer, start, end, prev1, prev2, u); // Tìm chu trình euler dùng thuật toán Fleury
	
	freopen(argv[7], "wt", stdout);
	if (ret != HAS_EULER_CYCLE)
	{
		stack<int> st1, st2;
		g1.savePath(start, u[0], prev1, st1);
		g1.writeFile(st1);
		g2.writeFile(g1, eulerPath, nVer); // Ghi kết quả tìm được vào file
		g1.savePath(u[1], end, prev2, st2);
		g1.writeFile(st2);
	}
	else
	{
		cout << "Khong tim duoc duong di" << endl;
	}
	
	delete[] a;
	a = NULL;
	delete[] prev1;
	prev1 = NULL;
	delete[] prev2;
	prev2 = NULL;
	
	return 0;
}