//
// Created by alex on 05.03.23.
//

#include "Matrix.h"

enum	types {zero, diag, full};

Matrix::Matrix() {
	this->_detSign = 1;
	this->_linesQuan = 0;
	this->_columnsQuan = 0;
}

Matrix::Matrix(const Matrix &other) {
	this->_linesQuan = other._linesQuan;
	this->_columnsQuan = other._columnsQuan;

	this->_detSign = 1;
	this->_mat.resize(this->_linesQuan);
	for (size_t i = 0; i < this->_linesQuan; ++i) {
		this->_mat[i].resize(this->_columnsQuan);
		for (size_t j = 0; j < this->_columnsQuan; ++j) {
			this->_mat[i][j] = other._mat[i][j];
		}
	}
}

Matrix::Matrix(std::string filename) {
	std::fstream	file;

	file.open(filename, std::fstream::in | std::fstream::out);

	this->_detSign = 1;
 	file >> this->_linesQuan >> this->_columnsQuan;
	this->_mat.resize(this->_linesQuan);

	for (size_t i = 0; i < this->_linesQuan; ++i) {
		this->_mat[i].resize(this->_columnsQuan);
		for (size_t j = 0; j < this->_columnsQuan; ++j) {
			file >> this->_mat[i][j];
		}
	}
}
Matrix::Matrix(size_t linesQuan, size_t colQuan, short type) {
	this->_linesQuan = linesQuan;
	this->_columnsQuan = colQuan;

	this->_mat.resize(this->_linesQuan);
	for (int i = 0; i < this->_linesQuan; ++i) {
		this->_mat[i].resize(_columnsQuan);
	}
	if (type == diag) {
		for (int i = 0; i < linesQuan; ++i) {
			this->_mat[i][i] = 1;
		}
	}
}

Matrix::Matrix(size_t linesQuan, size_t colQuan, std::vector<float> values) {
	size_t	val;

	val = 0;
	this->_linesQuan = linesQuan;
	this->_columnsQuan = colQuan;

	this->_detSign = 1;
	this->_mat.resize(this->_linesQuan);
	for (size_t i = 0; i < this->_linesQuan; ++i) {
		this->_mat[i].resize(this->_columnsQuan);
		for (size_t j = 0; j < this->_columnsQuan; ++j) {
			this->_mat[i][j] = values[val];
			val++;
		}
	}
}

Matrix&	Matrix::operator=(const Matrix &rhs) {
	if (this != &rhs) {
		this->_detSign - rhs._detSign;
		this->_linesQuan = rhs._linesQuan;
		this->_columnsQuan = rhs._columnsQuan;

		this->_mat.resize(this->_linesQuan);
		for (size_t i = 0; i < this->_linesQuan; ++i) {
			this->_mat[i].resize(this->_columnsQuan);
			for (size_t j = 0; j < this->_columnsQuan; ++j) {
				this->_mat[i][j] = rhs[i][j];
			}
		}
	}
	return (*this);
}

Matrix	Matrix::operator*(const Matrix &rhs) {
	Matrix	ret;
	double	sum;

	if (this->_columnsQuan != rhs._linesQuan)
		throw std::exception();
	else {
		ret._linesQuan = this->_linesQuan;
		ret._columnsQuan = rhs._columnsQuan;
		ret._detSign = 1;
		ret._mat.resize(_linesQuan);
		for (int i = 0; i < ret._linesQuan; ++i) {
			ret._mat[i].resize(ret._columnsQuan);
			for (int j = 0; j < ret._columnsQuan; ++j) {
				sum = 0;
				for (int k = 0; k < this->_columnsQuan; ++k) {
					sum += this->_mat[i][k] * rhs._mat[k][j];
				}
				ret._mat[i][j] = sum;
			}
		}
	}
	return (ret);
}

const std::vector<double>&	Matrix::operator[](int rhs) const {
	return (this->_mat[rhs]);
}


void	Matrix::swapLines(size_t line1, size_t line2) {
	this->_detSign *= -1;
	std::swap(this->_mat[line1], this->_mat[line2]);
}

