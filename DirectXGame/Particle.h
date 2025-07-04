#pragma once
#include<KamataEngine.h>
#include "Model2.h"
using namespace KamataEngine;
//パーティクル
class Particle 
{
public:
	//初期化
	void Initialize(Model2*model);
	//更新
	void Update();
	//描画
	void Draw(Camera& camera);
	
private://メンバ変数（アンダーバーがついてるやつが引数として受け取ったデータをメンバ変数に記録する事ができる）
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model2* model_ = nullptr;
};
