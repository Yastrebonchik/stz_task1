//
// Created by alex on 05.03.23.
//

#include "Matrix.h"

Matrix::Matrix() {
	this->_detSign = 1;
	this->_linesQuan = 0;
	this->_columnsQuan = 0;
}

Matrix::Matrix(Matrix &other) {
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

Matrix::Matrix(size_t linesQuan, size_t _colQuan, std::vector<float> values) {
	size_t	val;

	val = 0;
	this->_linesQuan = linesQuan;
	this->_columnsQuan = _colQuan;

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

const std::vector<float>&	Matrix::operator[](int rhs) const {
	return (this->_mat[rhs]);
}

void	Matrix::addMatrixFromRight(Matrix other) {
	size_t	prevLinesQuan;
	size_t	prevColsQuan;
	size_t	count;

	prevColsQuan = this->_columnsQuan;
	this->_columnsQuan += other._columnsQuan;

	for (size_t i = prevLinesQuan; i < this->_linesQuan; ++i) {
		this->_mat[i].resize(this->_linesQuan);
		count = 0;
		for (size_t j = prevColsQuan; i < this->_columnsQuan; ++j) {
			this->_mat[i][j] = other._mat[i][count];
			count++;
		}
	}
}

void	Matrix::swapLines(size_t line1, size_t line2) {
	this->_detSign *= -1;
	std::swap(this->_mat[line1], this->_mat[line2]);
}

void	Matrix::swapLinesWithMaxAik(size_t begLine, size_t k) {
	size_t	aim;

	aim = begLine;
	for (size_t i = begLine; i < this->_linesQuan; ++i) {
		if (this->_mat[aim][k] == 0 || this->_mat[i][k] > this->_mat[aim][k])
			aim = i;
	}
	this->swapLines(begLine, aim);
}

Matrix	Matrix::triangle() const {
	Matrix	ret;
	float	mu;

	ret = *this;
	ret.swapLinesWithMaxAik(0, 0);
	for (size_t i = 1; i < ret._linesQuan; ++i) {
		if (ret._mat[i][i] == 0) {

		}
		ret.swapLinesWithMaxAik(i, i);
		if (ret._mat[i][i] == 0)
			return (ret);
		for (size_t k = i; k < ret._linesQuan; ++k) {
			mu = ret._mat[k][i - 1] / ret._mat[i - 1][i - 1];
			if (mu != 0) {
				for (size_t j = 0; j < ret._columnsQuan; ++j) {
					ret._mat[k][j] = ret._mat[k][j] - mu * ret._mat[i - 1][j];
				}
			}
		}
		if (ret._mat[i][i] == 0) {
			for (int k = i; k < ret._linesQuan; ++k) {
				if (ret._mat[k][i] != 0) {
					for (size_t j = 0; j < ret._columnsQuan; ++j) {
						ret._mat[i][j] = ret._mat[i][j] - ret._mat[k][j];
					}
					break;
				}
			}
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

void	Matrix::solve() const {
	Matrix	sol;
	std::vector<float>	solution;
	float	sum;
	float	val;

	std::cout << "-----" << std::endl;
	if (this->findDet() == 0) {
		std::cout << "No solution" << std::endl;
		return;
	}
	sol = this->triangle();
	solution.resize(sol._linesQuan);
	for (int i = solution.size() - 1; i >= 0 ; --i) {
		sum = 0;
		for (int j = i + 1; j < sol._linesQuan - 1; ++j) {
			sum += sol[i][j];
		}
		val = (sol[i][sol._columnsQuan - 1] - sum) / sol[i][i];
		solution[i] = val;
	}

	for (size_t i = 0; i < solution.size(); ++i) {
		std::cout << solution[i] << std::endl;
	}
}