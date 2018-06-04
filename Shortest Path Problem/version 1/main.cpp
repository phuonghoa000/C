# pragma warning (disable: 4996)
# include "Graph.h"

int main(int argc, char* argv[])
{
	CGRAPH g;
	stack<int> path; // Lưu đường đi ngắn nhất (hoặc đường đi nhanh nhất)
	int* T; // Mảng đánh dấu đỉnh trong T
	float* Length; // Độ dài ngắn nhất (hoặc thời gian nhanh nhất) từ điểm đầu (start) tới các điểm khác
	int* Prev; // Mảng lưu điểm liền trước của đường đi
	int start = atoi(argv[3]); // Điểm đầu
	int end = atoi(argv[4]); // Điểm cuối
	int prior = atoi(argv[5]); // Lựa chọn đường đi ngắn nhất hay nhanh nhất
	bool check;
	float value;

	// Mở và đọc file lưu thông tin đường
	freopen(argv[2], "rt", stdin);
	g.readFileStreet(); 
	cin.clear();

	// Mở và đọc file lưu thông tin tên địa điểm
	freopen(argv[1], "rt", stdin);
	g.readFilePlace();

	// Mở file để ghi
	freopen(argv[6], "wt", stdout);
	
	// Gọi hàm Dijkstra tìm đường đi ngắn nhất (hoặc nhanh nhất) từ start tới end
	check = g.Dijkstra(start, end, prior, T, Length, Prev);
	if (check)
	{
		value = Length[end]; // Lưu độ dài đường đi ngắn nhất hoặc độ lớn thời gian ngắn nhất
		g.savePath(start, end, Prev, path); // Gọi hàm lưu đường đi tìm được		
		g.writeFile(path, value); // Xuất đường đi tìm được vào file
	}

	// Hủy cấp phát động
	delete[] T;
	T = NULL;
	delete[] Length;
	Length = NULL;
	delete[] Prev;
	Prev = NULL;
	
	return 0;
}