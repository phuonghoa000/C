#pragma warning (disable: 4996)
#include "Graph.h"

int main(int argc, char* argv[])
{
	CGRAPH g;
	stack<int> path; // Lưu đường đi ngắn nhất (hoặc nhanh nhất)
	int* T; // Mảng đánh dấu đỉnh trong T
	float* Length; // Độ dài ngắn nhất (hoặc thời gian nhanh nhất) từ điểm đầu (start) tới các điểm khác trong đồ thị
	int* Prev; // Mảng lưu điểm liền trước của đường đi
	int start = atoi(argv[3]); // Điểm đầu
	int middle = atoi(argv[4]); // Điểm phải đi qua
	int end = atoi(argv[5]); // Điểm cuối
	int prior = atoi(argv[6]); // Chọn lựa ngắn nhất hoặc nhanh nhất
	bool check;
	float value; // Độ dài đường đi ngắn nhất hoặc thời gian ngắn nhất

	// Mở file và đọc thông tin về các con đường
	freopen(argv[2], "rt", stdin);
	g.readFileStreet();
	cin.clear();

	// Mở file và đọc tên các địa điểm
	freopen(argv[1], "rt", stdin);
	g.readFilePlace();
	
	// Mở file để ghi thông tin đường đi
	freopen(argv[7], "wt", stdout);

	// Gọi hàm Dijkstra tìm đường đi ngắn nhất (hoặc thời gian ngắn nhất) từ middle tới end
	check = g.Dijkstra(middle, end, prior, T, Length, Prev);
	if (check)
	{
		value = Length[end]; // Lưu đường đi ngắn nhất (hoặc thời gian ngắn nhất) tìm được
		g.savePath(middle, end, Prev, path); // Gọi hàm lưu đường đi tìm được
		// Hủy cấp phát động
		delete[] T;
		delete[] Length;
		delete[] Prev;
		// Gọi lại hàm Dijstra để tìm đường đi ngắn nhất (hoặc nhanh nhất) từ start tới middle
		check = g.Dijkstra(start, middle, prior, T, Length, Prev);
		if (check)
		{
			value = value + Length[middle]; // Lưu đường đi ngắn nhất (hoặc thời gian ngắn nhất) từ start tới end
			path.pop();
			g.savePath(start, middle, Prev, path);
			g.writeFile(path, value);
		}
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