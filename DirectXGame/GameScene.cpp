#include "GameScene.h"
#include <cmath> // sin関数に必要
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	delete sprite_;
	delete stage_;
	delete modelPlayer_;
	delete player_;
	delete gauge_;
	delete camera_;
	delete number_;
}

void GameScene::Initialize() {

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Stage.png");
	// スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});//タイトル

	//ステージ背景
	stage_ = new Stage();
	stage_->Initialize(textureHandle_);
	

	// カメラ生成・初期化
	camera_ = new Camera();
	camera_->Initialize();


	modelPlayer_ = Model::CreateFromOBJ("player", true);
	player_ = new Player();
	player_->Initialize(modelPlayer_, camera_, {0, 0, 0});

	//ゲージ
	gauge_ = new Gauge();
	gauge_->Initialize();

	//数値
	number_ = new Number();
	number_->Initialize();
}

// メンバー変数に追加
int frameCount = 0;



void GameScene::Update() {
	
	player_->Update();

	frameCount++;

	// sin波で上下に揺れるY座標を作る（±10ピクセル範囲で動かす）
	float y = 10 * sin(frameCount * 0.05f);

	// スプライトの位置を更新
	sprite_->SetPosition({0.0f, y});

	stage_->Update();
	
	gauge_->Update();

	number_->Update();
}

void GameScene::Draw() 
{
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	// スプライト描画前処理(背景)
	Sprite::PreDraw(dxCommon->GetCommandList());

	
	// スプライトインスタンスの描画処理
	
	sprite_->Draw();
	
	stage_->Draw();

	// スプライト描画後処理(背景)
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	
	player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();

	// スプライト描画前処理(2D近景)
	Sprite::PreDraw(dxCommon->GetCommandList());

	//ゲージ
	gauge_->Draw();

	//数値
	number_->Draw();

	// スプライト描画後処理(背景)
	Sprite::PostDraw();
}
