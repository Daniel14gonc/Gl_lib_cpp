#pragma once 

#include <iostream>
#include <string>
#include <vector4.h>

using namespace std;

template<int N, int M>
struct Matrix
{	
	float matrix[N][M];
	
	Matrix<N, M> operator * (Matrix other)
	{
		Matrix<N, M> m;
		for (int i = 0; i < N; i++)
		{
			for(int j = 0; j < other.getRows(); j++)
			{
				float res = 0;
				for(int k = 0; k < M; k++)
				{
					res += this->getElement(i, k) * other.getElement(k, j);
				}
				m.setElement(i, j, res);
			}
		}
		return m;
	}

	Vector4 operator * (Vector4 other)
	{
		float x1 = this->getElement(0, 0) * other.getX() +
				   this->getElement(0, 1) * other.getY() +
				   this->getElement(0, 2) * other.getZ() +
				   this->getElement(0, 3) * other.getW();
		
		float x2 = this->getElement(1, 0) * other.getX() +
				   this->getElement(1, 1) * other.getY() +
				   this->getElement(1, 2) * other.getZ() +
				   this->getElement(1, 3) * other.getW();

		float x3 = this->getElement(2, 0) * other.getX() +
				   this->getElement(2, 1) * other.getY() +
				   this->getElement(2, 2) * other.getZ() +
				   this->getElement(2, 3) * other.getW();

		float x4 = this->getElement(3, 0) * other.getX() +
				   this->getElement(3, 1) * other.getY() +
				   this->getElement(3, 2) * other.getZ() +
				   this->getElement(3, 3) * other.getW();
		Vector4 m(x1, x2, x3, x4);
		return m;
	}

	void setElement(int x, int y, float value)
	{
		matrix[x][y] = value;
	}

	float getElement(int x, int y)
	{
		return matrix[x][y];
	}

	int getRows()
	{
		return N;
	}
	
	int getColumns()
	{
		return M;
	}

	string to_string()
	{
		string res = "M(";
		for (int i = 0; i < N; i++)
		{
			res += "[ ";
			for (int j = 0; j < M; j++)
			{
				if (j + 1 == M)
					res += std::to_string(matrix[i][j]) + " ";
				else
					res += std::to_string(matrix[i][j]) + ", ";
				
			}
			res += "]";
		}
		res += ")";
		return res;
	}
};