#include <iostream>
#include <typeinfo> 

int print_values() { //без параметров

	return 0;
}

int print_values(std::ostream& os) { //только поток
	return 0;
}

template <typename T>
void print_values(std::ostream& os, T value) {
	os << typeid(value).name() << ": " << value << std::endl;
	os << '\n';
	return;
}

template<typename T, typename... Args> // Args — это пакет параметров шаблона
void print_values(std::ostream& os, T value, Args... arg)
{
	os << typeid(value).name() << ": " << value << std::endl;
	print_values(os, arg...); // рекурсия
}