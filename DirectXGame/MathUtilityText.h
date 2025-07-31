#pragma once
#include <cmath>
#include <math/Matrix4x4.h>
#include <math/Vector3.h>

namespace KamataEngine {

inline Matrix4x4 MakeIdentity() {
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i)
		result.m[i][i] = 1.0f;
	return result;
}

inline Matrix4x4 MakeScale(const Vector3& scale) {
	Matrix4x4 result = MakeIdentity();
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	return result;
}

inline Matrix4x4 MakeTranslation(const Vector3& translation) {
	Matrix4x4 result = MakeIdentity();
	result.m[3][0] = translation.x;
	result.m[3][1] = translation.y;
	result.m[3][2] = translation.z;
	return result;
}

inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.m[row][col] = m1.m[row][0] * m2.m[0][col] + m1.m[row][1] * m2.m[1][col] + m1.m[row][2] * m2.m[2][col] + m1.m[row][3] * m2.m[3][col];
		}
	}

	return result;
}
inline Matrix4x4 MakeRotation(const Vector3& rotation) {
	float cx = cosf(rotation.x), sx = sinf(rotation.x);
	float cy = cosf(rotation.y), sy = sinf(rotation.y);
	float cz = cosf(rotation.z), sz = sinf(rotation.z);

	// 回転行列 X
	Matrix4x4 rotX = MakeIdentity();
	rotX.m[1][1] = cx;
	rotX.m[1][2] = sx;
	rotX.m[2][1] = -sx;
	rotX.m[2][2] = cx;

	// 回転行列 Y
	Matrix4x4 rotY = MakeIdentity();
	rotY.m[0][0] = cy;
	rotY.m[0][2] = -sy;
	rotY.m[2][0] = sy;
	rotY.m[2][2] = cy;

	// 回転行列 Z
	Matrix4x4 rotZ = MakeIdentity();
	rotZ.m[0][0] = cz;
	rotZ.m[0][1] = sz;
	rotZ.m[1][0] = -sz;
	rotZ.m[1][1] = cz;

	// Z * X * Y 順
	return rotZ * rotX * rotY;
}
} // namespace KamataEngine