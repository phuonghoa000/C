# include "UndirectedGraph.h"

// Hàm khởi tạo ma trận rỗng
CUndirectedGraph::CUndirectedGraph()
{
	nV = 0;
	idxPlace = NULL;
}

// Hàm khởi tạo đồ thị từ ma trận trọng số
CUndirectedGraph::CUndirectedGraph(int n, int** A)
{
	nV = n;
	idxPlace = NULL;

	// Xin cấp phát động cho đồ thị
	adjencyMatrix = new int*[nV];
	for (int i = 0; i < nV; i++)
		adjencyMatrix[i] = new int[nV];
	// Khởi tạo đồ thị từ ma trận trọng số
	for (int i = 0; i < nV; i++)
		for (int j = 0; j < nV; j++)
			adjencyMatrix[i][j] = A[i][j];
}

// Hàm tạo mảng chỉ số các địa điểm
void CUndirectedGraph::createIdxPlace(int* a, int n)
{
	nV = n;

	idxPlace = new int[n];
	for (int i = 0; i < n; i++)
		idxPlace[i] = a[i];
}

// Hàm xác định bậc của một đỉnh
unsigned int CUndirectedGraph::getVertexDeg(int v)
{
	int count = 0;
	for (int i = 0 ; i < nV; i++)
		count = count + adjencyMatrix[v][i];
	return count;
}

// Hàm thêm cạnh (i, j)
bool CUndirectedGraph::addEdge(int i, int j)
{
	adjencyMatrix[i][j] = 1;
	return true;
}

// Hàm xóa cạnh (i, j)
bool CUndirectedGraph::removeEdge(int i, int j)
{
	adjencyMatrix[i][j] = 0;
	adjencyMatrix[j][i] = 0;
	return true;
}

// Hàm lấy cạnh (i, j)
int CUndirectedGraph::getEdge(int i, int j)
{
	return adjencyMatrix[i][j];
}

// Hàm kiểm tra cạnh (i, j) có phải là cầu hay không
int CUndirectedGraph::bridgeDetection(int i, int j)
{
	static int dfsNum[MAX]; //số thứ tự khi duyệt DFS
	static int curNum = 0;
	int ret;

	// Khởi động mảng dfsNum
	for (int k = 0; k < nV; k++)
		dfsNum[k] = -1; 

	ret = NON_BRIDGE; // Khởi tạo ret ban đầu (coi cạnh (i, j) không phải là cầu)
	dfsNum[j] = curNum;
	curNum++;

	// Khởi tạo g bằng phương thức khởi tạo truyền tham số
	CUndirectedGraph g(nV, adjencyMatrix);

	g.removeEdge(i, j); // Xóa cạnh (i, j) khỏi đồ thị g
	ret = g.dfsSearch(i, j, dfsNum, curNum, dfsNum[j], i); // Duyệt dfs có xác định cầu
	if (ret <= dfsNum[j])
		return NON_BRIDGE; 
	else
		return BRIDGE;
}

// Hàm duyệt dfs (theo chiều sâu), có xác định cầu
int CUndirectedGraph::dfsSearch(int u, int v, static int dfsNum[], 
								static int &curNum, static int num_p, static int startV)
{
	int ret = 0; 
	dfsNum[u] = curNum;
	int oldestAncestor = dfsNum[u];

	curNum++;

	for (int i = 0; i < nV; i++)
	{
		// Xóa các cạnh nối từ đỉnh u tới các đỉnh khác
		if (adjencyMatrix[u][i] != 0)
			removeEdge(u, i);

		if (dfsNum[i] == -1)
		{   
			if (u == startV)
				int t = 1;

			ret = dfsSearch(i, u, dfsNum, curNum, num_p, startV);
			if (u == startV)
				if (ret <= num_p)
					return NON_BRIDGE;   
		
			oldestAncestor = min(oldestAncestor, ret);
		}
		else
		{
			oldestAncestor = min(oldestAncestor, dfsNum[i]);
		}
	}
	return oldestAncestor;
}

// Hàm tính số lượng cạnh của đồ thị
int CUndirectedGraph::getNumEdge()
{
	int nE = 0;

	for (int i = 0; i < nV; i++)
		for (int j = i; j < nV; j++)
			nE = nE + adjencyMatrix[i][j];
	
	return nE;
}

// Hàm tìm chỉ số tương ứng với địa điểm
int CUndirectedGraph::findIdxPlace(int idx)
{
	for (int i = 0;; i++)
		if (idx == idxPlace[i])
			return i;

	return -1;
}

// Hàm đọc ma trận từ file
void CUndirectedGraph::readMatrix()
{
	char kt[5];

	// Xin cấp phát động cho đồ thị
	adjencyMatrix = new int*[nV];
	for (int i = 0; i < nV; i++)
		adjencyMatrix[i] = new int[nV];

	// Khởi gán các trọng số đều là 0
	for (int i = 0; i < nV; i++)
		for (int j = 0; j < nV; j++)
			adjencyMatrix[i][j] = 0;
	do
	{
		int be;
		int af;
		
		cin >> be;
		cin >> af;

		// Trả về chỉ số tương ứng trong ma trận của địa điểm tại chỉ số be (before) và af (after)
		be = findIdxPlace(be);
		af = findIdxPlace(af);

		// Đặt giá trị 1 tại những cạnh cần đi qua
		adjencyMatrix[af][be] = 1;
		adjencyMatrix[be][af] = 1;
	}
	while (gets(kt) != NULL);
}

// Hàm xuất ma trận
void CUndirectedGraph::outputMatrix()
{
	cout << nV << endl;
	for (int i = 0; i < nV; i++)
	{
		for (int j = 0; j < nV; j++)
			cout << adjencyMatrix[i][j] << " ";
		cout << endl;
	}
}

