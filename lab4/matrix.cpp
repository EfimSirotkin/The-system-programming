#include "matrix.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <cstring>

Matrix::Matrix(std::vector<std::vector<double>> mx) : matrix_(mx)
{
	size_ = mx.size();
}

double Matrix::get_determinant(std::vector<std::vector<double>> mx, int size) const
{
	double determinant = 0;

	if (size == 1) {
		determinant = mx[0][0];
		return determinant;
	}
	else if (size == 2) {
		determinant = (mx[0][0] * mx[1][1]) - (mx[1][0] * mx[0][1]);
		return determinant;
	}
	else if (size > 2) {
		std::vector<std::vector<double>> submx(size, std::vector<double>(size));
		for (int i = 0; i < size; i++) {
			int subi = 0;
			for (int j = 1; j < size; j++) {
				int subj = 0;
				for (int k = 0; k < size; k++) {
					if (k == i) continue;
					submx[subi][subj] = mx[j][k];
					subj++;
				}
				subi++;
			}
			determinant = determinant + (pow(-1, i) * mx[0][i] * get_determinant(submx, size - 1));
		}
	}
	return determinant;
}

void Matrix::get_minor_matrix()
{
	if (size_ == 2) {
		std::vector<std::vector<double>> submx(size_, std::vector<double>(size_));

		for (int i = 0; i < size_; ++i) {
			for (int j = 0; j < size_; ++j) {
				submx[i][j] = matrix_[size_ - i - 1][size_ - j - 1];
			}
		}
		matrix_ = submx;
	}
	else if (size_ > 2) {
		std::vector<std::vector<double>> submx(size_, std::vector<double>(size_));
		std::vector<std::vector<double>> mnrmx(size_ - 1, std::vector<double>(size_ - 1));

		for (int i = 0; i < size_; ++i) {
			for (int j = 0; j < size_; ++j) {
				for (int r = 0, mnr_row = 0; r < size_; ++r, ++mnr_row) {
					if (r == i) {
						--mnr_row;
						continue;
					}
					for (int c = 0, mnr_col = 0; c < size_; ++c, ++mnr_col) {
						if (c == j) {
							--mnr_col;
							continue;
						}
						mnrmx[mnr_row][mnr_col] = matrix_[r][c];
					}
				}
				submx[i][j] = get_determinant(mnrmx, size_ - 1);
			}
		}
		matrix_ = submx;
	}
	return;
}

void Matrix::get_add_matrix()
{
	if (size_ > 1) {
		for (int i = 0; i < size_; ++i) {
			for (int j = 0; j < size_; ++j) {
				matrix_[i][j] = matrix_[i][j] * pow(-1, i + j);
			}
		}
	}
	return;
}

void Matrix::get_transpose_matrix()
{
	double temp;
	for (int i = 0; i < size_; ++i) {
		for (int j = i; j < size_; ++j) {
			temp = matrix_[i][j];
			matrix_[i][j] = matrix_[j][i];
			matrix_[j][i] = temp;
		}
	}
	return;
}

void Matrix::multiply_num_matrix(double determinant)
{
	if(size_ == 1) {
		matrix_[0][0] = 1.0/determinant;
	}
	else {
		for (int i = 0; i < size_; ++i) {
			for (int j = 0; j < size_; ++j) {
				matrix_[i][j] *= 1.0 / determinant;
			}
		}
	}
	return;
}

void Matrix::get_inverse_matrix()
{
	double determinant = this->get_determinant(matrix_, size_);
	if (determinant == 0)
		throw std::logic_error("Determinant of this matrix equal zero!");
	this->get_minor_matrix();
	this->get_add_matrix();
	this->get_transpose_matrix();
	this->multiply_num_matrix(determinant);
	return;
}

void Matrix::print_matrix(std::string msg) const
{
	if (!msg.empty()) {
		std::cout << msg << std::endl;
	}
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			std::cout << std::setw(15) << matrix_[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return;
}

void Matrix::print_inverse_matrix()
{
	
	std::string msg = "Success! Your inverse matrix:";
	try {
		this->get_inverse_matrix();
	}
	catch (std::exception& e) {
		msg = e.what();
	}
	this->print_matrix(msg);
	return;
}
std::string Matrix::get_matrix_as_string(std::string msg){
	std::string temp_str = "";
	if(!msg.empty()) {
		temp_str = msg;
		temp_str += "   ";
	}
	 
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			temp_str += std::to_string(matrix_[i][j]);
			temp_str += "   ";
		}
		temp_str +='\n';
	}
	return temp_str;
}