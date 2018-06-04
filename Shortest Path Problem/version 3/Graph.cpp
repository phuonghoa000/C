#include "Graph.h"

// Hàm đọc file chứa thông tin các con đường liên kết các địa điểm
void CGRAPH::readFileStreet()
{
	string s;

	cin >> n; // Đọc số địa điểm
	getline(cin, s);
	
	// Xin cấp phát động
	L = new CSTREET*[n];
	for (int i = 0; i < n; i++)
		L[i] = new CSTREET[n];

	// Đọc file
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			L[i][j].readFile(j - n + 1);
}

// Hàm đọc file lưu tên các địa điểm
void CGRAPH::readFilePlace()
{
	place = new string[n];

	for (int i = 0; i < n; i++)
		getline(cin, place[i]);
}

// Hàm đọc tọa độ các địa điểm
void CGRAPH::readFileGPSS()
{
	pointPlace = new CPOINT[n];

	for (int i = 0; i < n; i++)
		pointPlace[i].input();
}

// Hàm đọc chỉ số các địa điểm của các con đường cần đi qua
void CGRAPH::readFileStreetToVisit(int* &a, int &num)
{
	char kt[5];
	int i = 0;

	a = new int[n];
	do
	{
		int value;
		int j;
		
		cin >> value; // Đọc địa điểm xuất phát
		// Thêm value vào mảng nếu value chưa tồn tại trong mảng
		for (j = 0; j < i; j++)
			if (value == a[j])
				break;
		if (j == i)
		{
			a[i] = value;
			i++;
		}

		cin >> value; // Đọc điểm dừng
		for (j = 0; j < i; j++)
			if (value == a[j])
				break;
		// Thêm value vào mảng nếu value chưa tồn tại trong mảng
		if (j == i)
		{
			a[i] = value;
			i++;
		}
	}
	while (gets(kt) != NULL);

	num = i; // Số phần tử mảng
}


// Hàm xuất đường đi cần tìm và độ dài đường đi ngắn nhất
void CGRAPH::writeFile(stack<int> path)
{
	int idx1;

	// Xuất đường đi ra file
	idx1 = path.top();
	while (path.size() > 1)
	{
		int idx2;
		cout << place[idx1] << " --- ";
		path.pop();
		idx2 = path.top();
		if (L[idx1][idx2].strName.length() != 0)
			cout << L[idx1][idx2].strName << " ---> ";
		else
			cout << L[idx2][idx1].strName << " ---> ";
		cout << place[idx2] << endl;
		idx1 = idx2;
	}
}


// Hàm khởi tạo các tham số thuật toán Dijkstra
void CGRAPH::init(int start, int* &T, float* &Length, int* &Prev)
{
	// Xin cấp phát động
	T = new int[n];
	Length = new float[n];
	Prev = new int[n];

	for(int i = 0; i < n; i ++)
	{
		T[i] = 1;		  // 1: đỉnh i còn nằm trong T
		Length[i] = INF;  // Khởi tạo độ dài ban đầu (thời gian ban đầu) là vô cùng lớn
		Prev[i] = -1;     // Chưa có đỉnh liền trước
	}
	// Khởi tạo đỉnh đầu tiên
	Length[start] = 0;  
}


// Hàm tìm đường đi ngắn nhất giữa hai điểm (start và end) bằng thuật toán Dijkstra
bool CGRAPH::Dijkstra(int start, int end, int* &T, float* &Length, int* &Prev)
{
	// Khởi tạo các thông số cho thuật toán
	init(start, T, Length, Prev);
	
	while(T[end] == 1)   // Trong khi đỉnh cuối vẫn nằm trong T
	{
		float fMin = INF;	
		int v = -1;

		//Tìm điểm v thuộc T sao cho Length[v] nhỏ nhất
		for(int i = 0 ; i < n; i ++)
		{
			if(T[i] == 1 && Length[i] != INF && (Length[i] < fMin || fMin == INF))
			{
				fMin = Length[i];
				v = i;
			}
		}

		if(fMin == INF)
			return false;
		
		Length[v] = fMin;
		T[v] = 0;  // Loại v ra khỏi T
		
		// Tìm tổng độ dài các cạnh (tổng trọng số) từ start tới v
		for(int j = 0; j < n; j ++)
		{
			// Nếu đỉnh j còn trong T và có cạnh nối v và j
			if(T[j] == 1 && L[v][j].fLength != 0)
			{
				// Nếu Length[j] hiện tại bằng lúc khởi tạo
				// hoặc lớn hơn tổng độ dài đường đi từ start tới đỉnh v và độ dài cạnh nối v và j
				if(Length[j] == -1 || Length[j] > Length[v] + L[v][j].fLength)
				{
					// Length[j] bằng tổng độ dài đường đi
					// từ start tới v và độ dài cạnh nối v và j
					Length[j] = Length[v] + L[v][j].fLength;
					Prev[j] = v; // Lưu vết đường đi
				}
			}
		}
	}

	return true;
}

// Hàm lưu đường đi ngắn nhất từ đỉểm đầu (start) tới điểm cuối (end) vào biến kiểu stack
void CGRAPH::savePath(int start, int end, int* Prev, stack<int> &Path)
{
	// Nếu đỉnh đầu bằng đỉnh cuối,
	// đường đi chính là đỉnh đó
	if (start == end)
		Path.push(start);
	// Nếu đỉnh đầu khác đỉnh cuối
	else
	{
		int temp = end;		
		// Truy vết đường đi từ đỉnh cuối end về đỉnh đầu start,
		while (temp != start)
		{
			Path.push(temp); // lưu vết vào stack
			temp = Prev[temp];
		}
		Path.push(temp);
	}
}

// Phương thức khởi tạo mặc định
CGRAPH::CGRAPH()
{
	place = NULL;
	pointPlace = NULL;
}

// Phương thức hủy
CGRAPH::~CGRAPH()
{
	if (place != NULL)
	{
		delete[] place;
		place = NULL;
	}

	if (pointPlace != NULL)
	{
		delete[] pointPlace;
		pointPlace = NULL;
	}

	for (int i = 0; i < n; i++)
	{
		delete[] L[i];
		L[i] = NULL;
	}
	delete[] L;
	L = NULL;
}
