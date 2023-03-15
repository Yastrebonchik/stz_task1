//
// Created by alex on 05.03.23.
//

#ifndef TASK1_MATRIX_H
# define TASK1_MATRIX_H

# include <vector>
# include <fstream>
# include <iostream>

class Matrix {
private:
	float	_detSign;
	size_t	_linesQuan;
	size_t	_columnsQuan;
	std::vector<std::vector<double>>	_mat;

	void	swapLines(size_t line1, size_t line2);
	void	swapLinesWithMaxAik(size_t begLine, size_t k);

public:
	Matrix();
	Matrix(std::string filename);
	Matrix(size_t linesQuan, size_t _colQuan, short type);
	Matrix(const Matrix &other);
	Matrix(size_t linesQuan, size_t _colQuan, std::vector<float> values);

	Matrix&	operator=(const Matrix &rhs);
	Matrix	operator*(const Matrix &rhs);
	const std::vector<double>&	operator[](int rhs) const;

	Matrix	triangle() const;
	float	findDet() const;
	Matrix	solve(const Matrix &b) const;
	Matrix	inverseMatrix() const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);
};


#endif //TASK1_MATRIX_H
