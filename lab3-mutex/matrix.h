#include <vector>
#include <string>
#include <windows.h>

class Matrix
{
public:
	Matrix() {};
	Matrix(std::vector<std::vector<double>> matrix);
	double get_determinant(std::vector<std::vector<double>> mx, int size) const;
	void get_minor_matrix();
	void get_add_matrix();
	void get_transpose_matrix();
	void multiply_num_matrix(double determinant);
	void get_inverse_matrix();
	void print_matrix(std::string msg = "") const;
	void print_inverse_matrix();
	std::string get_matrix_as_string(std::string msg);
private:
	std::vector<std::vector<double>> matrix_;
	int size_;
};

