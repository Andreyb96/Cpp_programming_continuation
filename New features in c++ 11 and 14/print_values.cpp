#include <iostream>
#include <typeinfo> 

int print_values() { //��� ����������

	return 0;
}

int print_values(std::ostream& os) { //������ �����
	return 0;
}

template <typename T>
void print_values(std::ostream& os, T value) {
	os << typeid(value).name() << ": " << value << std::endl;
	os << '\n';
	return;
}

template<typename T, typename... Args> // Args � ��� ����� ���������� �������
void print_values(std::ostream& os, T value, Args... arg)
{
	os << typeid(value).name() << ": " << value << std::endl;
	print_values(os, arg...); // ��������
}