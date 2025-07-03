#include <Windows.h>
#include <KamataEngine.h>
#include"GameScene.h"
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
KamataEngine::Initialize(L"LE3D_02_ウエノ_ユウキ");

// DirectXCommonのインスタンスの取得
DirectXCommon* dxcommon = DirectXCommon::GetInstance();

GameScene* gamescene = new GameScene();
gamescene->Initialize();
	//メインループ
while (true) {
	//エンジンの更新
	if (KamataEngine::Update()) {
		break;
	}
	gamescene->Update();
	//描画開始
	dxcommon->PreDraw();
	
	gamescene->Draw();

	dxcommon->PostDraw();
}

delete gamescene;
//エンジンの終了処理
KamataEngine::Finalize();

	return 0;
}