// Hàm xuất chu trình Euler vào file

void CUndirectedGraph::writeFile(CGRAPH &g, int eulerPath[], int nVer)
{
	// Đối sánh chỉ số của các địa điểm
	for (int i = 0; i < nVer; i++)
		eulerPath[i] = idxPlace[eulerPath[i]];

	// Xuất đường đi
	for (int i = 0; i < nVer - 1; i++)
	{
		cout << g.place[eulerPath[i]] << " --- ";
		if (g.L[eulerPath[i]][eulerPath[i + 1]].strName.length() != 0)
			cout << g.L[eulerPath[i]][eulerPath[i + 1]].strName;
		else
			cout << g.L[eulerPath[i + 1]][eulerPath[i]].strName;
		cout << " ---> " << g.place[eulerPath[i + 1]] << endl;
	}
}


// Hàm Fleury
int CUndirectedGraph::runFleury(CGRAPH &g, int eulerPath[], int &nVer, int start, int end, int* &prev1, int* &prev2, int u[])
{
	int count = 0;

	// Tìm số đỉnh bậc lẻ của đồ thị
	for (int i = 0; i < nV; i++)
	{
		if (this->getVertexDeg(i) % 2 != 0)
		{
			u[count] = i;
			count++;
		}
		// Nếu số đỉnh bậc lẻ lớn hơn 2 thì không tìm được chu trình euler
		if (count > 2)
			return NOT_HAS_EULER_PATH;
	}
	

	// Tạo g1 = g
	CUndirectedGraph g1(nV, adjencyMatrix);
	int ret;

	// Nếu đồ thị có đúng 2 đỉnh bậc lẻ
	if (count == 2)
	{
		ret = HAS_EULER_PATH; // tức có chu trình euler
		g1.addEdge(u[0], u[1]); // xóa cạnh nối bởi 2 đỉnh bậc lẻ
	}
	else
	{
		ret = HAS_EULER_CYCLE;
	}
	
	// Hai đỉnh bậc lẻ
	u[0] = idxPlace[u[0]];
	u[1] = idxPlace[u[1]];
	
	// Tìm khoảng cách từ đỉnh start tới hai đỉnh bậc lẻ
	float f1 = g.pointPlace[start].findDistance(g.pointPlace[u[0]]);
	float f2 = g.pointPlace[start].findDistance(g.pointPlace[u[1]]);

	int* T = NULL; // Mảng đánh dấu đỉnh trong T
	float* Length = NULL; // Độ dài ngắn nhất từ điểm đầu (start) tới các điểm khác
	bool check = 0;

	// Tìm đường từ start -> u[0] và u[1] tới end (nếu start gần u[0] hơn u[1])
	if (f1 <= f2)
	{
		check = g.Dijkstra(start, u[0], T, Length, prev1);
		if (check)
		{
			delete[] T;
			delete[] Length;
			check =	g.Dijkstra(u[1], end, T, Length, prev2);
		}
	}
	
	// Nếu không có đường đi từ start -> u[0] hoặc u[1] -> end
	// thì tìm đường từ start -> u[1] và u[0] -> end
	if (!check)
	{
		if (prev1 != NULL)
			delete[] prev1;
		if (prev2 != NULL)
			delete[] prev2;

		check = g.Dijkstra(start, u[1], T, Length, prev1);
		if (check)
		{
			delete[] T;
			delete[] Length;
			check = g.Dijkstra(u[0], end, T, Length, prev2);
		}

		int temp = u[0];
		u[0] = u[1];
		u[1] = temp;
	}

	// Nếu vẫn không có đường đi, tức là không tìm được đường đi
	if (!check)
		return NOT_HAS_EULER_PATH;
	
	// Chọn đỉnh bậc lẻ gần start nhất
	int startVertex = findIdxPlace(u[0]);
	nVer = 0;
	eulerPath[nVer] = startVertex;
	nVer++;
	int nE = getNumEdge();
	int k = 0;

	while (nVer - 1 < nE)
	{
		// Chọn 1 cạnh e = (startVertex, i) từ g1
		int bridgeEndV = -1;
		int flag = NOT_DONE;
		for (int i = 0; i < nV; i++)
		{
			if (g1.getEdge(eulerPath[nVer - 1], i) != 0)
			{
				// Nếu cạnh nối giữa hai đỉnh eulerPath[nVer - 1] và i không phải là cầu
				if (g1.bridgeDetection(eulerPath[nVer - 1], i) == NON_BRIDGE)
				{
					eulerPath[nVer] = i; // Chọn cạnh đó (tức thêm đỉnh i vào mảng chu trình euler
					g1.removeEdge(eulerPath[nVer - 1], i); //Xóa cạnh khỏi g: g = g - e
					flag = DONE;
					nVer++;
					break;
				}
				// Ngược lại
				else
				{
					bridgeEndV = i;
				}	
			}
		}
		
		// Chọn cạnh cầu (ở trên) khi không còn lựa chọn nào khác
		if (bridgeEndV != -1 && flag == NOT_DONE)
		{
			eulerPath[nVer] = bridgeEndV;
			g1.removeEdge(eulerPath[nVer - 1], bridgeEndV); // Xóa cạnh khỏi g: g = g - e
			nVer++;
		}
	}
	
	return ret; 
}

// Hàm hủy
CUndirectedGraph::~CUndirectedGraph()
{
	if (idxPlace != NULL)
	{
		delete[] idxPlace;
		idxPlace = NULL;
	}

	for (int i = 0; i < nV; i++)
	{
		delete[] adjencyMatrix[i];
		adjencyMatrix[i] = NULL;
	}
	delete[] adjencyMatrix;
	adjencyMatrix = NULL;
}