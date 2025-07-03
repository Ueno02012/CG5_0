
#include "Effect.h"
using namespace KamataEngine;
#include <random>
using namespace MathUtility;
#include <cassert>
void Effect::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 pos, KamataEngine::Vector4 color) {
	std::random_device seed_Generator;
	std::mt19937 RandomEngine(seed_Generator());
	std::uniform_real_distribution<float> RandomSize(0.0f, 1.0f);
	std::uniform_real_distribution<float> RandomRotation(-1.0f, 1.0f);
	std::uniform_real_distribution<float> RandomColor(0.0f, 255.0f);
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// Vector3 rotate = Vector3(0.0f, 0.0f, RandomRotation(RandomEngine));
	worldTransform_.scale_.y = RandomSize(RandomEngine) * 10.0f;
	worldTransform_.rotation_.z = RandomRotation(RandomEngine) * 20.0f;
	// worldTransform_.rotation_ = rotate;
	worldTransform_.translation_ = pos;
	// 色の初期化
	objectColor_.Initialize();
	color_ = color;
	// ワールド変換データの初期化
	worldTransform_.Initialize();
}

void Effect::Update() {
	worldTransform_.rotation_.y += moveSpeed_;
	worldTransform_.translation_.x += moveSpeed_;
	worldTransform_.translation_.z += moveSpeed_;

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}

	// 存在時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	worldTransform_.UpdateMatrix();
}

void Effect::Draw(Camera& camera) { model_->Draw(worldTransform_, camera, &objectColor_); }

bool Effect::IsFinished() { return isFinished_; }
