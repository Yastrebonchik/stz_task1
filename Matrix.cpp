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
	std::cout << "file is opened: " << file.is_open() << std::endl;

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


std::pair<Matrix, Matrix>	Matrix::LU() const {
	std::pair<Matrix, Matrix>	ret;
	Matrix	L;
	Matrix	LMid;
	Matrix	U;

	L._linesQuan = this->_linesQuan;
	L._columnsQuan = this->_columnsQuan;
	L._mat.resize(_linesQuan);
	U = *this;
	for (int i = 0; i < _linesQuan; ++i) {
		L._mat[i].resize(_columnsQuan);
	}
//	for (int i = 0; i < _linesQuan; ++i) {
//		L._mat[i][i] = 1;
//		for (int j = i + 1; j < L._columnsQuan; j++)
//			L._mat[j][i] = U._mat[j][i] / U._mat[i][i];
//	}
//	for (int k = 1; k < L._columnsQuan; k++) {
//		for (int i = k - 1; i < L._columnsQuan; i++)
//			for (int j = i; j < L._columnsQuan; j++)
//				L._mat[j][i] = U[j][i] / U[i][i];
//		for (int i = k; i < L._columnsQuan; i++)
//			for (int j = k-1; j < L._columnsQuan; j++)
//				U._mat[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
//	}
	ret.first = L;
	ret.second = U;
	ret = std::make_pair(L, U);
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

Matrix	Matrix::solve() const {
	Matrix	A;
	Matrix	ret(this->_linesQuan, 1, zero);
	std::vector<float>	solution;
	float	sum;
	float	val;

	if (this->findDet() == 0) {
		std::cout << "No solution" << std::endl;
		return (ret);
	}
	A = this->triangle();
	solution.resize(A._linesQuan);
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
	Matrix	x;

	A = *this;
	A._columnsQuan++;
	ret._columnsQuan = this->_columnsQuan;
	ret._linesQuan = this->_columnsQuan;
	ret._mat.resize(_linesQuan);
	for (int i = 0; i < A._linesQuan; ++i) {
		A._mat[i].resize(A._columnsQuan);
		ret._mat[i].resize(ret._columnsQuan);
	}
	for (int i = 0; i < this->_columnsQuan; ++i) {
		for (int j = 0; j < A._linesQuan; ++j) {
			A._mat[j][A._columnsQuan - 1] = E[j][i];
		}
		x = A.solve();
		for (int j = 0; j < x._linesQuan; ++j) {
			ret._mat[j][i] = x[j][0];
		}
	}
//	Matrix	Y(this->_linesQuan, 1, 0);
//	Matrix	E(this->_columnsQuan, this->_linesQuan, diag);

//	LU = this->LU();
//	ret._linesQuan = this->_linesQuan;
//
//	for (int k = 0; k < ret._linesQuan; ++k) {
//		for (int i = 0; i < Y._linesQuan; ++i) {
//			sum = 0;
//			for (int j = 0; j < i; ++j) {
//				sum += Y[j][0] * LU.first[i][j];
//			}
//			Y._mat[i][0] = E[i][k] - sum;
//		}
//		for (int i = ret._linesQuan - 1; i >= 0 ; --i) {
//			sum = 0;
//			for (int j = i; j < ret._linesQuan - 1; ++j) {
//				sum += LU.second[i][j] * ret[j][k];
//			}
//			ret._mat[i][k] = (Y[i][0] - sum) / LU.second[i][i];
//		}
//	}
	return (ret);
};
