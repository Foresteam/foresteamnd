#pragma once
#include <iostream>

/// Matrix, rows*cols
class Matrix {
protected:
	double** self;
	int rows, cols;
	void Init(int rows, int cols);
    /// @deprecated Matrix can now be initialized directly from double[][]
	void Copy(const Matrix& other);
public:
	Matrix& operator=(const Matrix& other);
    /// @param array An array of double to initialize from
	Matrix(int rows, int cols, double** array = nullptr);
	Matrix(const Matrix& other);
	~Matrix();

    int Rows();
    int Cols();
	/// @return Determinator
	double Det();

	/// Sets the main diag to 1
	void Fill1();

    /// @return Matrix with no row and no col
	Matrix Cropped(int row, int col);
    /// @return Transposed matrix
	Matrix Transposed();

    /// Prints matrix
    //// @param roundTo Number of digits after point
	void Print(int roundTo = 2);

	/// Adds toBeAdded'th row to addTo'th row of matrix m, multiplied by k
	static void Manipulate(Matrix& m, int toBeAdded, int addTo, double k);
	/// Adds toBeAdded'th row to addTo'th row of matrix m and pair, multiplied by k
	static void Manipulate(Matrix& m, Matrix& pair, int toBeAdded, int addTo, double k);
	/// Multiplies toChange'th row of m by k
	static void Manipulate(Matrix& m, int toChange, double k);
    /// Multiplies toChange'th row of m and pair by k
	static void Manipulate(Matrix& m, Matrix& pair, int toChange, double k);

	Matrix operator*(const double& a);
	Matrix operator/(const double& a);
	Matrix operator*(const Matrix& other);
	Matrix operator-();
    
    /// @return Row
    double* operator[](const int& index) const;
};