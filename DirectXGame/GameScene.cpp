#include "GameScene.h"
#include <cmath> // sin関数に必要
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	delete sprite_;
}

void GameScene::Initialize() {

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Title.png");

	// スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	sprite_->SetSize({920.0f, 200.0f});
}

// メンバー変数に追加
int frameCount = 0;

void GameScene::Update() 
{
	//スプライトの今の座標を取得
	//Vector2 position = sprite_->GetPosition();
	////座標を｛２，１｝移動
	//position.x += 2.0f;
	//position.y += 1.0f;
	////移動した座標をスプライトに反映
	//sprite_->SetPosition(position);
	frameCount++;

	// sin波で上下に揺れるY座標を作る（±10ピクセル範囲で動かす）
	float y = 10 * sin(frameCount * 0.05f);

	// スプライトの位置を更新
	sprite_->SetPosition({220.0f, y+100});
}

void GameScene::Draw() 
{
	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());
	//スプライトインスタンスの描画処理
		sprite_->Draw();
	

	//スプライト描画後処理
	Sprite::PostDraw();
}

