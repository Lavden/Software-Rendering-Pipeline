#include <stdexcept>
#include <math.h>

#include "globals.h"
#include "Matrix.h"

/* Public Member Function*/
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
	allocSpace();
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] = 0;
		}
	}
}

Matrix::Matrix() : rows_(1), cols_(1) {
	allocSpace();
	p[0][0] = 1;
}

Matrix::~Matrix() {
	for (int i = 0; i < rows_; ++i) {
		delete[] p[i];
	}
	delete p;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_) {
	allocSpace();
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] = m.p[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (this == &m)
		return *this;

	if (rows_ != m.rows_ || cols_ != m.cols_) {
		for (int i = 0; i < rows_; ++i) {
			delete[] p[i];
		}
		delete[] p;

		rows_ = m.rows_;
		cols_ = m.cols_;
		allocSpace();
	}

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] = m.p[i][j];
		}
	}
	return *this;
}


Matrix& Matrix::operator+=(const Matrix& m) {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] += m.p[i][j];
		}
	}
	return *this;
}

Matrix&Matrix::operator-=(const Matrix& m) {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] -= m.p[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	Matrix temp(rows_, m.cols_);

	for (int i = 0; i < temp.rows_; ++i) {
		for (int j = 0; j < temp.cols_; ++j) {
			for (int k = 0; k < cols_; ++k) {
				temp.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	return (*this = temp);
}

Matrix& Matrix::operator*=(float num) {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] *= num;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(float num) {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			p[i][j] /= num;
		}
	}
	return *this;
}

Matrix Matrix::transpose() {
	Matrix ret(cols_, rows_);
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			ret.p[j][i] = p[i][j];
		}
	}
	return ret;
}


/* Static Class function*/
Matrix Matrix::createIdentity(int size)
{
	Matrix temp(size, size);
	for (int i = 0; i < temp.rows_; ++i) {
		for (int j = 0; j < temp.cols_; ++j) {
			if (i == j) {
				temp.p[i][j] = 1;
			}
			else {
				temp.p[i][j] = 0;
			}
		}
	}
	return temp;
}

Matrix Matrix::rotateX(float angle) {
	Matrix temp(4, 4);
	float sin_angle = sin(angle * MY_PI / 180);
	float cos_angle = cos(angle * MY_PI / 180);

	/* R_x(angle) =
		1	0	  0
		0  cos   -sin
		0  sin  cos
	*/
	temp(0, 0) = 1;
	temp(1, 1) = cos_angle;
	temp(1, 2) = -sin_angle;
	temp(2, 1) = sin_angle;
	temp(2, 2) = cos_angle;
	temp(3, 3) = 1;

	return temp;
}

Matrix Matrix::rotateY(float angle) {
	Matrix temp(4, 4);
	float sin_angle = sin(angle * MY_PI / 180);
	float cos_angle = cos(angle * MY_PI / 180);

	/* R_y(angle) =
		cos	 0  sin
		 0   1	 0
		-sin  0  cos
	*/
	temp(0, 0) = cos_angle;
	temp(0, 2) = sin_angle;
	temp(1, 1) = 1;
	temp(2, 0) = -sin_angle;
	temp(2, 2) = cos_angle;
	temp(3, 3) = 1;

	return temp;
}
Matrix Matrix::rotateZ(float angle) {
	Matrix temp(4, 4);
	float sin_angle = sin(angle * MY_PI / 180);
	float cos_angle = cos(angle * MY_PI / 180);

	/* R_z(angle) =
		cos	 -sin  0
		sin  cos  0
		0     0   1
	*/
	temp(0, 0) = cos_angle;
	temp(0, 1) = -sin_angle;
	temp(1, 0) = sin_angle;
	temp(1, 1) = cos_angle;
	temp(2, 2) = 1;
	temp(3, 3) = 1;

	return temp;
}

Matrix Matrix::my_translate(float x, float y, float z) {
	/* In OpenGL Tanslatef Matrix =
		1	0	0	x
		0	1	0	y
		0	0	1	z
		0	0	0	1
	*/
	Matrix temp(4, 4);
	temp(0, 0) = 1;
	temp(1, 1) = 1;
	temp(2, 2) = 1;
	temp(3, 3) = 1;

	temp(0, 3) = x;
	temp(1, 3) = y;
	temp(2, 3) = z;
	//temp(3, 0) = x;
	//temp(3, 1) = y;
	//temp(3, 2) = z;
	return temp;
}

