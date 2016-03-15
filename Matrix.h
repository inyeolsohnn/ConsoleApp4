#pragma once
#include <iostream>
namespace Moo {
	class Matrix
	{
	public:
		Matrix();
		Matrix(Matrix&& src) {
			std::cout << "move constructor" << std::endl;
			rowCount = src.rowCount;
			colCount = src.colCount;
			values = src.values;

			src.rowCount = 0;
			src.colCount = 0;
			src.values = nullptr;
		}
		Matrix(const Matrix& copyMat) :rowCount(copyMat.rowCount), colCount(copyMat.colCount){
			std::cout << "copy operator" << std::endl;
			values = new float*[rowCount];
			for (int i = 0; i < rowCount; i++) {
				values[i] = new float[colCount];
			}
			for (int i = 0; i < rowCount; i++) {
				for (int j = 0; j < colCount; j++) {
					values[i][j] = copyMat.values[i][j];
				}
			}
		}
		Matrix(int x, int y) :rowCount(y), colCount(x)
		{
			values = new float*[y];
			for (int i = 0; i < y; i++) {
				values[i] = new float[x];
			}
			for (int i = 0; i < rowCount; i++) {
				for (int j = 0; j < colCount; j++) {
					values[i][j] = 0.0f;
				}
			}
		}
		~Matrix() {
			for (int i = 0; i < rowCount; i++) {
				delete[] values[i];
			}
			delete[] values;
		}
		Matrix& operator=(Matrix&& src) {
			std::cout << "move assignment operator" << std::endl;
			if (this == &src) {
				return *this;
			}
			else {
				for (int i = 0; i < rowCount; i++) {
					delete[] values[i];
				}
				delete[] values;
				values = nullptr;
				rowCount = src.rowCount;
				colCount = src.colCount;
				values = src.values;

				src.rowCount = 0;
				src.colCount = 0;
				src.values = nullptr;
				return *this;
			}
		}
		Matrix& operator=(const Matrix& rhs) {
			std::cout << "assignment operator" << std::endl;
			if (this == &rhs) {
				return *this;
			}
			else {
				for (int i = 0; i < rowCount; i++) {
					delete[] values[i];
				}
				delete[] values;
				values = nullptr;
				rowCount = rhs.rowCount;
				colCount = rhs.colCount;
				values = new float*[rowCount];
				for (int i = 0; i < rowCount; i++) {
					values[i] = new float[colCount];
				}
				for (int i = 0; i < rowCount; i++) {
					for (int j = 0; j < colCount; j++) {
						values[i][j] = rhs.values[i][j];
					}
				}
				return *this;
			}
		}

		Matrix operator *(const Matrix& mat) {
			//this*mat
			//check row column count
			if (colCount == mat.rowCount) {
				//carry out the operation
				Matrix resultMat(mat.colCount, this->rowCount);
				for (int r = 0; r < resultMat.rowCount; r++) {
					for (int c = 0; c < resultMat.colCount; c++) {
						float temp = 0.0f;
						for (int leftC = 0; leftC < colCount; leftC++) {
							for (int rightR = 0; rightR < mat.rowCount; rightR++) {
								
								temp += values[r][leftC] * mat.values[rightR][c];
								
							}
						}
						std::cout << "row :"<<r <<", col : "<< c<<", temp : " << temp << std::endl;;
						resultMat.values[r][c] = temp;
					
					}
				}
				return resultMat;
			}
			else {
				//don't carry out the operation
				//throw exception;
				std::cout << "mat * operation error" << std::endl;
				return Matrix(0,0);
			}
		}


		void print() {
			for (int i = 0; i < rowCount; i++) {
				for (int j = 0; j < colCount; j++) {
					std::cout << this->values[i][j]<<" ";
				}
				std::cout << std::endl;
			}
		}
	private:


	public:
		float** values;
		int colCount;
		int rowCount;
	private:
		
	};
}
