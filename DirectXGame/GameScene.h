#pragma once
#include"KamataEngine.h"
#include "Stage.h"
#include "Player.h"
#include"Gauge.h"
class GameScene 
{
public:
	/// コンストクラタ
	/// </summary>
	GameScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();
	//初期化
	void Initialize();
	//更新
	void Update();

	//描画
	void Draw();
private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//スプライト(背景)
	KamataEngine::Sprite* sprite_ = nullptr;

	//ステージ
	Stage* stage_ = nullptr;

	// プレイヤーモデル
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelPlayer_ = nullptr;

	// プレイヤーの生成
	Player* player_ = nullptr;

	// ビュープロジェクション生成
	KamataEngine::Camera* camera_ = nullptr;

	//ゲージ
	Gauge* gauge_ = nullptr;
	// メンバー変数に追加
	int frameCount = 0;
};
