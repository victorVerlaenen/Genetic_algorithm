#pragma once
#include <iostream>

// Matrix2D 
template <typename Type>
using Matrix2D = std::vector<std::vector<Type>>;

template <typename Type>
std::ostream& operator<<(std::ostream& os, const Matrix2D<Type>& matrix)
{
	os << "[";
	for (auto row : matrix)
	{
		os << "\n[ ";
		for (auto value : row)
		{
			os << value << " ";
		}
		os << "]";
	}
	os << "]\n";

	return os;
}