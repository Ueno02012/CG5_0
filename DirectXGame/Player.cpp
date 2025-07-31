#include "Player.h"
#include <input/Input.h>
using namespace KamataEngine;

Player::Player() {}

Player::~Player() 
{
	delete model_;
}

//初期化
void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) 
{
	// Nullポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position; // 初期配置
}

// 更新
void Player::Update() 
{
	const float speed = 1.0f;

	// 入力取得
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_W)) {
		worldTransform_.translation_.y += speed;
	}
	if (input->PushKey(DIK_S)) {
		worldTransform_.translation_.y -= speed;
	}
	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= speed;
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x += speed;
	}

	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	worldTransform_.rotation_ = {0, 90, 0};
	// ワールド変換を更新
	worldTransform_.UpdateMatrix();
}

//描画
void Player::Draw() 
{
	 model_->Draw(worldTransform_, *camera_);
}
