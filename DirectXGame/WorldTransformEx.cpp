#include<KamataEngine.h>
#include "MathUtilityText.h"

using namespace KamataEngine;

void WorldTransform::UpdateMatrix() {
	Matrix4x4 matScale = MakeScale(scale_);
	Matrix4x4 matRot = MakeRotation(rotation_);
	Matrix4x4 matTrans = MakeTranslation(translation_);

	matWorld_ = matScale * matRot * matTrans;

	if (parent_) {
		matWorld_ = matWorld_ * parent_->matWorld_;
	}

	TransferMatrix();
}