Matrix Matrix::my_perspective(float eye_fov, float aspect_ratio, float z_near, float z_far) {
	/*
	f = 1 / tan(eye_fov / 2)
	In OpenGL Perspective Matrix =
		1/(tan(eye_fov / 2))	0	0	0
		0	1/(tan(eye_fov / 2))	0	0
		0	0	(near+far)/(near-far)	(2*far * near)/(near-far)
		0	0	-1  0
	*/
	Matrix temp(4, 4);
	float tan_angle = tan(eye_fov * MY_PI / 360);
	
	if (tan_angle == 0) {
		temp(0, 0) = 1;
		temp(1, 1) = 1;
		temp(2, 2) = 1;
		temp(3, 3) = 1;
	}
	else {
		temp(0, 0) = 1 / (tan_angle * aspect_ratio);
		temp(1, 1) = 1 / tan_angle;
		temp(2, 2) = (z_near + z_far) / (z_near - z_far);
		temp(2, 3) = (2 * z_far*z_near) / (z_near - z_far);
		temp(3, 2) = -1;
		//temp(2, 3) = -1;
		//temp(3, 2) = (2 * z_far*z_near) / (z_near - z_far);
	}
	return temp;
}

Matrix Matrix::my_frustum(float near, float far, float eye_fovy) {
	/* OpenGl perspective projection matrix
		2n/(r-l)	0	(r+l)/(r-l)		0
			0	2n/(t-b) (t+b)/(t-b)	0
			0		0	-(f+n)/(f-n)	-2fn/(f-n)
			0		0		-1			0
	*/
	Matrix temp(4, 4);

	float left, right, bottom, top;
	top = tan(eye_fovy * MY_PI / 360) * near;
	right = top;
	left = -top;
	bottom = -top;

	if (top == 0) {
		temp(0, 0) = 1;
		temp(1, 1) = 1;
		temp(2, 2) = 1;
		temp(3, 3) = 1;
	}
	else {
		temp(0, 0) = 2 * near / (right - left);
		temp(0, 2) = (right + left) / (right - left);
		temp(1, 1) = 2 * near / (top - bottom);
		temp(1, 2) = (top + bottom) / (top - bottom);
		temp(2, 2) = -(far + near) / (far - near);
		temp(2, 3) = -2 * far*near / (far - near);
		temp(3, 3) = -1;
	}

	return temp;
}

Matrix Matrix::setVector4(const Vertex& m) {
	Matrix temp = Matrix(4, 1);

	temp(0, 0) = m.x;
	temp(1, 0) = m.y;
	temp(2, 0) = m.z;
	temp(3, 0) = m.w;

	return temp;
}

/* Test if coordinates of vertor(x,y,z) in range [-1, 1]
	P[0][0] -> X, P[1][0] -> Y, P[2][0] -> Z, P[3][0] -> W
*/
bool Matrix::inRange(float min, float max) {
	if (p[0][0] < min || p[0][0] > max ||
		p[1][0] < min || p[1][0] > max ||
		p[2][0] < min || p[2][0] > max)
		return false;
	return true;
}

float Matrix::getValueAt(int i, int j) {
	return p[i][j];
}

Matrix& Matrix::toHomogeneous(void) {
	if (p[3][0] != 0) {
		p[0][0] = p[0][0] / p[3][0];
		p[1][0] = p[1][0] / p[3][0];
		p[2][0] = p[2][0] / p[3][0];
		p[3][0] = p[3][0] / p[3][0];
	}
	return *this;
}



/* for debugging */
void Matrix::print() {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			printf("%f ", p[i][j]);
		}
		printf("\n");
	}
}

/* Private helper function*/
void Matrix::allocSpace()
{
	p = new float*[rows_];
	for (int i = 0; i < rows_; ++i) {
		p[i] = new float[cols_];
	}
}

/* Non-Member Functions */
Matrix operator+(const Matrix& m1, Matrix& m2) {
	Matrix temp(m1);
	return (temp += m2);
}

Matrix operator-(const Matrix& m1, Matrix& m2) {
	Matrix temp(m1);
	return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
	Matrix temp(m1);
	return (temp *= m2);
}

Matrix operator*(const Matrix& m, float num) {
	Matrix temp(m);
	return (temp *= num);
}

Matrix operator*(float num, const Matrix& m) {
	return (m * num);
}

Matrix operator/(const Matrix& m, float num) {
	Matrix temp(m);
	return (temp /= num);
}
