#pragma once 

#include <iostream>
#include <string>

using namespace std;

template<int N, int M>
struct Matrix
{	
	float matrix[N][M];
	
	Matrix<N, M> operator * (Matrix other)
	{
		float x[N][M];
		Matrix<N, M> m;
		for (int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
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