void	Matrix::swapLinesWithMaxAik(size_t begLine, size_t k) {
	size_t	aim;

	aim = begLine;
	for (size_t i = begLine; i < this->_linesQuan; ++i) {
		if ( abs( this->_mat[i][k]) > abs(this->_mat[aim][k]))
			aim = i;
	}
	this->swapLines(begLine, aim);
}

Matrix	Matrix::triangle() const {
	Matrix	ret;
	double	mu;
	int		flag;

	ret = *this;
	if (this->_mat[0][0] == 0)
		ret.swapLinesWithMaxAik(0, 0);
	for (size_t i = 1; i < ret._linesQuan; ++i) {
		ret.swapLinesWithMaxAik(i, i);
		for (size_t k = i; k < ret._linesQuan; ++k) {
			mu = ret._mat[k][i - 1] / ret._mat[i - 1][i - 1];
			if (mu != 0) {
				for (size_t j = 0; j < ret._columnsQuan; ++j) {
					ret._mat[k][j] = ret._mat[k][j] - mu * ret._mat[i - 1][j];
				}
			}
		}
		if (ret._mat[i][i] == 0) {
			flag = 0;
			for (int k = i; k < ret._linesQuan; ++k) {
				if (ret._mat[k][i] != 0) {
					ret.swapLines(i, k);
					flag = 1;
					break;
				}
			}
			if (!flag)
				return (ret);
		}
	}
	return (ret);
}

float	Matrix::findDet() const {
	Matrix	triangle;
	float	det;

	triangle = this->triangle();
	det = triangle._detSign;
	for (size_t i = 0; i < triangle._linesQuan; i++) {
		det *= triangle[i][i];
	}
	return (det);
}

Matrix	Matrix::solve(const Matrix &b) const {
	Matrix	A;
	Matrix	ret(this->_linesQuan, 1, zero);
	std::vector<float>	solution;
	float	sum;
	float	val;

	if (this->findDet() == 0) {
		std::cout << "\033[1;31mNo solution\033[0m" << std::endl;
		return (ret);
	}
	A = *this;
	A._columnsQuan++;
	ret._linesQuan = this->_columnsQuan;
	ret._mat.resize(_linesQuan);
	for (int i = 0; i < A._linesQuan; ++i) {
		A._mat[i].resize(A._columnsQuan);
		A._mat[i][A._columnsQuan - 1] = b[i][0];
		ret._mat[i].resize(ret._columnsQuan);
	}
	solution.resize(A._linesQuan);
	A = A.triangle();
	for (int i = solution.size() - 1; i >= 0 ; --i) {
		sum = 0;
		for (int j = i + 1; j < A._columnsQuan - 1; ++j) {
			sum += A[i][j] * solution[j];
		}
		val = (A[i][A._columnsQuan - 1] - sum) / A[i][i];
		solution[i] = val;
	}
	for (int i = 0; i < solution.size(); ++i) {
		ret._mat[i][0] = solution[i];
	}
}

std::ostream&	operator<<(std::ostream& os, const Matrix& dt)
{
	for (int i = 0; i < dt._linesQuan; ++i) {
		for (int j = 0; j < dt._columnsQuan; ++j) {
			os << dt._mat[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}

Matrix	Matrix::inverseMatrix() const {
	Matrix	A;
	Matrix	ret;
	Matrix	E(this->_linesQuan, this->_columnsQuan, diag);
	Matrix	ESmall(4, 1, zero);
	Matrix	x;

	if (this->findDet() == 0) {
		std::cout << "\033[1;31mNo inverse matrix\033[0m" << std::endl;
		return (ret);
	}
	A = *this;
	ret._columnsQuan = this->_columnsQuan;
	ret._linesQuan = this->_columnsQuan;
	ret._mat.resize(_linesQuan);
	for (int i = 0; i < A._linesQuan; ++i) {
		ret._mat[i].resize(ret._columnsQuan);
	}
	for (int i = 0; i < this->_columnsQuan; ++i) {
		for (int j = 0; j < A._linesQuan; ++j) {
			ESmall._mat[j][0] = E[j][i];
		}
		x = A.solve(ESmall);
		for (int j = 0; j < x._linesQuan; ++j) {
			ret._mat[j][i] = x[j][0];
		}
	}
	return (ret);
};
