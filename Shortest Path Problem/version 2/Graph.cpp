#include "Graph.h"

// Hàm đọc file chứa đường liên kết các địa điểm
void CGRAPH::readFileStreet()
{
	char c;

	cin >> n; // Đọc số địa điểm
	cin >> c; // Đọc ký tự xuống dòng endline
	
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

// Hàm làm tròn số thực đến chữ số thập phân thứ 5
float roundNum(float f)
{
	float fCarry;
	int i;

	f = f*100000; // Nhân f cho 10^5
	fCarry = 0.5;
	i = (int)f;
	if (f - i >= fCarry) // Nếu phần thập phân của f (lúc này) lớn hơn hoặc bằng 0.5,
		i ++; // thì làm tròn phần thập phân đó lên 1.0
	f = (float)i/100000; // Trả lại giá trị tương đương giá trị ban đầu của f

	return f;
}

// Hàm ghi kết quả đường đi tìm được vào file
void CGRAPH::writeFile(stack<int> path, float value)
{
	int idx1;

	value = roundNum(value); // Làm tròn số
	cout << value << endl;

	// Xuất đường đi ra file
	idx1 = path.top();
	if (path.size() == 1)
		cout << place[idx1];
	else
	{
		while (path.size() > 1)
		{
			int idx2;
			cout << place[idx1] << " --- ";
			path.pop();
			idx2 = path.top();
			cout << L[idx1][idx2].strName << " ---> ";
			cout << place[idx2] << endl;
			idx1 = idx2;
		}
	}
}

// Hàm lấy giá trị từ một phần tử trong đồ thị
float CGRAPH::getterValue(int prior, int row, int column)
{
	// prior = 1: lấy fLength (độ dài con đường)
	// prior = 0: lấy fTime (thời gian đi hết con đường)
	if (prior)
		return L[row][column].fLength;
	else
		return L[row][column].fTime;
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
		Length[i] = INF;  // Khởi tạo độ dài ban đầu (hoặc thời gian ban đầu) là vô cùng lớn
		Prev[i] = -1;     // Chưa có đỉnh liền trước
	}
	// Khởi tạo đỉnh đầu tiên
	Length[start] = 0;  
}


// Hàm tìm đường đi ngắn nhất (hoặc nhanh nhất) giữa hai điểm (start và end) bằng thuật toán Dijkstra
bool CGRAPH::Dijkstra(int start, int end, int prior, int* &T, float* &Length, int* &Prev)
{
	// Khởi tạo các thông số cho thuật toán
	this->init(start, T, Length, Prev);
	
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
		{
			cout << "Khong tim thay duong di." << endl;
			return false;
		}
		
		Length[v] = fMin;
		T[v] = 0;  // Loại v ra khỏi T
		
		
		// Tìm tổng độ dài các cạnh (tổng trọng số) từ start tới v
		// (hoặc tổng thời gian nhỏ nhất để di chuyển từ start tới v)
		for(int j = 0; j < n; j ++)
		{
			float fCarry;
			fCarry = this->getterValue(prior, v, j);
			// Nếu đỉnh j còn trong T và có cạnh nối v và j
			if(T[j] == 1 && fCarry != 0)
			{
				// Nếu Length[j] hiện tại bằng lúc khởi tạo
				// hoặc lớn hơn tổng độ dài đường đi (hoặc tổng thời gian đi) từ start tới đỉnh v
				// và độ dài cạnh nối v và j
				if(Length[j] == -1 || Length[j] > Length[v] + fCarry)
				{
					// Length[j] bằng tổng độ dài đường đi (hoặc tổng thời gian đi)
					// từ start tới v và độ dài cạnh nối v và j
					Length[j] = Length[v] + fCarry;
					Prev[j] = v; // Lưu vết đường đi
				}
			}
		}
	}
	return true;
}

// Hàm lưu đường đi ngắn nhất (hoặc đường đi có thời gian nhỏ nhất)
// từ đỉểm đầu (start) tới điểm cuối (end) vào biến kiểu stack
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
}

// Phương thức hủy
CGRAPH::~CGRAPH()
{
	for (int i = 0; i < n; i++)
	{
		delete[] L[i];
		L[i] = NULL;
	}
	delete[] L;
	L = NULL;
}
