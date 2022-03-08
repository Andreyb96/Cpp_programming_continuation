// ����������� ��������� Point ��� ����������
/* struct Point
{
	constexpr Point(double x, double y)
		: x(x), y(y)
	{}

	double x = 0;
	double y = 0;
};
*/

// ��������
constexpr Point operator+(const Point &pt1, const Point &pt2) // operator+
{

	return  Point(pt2.x + pt1.x, pt2.y + pt1.y);
}

// ��������� ������������
constexpr double operator*(const Point &pt1, const Point &pt2)// operator+
{
	return pt2.x*pt1.x + pt2.y*pt1.y;
}

// ���������
constexpr Point operator-(const Point &pt1, const Point &pt2)// operator+
{
	return Point(pt1.x - pt2.x, pt1.y - pt2.y);
}