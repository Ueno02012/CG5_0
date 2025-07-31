#include "Stage.h"
using namespace KamataEngine;

Stage::Stage() {}

Stage::~Stage() { 
	delete sprite_;
	delete sprite2_;

}

void Stage::Initialize(uint32_t textureHandle) {
	textureHandle_=textureHandle;

	// スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});//タイトル
	sprite2_ = Sprite::Create(textureHandle_, {1280, 0});//ステージ背景
}

void Stage::Update() 
{
	// スクロール
	Vector2 position=sprite_->GetPosition();
	position.x -= 2;

	if (position.x < -1280)
	{
		position.x += 1280;
	}
	sprite_->SetPosition(position);
	position.x += 1280;
	sprite2_->SetPosition(position);
}

void Stage::Draw() 
{
	sprite_->Draw();
	sprite2_->Draw();
}
