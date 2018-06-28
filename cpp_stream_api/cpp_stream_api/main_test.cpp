#include "streamapi.h"
#include <sstream>

class my_class
{
public:
	explicit my_class(int x = 0)
		: x_(x)
	{
	}

	friend bool operator==(const my_class& lhs, const my_class& rhs)
	{
		return lhs.x_ == rhs.x_;
	}

	friend bool operator!=(const my_class& lhs, const my_class& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const my_class& lhs, const my_class& rhs)
	{
		return lhs.x_ < rhs.x_;
	}

	friend bool operator<=(const my_class& lhs, const my_class& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const my_class& lhs, const my_class& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const my_class& lhs, const my_class& rhs)
	{
		return !(lhs < rhs);
	}

private:
	int x_;
};

int main()
{
	std::stringstream ss;
	ss << 1 << ":" << 2 << ";" << 3 << ":" << 4 << ";";
	int x, y;
	x = y = 0;
	char c;
	while (!ss.eof())
	{
		ss >> x >> c >> y >> c;
	}
	ss >> x;
	std::vector<my_class> what = StreamAPI::array_of<my_class>(my_class(7)
		,my_class(1),my_class(2),my_class(3),my_class(4)
		,my_class(1),my_class(2),my_class(3),my_class(4)
		,my_class(1),my_class(2),my_class(3),my_class(4)
		,my_class(1),my_class(2),my_class(3),my_class(4)
		,my_class(1),my_class(2),my_class(3),my_class(4)
		,my_class(1),my_class(2),my_class(3),my_class(4)
		,my_class(5),my_class(6),my_class(4),my_class(5),my_class(6));
	// std::sort(what.begin(), what.end());;
	bool contains = StreamAPI::contains1(what, my_class(3));
	contains = StreamAPI::contains(what, my_class(3));
	// int index = StreamAPI::index_fist(what, 3);
	return 0;
}