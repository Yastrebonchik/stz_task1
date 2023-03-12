//
// Created by alex on 05.03.23.
//

#ifndef TASK1_MATRIX_H
# define TASK1_MATRIX_H

# include <vector>
# include <fstream>
# include <iostream>
//?# include <Eigen/Dense>

class Matrix {
private:
	float	_detSign;
	size_t	_linesQuan;
	size_t	_columnsQuan;
	std::vector<std::vector<float>>	_mat;

	void	swapLines(size_t line1, size_t line2);
	void	swapLinesWithMaxAik(size_t begLine, size_t k);

public:
	Matrix();
	explicit Matrix(std::string filename);
	Matrix(Matrix &other);
	Matrix(size_t linesQuan, size_t _colQuan, std::vector<float> values);

	Matrix&	operator=(const Matrix &rhs);
	const std::vector<float>&	operator[](int rhs) const;

	void	addMatrixFromRight(Matrix other);
	Matrix	triangle() const;
	float	findDet() const;
	void	solve() const;
	Matrix	inverseMatrix() const;
	std::pair<Matrix, Matrix>	matSeparate();
};


#endif //TASK1_MATRIX_H
