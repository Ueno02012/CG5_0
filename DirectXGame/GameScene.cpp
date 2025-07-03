#include "GameScene.h"
using namespace KamataEngine;

#include <random>

std::random_device seed_Generator;
std::mt19937 RandomEngine(seed_Generator());
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
std::uniform_real_distribution<float> RandomFloat(-1.0f, 1.0f);

GameScene::GameScene() {}
GameScene::~GameScene() {

	//// パーティクル3Dモデルデータの解放
	// delete modelParticle_;
	// modelParticle_ = nullptr;
	//  カメラの解放

	// エフェクトの解放
	for (Effect* effect : effectes_) {
		delete effect;
		effect = nullptr;
	}

	delete modelEffect_;
	modelEffect_ = nullptr;
}

void GameScene::Initialize() {
	// DirectXCommonインスタンスの取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンスの取得
	input_ = Input::GetInstance();
	// Audioインスタンスの取得
	audio_ = Audio::GetInstance();

	// 乱数の初期化
	// srand((unsigned)time(NULL));

	// Vector3 size = Vector3(0.0f, 0.0f/*RandomSize(RandomEngine)*/, 0.0f);
	// Vector3 rotate = Vector3(0.0f, 0.0f, 0.0f/*RandomRotation(RandomEngine)*/);

	//// モデルの初期化
	// modelParticle_ = Model::CreateSphere(4, 4);
	//  モデルの初期化
	// modelEffect_->Create();
	modelEffect_ = Model::CreateFromOBJ("Plane");

	// エフェクトの生成
	// modelEffect_=Model::CreateSphere(4, 4);
	// effect_ = new Effect();
	// effect_->Initialize(modelEffect_,pos);

	// カメラの初期化
	camera_.Initialize();

	// 乱数の初期化
	srand((unsigned)time(NULL));
}

void GameScene::Update() {
	if (rand() % 20 == 0) {
		Vector3 pos = Vector3(RandomFloat(RandomEngine) * 30.0f, RandomFloat(RandomEngine) * 20.0f, 0);
		Vector4 color = Vector4(distribution(RandomEngine), distribution(RandomEngine), distribution(RandomEngine), 1.0f);
		EffectBorn(pos, color);
	}

	for (Effect* effect : effectes_) {
		effect->Update();
	}
	// 終了フラグが立ったエフェクトを削除
	effectes_.remove_if([](Effect* effect) {
		if (effect->IsFinished()) {
			delete effect;
			return true;
		}
		return false;
	});
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (Effect* effect : effectes_) {
		effect->Draw(camera_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::EffectBorn(Vector3 pos, Vector4 color) {
	for (int i = 0; i < 10; i++) {
		// 生成
		Effect* effect = new Effect();
		//// 位置
		// Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
		//  初期化
		effect->Initialize(modelEffect_, pos, color);
		// リストに追加
		effectes_.push_back(effect);
	}
}