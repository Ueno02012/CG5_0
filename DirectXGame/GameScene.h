#pragma once
#include"KamataEngine.h"
#include"Particle.h"
#include "Model2.h"
using namespace KamataEngine;
class GameScene 
{
public:
	//初期化
	void Initialize();
	//更新
	void Update();

	//描画
	void Draw();
	
	//デストラクタ
	~GameScene();

	//カメラ
	Camera camera_;

private:
	// パーティクル3Dモデルデータ
	Model2* modelParticle_ = nullptr;
	// パーティクル
	Particle* particle_ = nullptr;
};
