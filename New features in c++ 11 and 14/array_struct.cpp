#include <utility>

template<class T>
struct Array
{
	// все объ€вленные ниже методы уже реализованы
	explicit Array(size_t size = 0);
	Array(Array const& a);
	Array & operator=(Array const& a);
	~Array();

	size_t size() const;
	T &         operator[](size_t i);
	T const&    operator[](size_t i) const;

	Array(Array&& obj) : size_(obj.size_), data_(obj.data_)
	{
		obj.size_ = 0;
		obj.data_ = nullptr;
	}

	// реализуйте перемещающий оператор присваивани€
	Array& operator= (Array&& obj)
	{
		this->~Array();
		this->size_ = obj.size_;
		this->data_ = obj.data_;
		obj.size_ = 0;
		obj.data_ = nullptr;
		return *this;
	}
private:
	size_t  size_;
	T *     data_;
};