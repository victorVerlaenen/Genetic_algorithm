#pragma once
#include <iostream>

// Matrix2D 
template <int N, int DIMENSIONS>
using Matrix2D = std::array<std::array<float, DIMENSIONS>, N>;

template <int N, int DIMENSIONS>
std::ostream& operator<<(std::ostream& os, const Matrix2D<N, DIMENSIONS>& matrix)
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