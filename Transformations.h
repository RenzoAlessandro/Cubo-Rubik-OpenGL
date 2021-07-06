#pragma once
#include <iostream>
#include <math.h>
#include <iomanip>

#define PI 3.14159265


namespace sco {



	class Vector4 {
		float vec[4];
	public:
		Vector4() {
			vec[0] = vec[1] = vec[2] = 0;
			vec[3] = 1;
		}


		Vector4(float x, float y, float z) {
			vec[0] = x;
			vec[1] = y;
			vec[2] = z;
			vec[3] = 1;
		}


		void operator()(int i, float n) {
			vec[i] = n;
		}

		float operator[](int i) {
			return vec[i];
		}

		void operator=(Vector4 v2) {
			for (int i = 0; i < 4; i++) vec[i] = v2[i];
		}
	};


	class Matrix {
	protected:
		float mat[4][4];
	public:
		Matrix() {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					mat[i][j] = (i == j) ? 1 : 0;
				}
			}
		}

		Vector4 operator*(Vector4 v) {
			Vector4 result;
			for (int i = 0; i < 4; i++) {
				float aux = 0;
				for (int j = 0; j < 4; j++) {
					aux += mat[i][j] * v[j];
				}
				result(i, aux);
			}

			return result;
		}

		Matrix operator*(Matrix m) {
			Matrix Result;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					float aux = 0;
					for (int k = 0; k < 4; k++) {
						aux += (mat[i][k] * m(k, j));
					}
					Result.mat[i][j] = aux;
				}
			}
			return Result;
		}

		void operator=(Matrix m) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					mat[i][j] = m(i, j);
				}
			}
		}

		void print() {
			std::cout << std::fixed << std::setprecision(3) << std::setfill('0');
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					std::cout << mat[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
		float operator()(int i, int j) { return mat[i][j]; }

		virtual void setX(float x) { return; };
		virtual void setY(float y) { return; };
		virtual void setAngle(double angle) { return; }

	};

	class TraslationMatrix :public Matrix {
	public:
		TraslationMatrix(float x, float y, float z) {
			Matrix();
			mat[0][3] = x;
			mat[1][3] = y;
			mat[2][3] = z;
		}

		void setX(float x) { mat[0][3] = x; }
		void setY(float y) { mat[1][3] = y; }
		void setAngle(double angle) { return; }
	};

	class ScaleMatrix : public Matrix {
	public:
		ScaleMatrix(float sx, float sy, float sz) {
			Matrix();
			mat[0][0] = sx;
			mat[1][1] = sy;
			mat[2][2] = sz;
		}

		void setX(float x) { mat[0][0] = 1.f + x; }
		void setY(float y) { mat[1][1] = 1.f + y; }
		void setAngle(double angle) { return; }
	};


	class mirrorYZMatrix :public Matrix {
	public:
		mirrorYZMatrix() {
			Matrix();
			mat[0][0] = -1;
		}

		void setX(float x) { return; }
		void setY(float y) { return; }
		void setAngle(double angle) { return; }

	};

	class rotateZMatrix :public Matrix {
	public:
		rotateZMatrix(double angle) {
			angle = (angle * PI) / 180; // A radianes
			mat[0][0] = (float)cos(angle);
			mat[0][1] = (float)(-sin(angle));
			mat[1][0] = -mat[0][1];
			mat[1][1] = mat[0][0];
		}
		void setX(float x) { return; }
		void setY(float y) { return; }
		void setAngle(double angle) {
			mat[0][0] = (float)cos(angle);
			mat[0][1] = (float)(-sin(angle));
			mat[1][0] = -mat[0][1];
			mat[1][1] = mat[0][0];
		}
	};

	class rotateYMatrix :public Matrix {
	public:
		rotateYMatrix(double angle) {
			angle = angle * PI / 180.0;
			//std::cout << "Angulo: " << angle << std::endl;
			mat[0][0] = (float)cos(angle);
			mat[0][2] = (float)sin(angle);
			mat[2][0] = -mat[0][2];
			mat[2][2] = mat[0][0];
		}
		void setX(float x) { return; }
		void setY(float y) { return; }
		void setAngle(double angle) {
			angle = angle * PI / 180.0;
			mat[0][0] = (float)cos(angle);
			mat[0][2] = (float)sin(angle);
			mat[2][0] = -mat[0][2];
			mat[2][2] = mat[0][0];
		}
	};

	class rotateXMatrix :public Matrix {
	public:
		rotateXMatrix(double angle) {
			angle = (angle * PI) / 180.0;
			mat[1][1] = (float)cos(angle);
			mat[1][2] = (float)(-sin(angle));
			mat[2][1] = -mat[1][2];
			mat[2][2] = mat[1][1];
		}
		void setX(float x) { return; }
		void setY(float y) { return; }
		void setAngle(double angle) {
			angle = angle * PI / 180.0;
			mat[1][1] = (float)cos(angle);
			mat[1][2] = (float)(-sin(angle));
			mat[2][1] = -mat[1][2];
			mat[2][2] = mat[1][1];
		}
	};
}