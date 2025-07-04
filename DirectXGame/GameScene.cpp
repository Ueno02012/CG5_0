#include "GameScene.h"

using namespace KamataEngine;

//デストラクタ
GameScene::~GameScene() {
	// 3Dモデルデータの開放
	delete modelParticle_;

	// パーティクルの開放
	delete particle_;

	// 四角形
	Model2::StaticFinalize();
}

//初期化
void GameScene::Initialize() 
{
	// 3Dモデルデータの生成
	modelParticle_ = Model2::CreateSquare();
	
	//カメラの初期化
	camera_.Initialize();

	//四角形の初期化
	Model2::StaticInitialize();

	// パーティクルの生成
	particle_ = new Particle();
	// パーティクルの初期化
	particle_->Initialize(modelParticle_);
}
//更新
void GameScene::Update() 
{
	// パーティクルの更新
	particle_->Update();
}

//描画
void GameScene::Draw() 
{
	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//3Dモデル描画前処理
	Model2::PreDraw(dxCommon->GetCommandList());
	// パーティクルの描画
	particle_->Draw(camera_);
	//3Dモデル描画後処理
	Model2::PostDraw();
}