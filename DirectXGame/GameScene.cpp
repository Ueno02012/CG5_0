#include "GameScene.h"
#include <cmath> // sin関数に必要
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	delete sprite_;
	delete stage_;
}

void GameScene::Initialize() {

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Scene.png");

	// スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
	stage_ = new Stage();
	stage_->Initialize(textureHandle_);

}


void GameScene::Update() 
{
	frameCount++;

	// sin波で上下に揺れるY座標を作る（±10ピクセル範囲で動かす）
	float y = 10 * sin(frameCount * 0.05f);

	// スプライトの位置を更新
	sprite_->SetPosition({0.0f, y});

	stage_->Update();
}

void GameScene::Draw() 
{
	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());
	//スプライトインスタンスの描画処理
		//sprite_->Draw();
	
	stage_->Draw();
	//スプライト描画後処理
	Sprite::PostDraw();
}

