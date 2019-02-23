#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>

#include "Vertex.h"

/* Implement the matrix 4 x 4 */
class Matrix {
private:
	int rows_, cols_;
	float **p;

	void allocSpace();

public:
	int rows = rows_, cols = cols_;

	Matrix(int, int);
	Matrix();
	~Matrix();
	Matrix(const Matrix&);

	/* Set number at m[x][y] */
	inline float& operator()(int x, int y) { return p[x][y]; }
	//inline float getValueAt(int x, int y) { return (x, y);}

	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(float);
	Matrix& operator/=(float);

	Matrix transpose();
	static Matrix createIdentity(int);
	static Matrix rotateX(float);
	static Matrix rotateY(float);
	static Matrix rotateZ(float);
	static Matrix my_translate(float, float, float);
	static Matrix my_perspective(float, float, float, float);
	static Matrix my_frustum(float, float, float);

	static Matrix setVector4(const Vertex&);
	Matrix& toHomogeneous(void);
	bool inRange(float, float);
	float getValueAt(int, int);
	void print();
};


Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, float);
Matrix operator*(float, const Matrix&);
Matrix operator/(const Matrix&, float);

#endif#pragma once
