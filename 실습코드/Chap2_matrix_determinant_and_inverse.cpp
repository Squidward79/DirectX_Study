///
///	4 X 4 행렬의 Transpose, Determinant, Inverse를 구하는 프로그램  
/// 


#include <iostream>

using namespace std;

int calDetRecursive(int** src, int excluded_row, int dim); // recursively calculate a determinant
void getMinorMat(int** mat, int** src, int excluded_column, int excluded_row, int dim); //Make a small-scale minor matrix.
void printMat(float mat[][4]);

int main()
{
	cout << endl << "Matrix :  " << endl;
	float matrix[4][4] = { {1,1,1,-1}, {1,1,-1,1}, { 1,-1,1,1}, {-1,1,1,1} };
	printMat(matrix);

#pragma region Transpose

	float transMat[4][4];
	cout << endl << "Transpose: " << endl;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transMat[j][i] = matrix[i][j];
		}
	}

	printMat(transMat);

#pragma endregion


#pragma region Determinant

	int det = 0;

	//create a two-dimention matrix
	int** A = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		A[i] = new int[4];
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			A[i][j] = matrix[i][j];
		}
	}

	det = calDetRecursive(A,0,4); //calculate determinant

	cout << endl << "determinant : " << det << endl;

#pragma endregion


#pragma region Inverse
	if (det == 0)
	{
		cout << "No Inverse Matrix" << endl;
		return -1;
	}

	int** mat = new int *[3];
	for (int i = 0; i < 3; i++)
	{
		mat[i] = new int[3];
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			getMinorMat(mat, A, i, j, 4);
			float cofactor = (int)pow(-1, i + j) * calDetRecursive(mat, 0, 3);
			transMat[i][j] = cofactor / (float)det;
		}
	}

	cout << endl<<"Inverse : " << endl;
	printMat(transMat);

	for (int i = 0; i < 3; ++i)
	{
		delete[] mat[i];
	}
	delete[] mat;

#pragma endregion

	return 0;
}

int calDetRecursive(int** src, int excluded_row, int dim)
{
	int det = 0;

	if (dim > 1)
	{
		if (dim == 2)
		{
			return (src[0][0] * src[1][1]) - (src[0][1] * src[1][0]);
		}

		for(int i =0; i< dim; i++)
		{
			int** mat = new int *[dim - 1];
			for (int i = 0; i < dim - 1; i++)
			{
				mat[i] = new int[dim - 1];
			}
			getMinorMat(mat, src, i, excluded_row, dim);

			det += src[0][i] * (int)pow(-1, i) * calDetRecursive(mat, 0 ,dim-1);

			for (int i = 0; i < dim - 1; ++i)
			{
				delete[] mat[i];
			}
			delete[] mat;
		}
		return det;
	}
	return -1;
}

void getMinorMat(int** mat, int** src, int excluded_column, int excluded_row, int dim)
{
	int m = 0;
	for (int i = 0; i < dim; ++i)
	{
		int n = 0;
		if (i == excluded_row) continue;

		for (int j = 0; j < dim; ++j)
		{
			if ( j == excluded_column) continue;
			mat[m][n] = src[i][j];
			n++;
		}
		m++;
	}
}

void printMat(float mat[][4])
{

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << mat[i][j] << " ";
			if ((j + 1) % 4 == 0) cout << endl;
		}
	}
}
