#include <Windows.h>
#include "KamataEngine.h"
#include <cassert>
#include <d3dcompiler.h>
#include "Shader.h"
#include"RootSignature.h"
#include"PipelineState.h"
#include"VertexBuffer.h"
using namespace KamataEngine;

void SetupPipelineState(PipelineState& pipelineState, RootSignature& rs, Shader& vs, Shader& ps) {
	// InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[1] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// BlendState(今回は不透明)
	D3D12_BLEND_DESC blendDesc{};
	// 全ての色要素を書き込む
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	// RasterizerState
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	// 裏面(反時計回り)をカリングする
	rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	// 塗りつぶしモードをソリッドにする(ワイヤーフレームならD3D12_FILE_MODE_WIREFRAME)
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	// PSO(PipelineStateObject)の生成
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPiplineStateDesc{};
	graphicsPiplineStateDesc.pRootSignature = rs.Get();                                                    // RootSignature
	graphicsPiplineStateDesc.InputLayout = inputLayoutDesc;                                                // InputLayout
	graphicsPiplineStateDesc.VS = {vs.GetDxcBlob()->GetBufferPointer(), vs.GetDxcBlob()->GetBufferSize()}; // VertexShader
	graphicsPiplineStateDesc.PS = {ps.GetDxcBlob()->GetBufferPointer(), ps.GetDxcBlob()->GetBufferSize()}; // PixelShader
	graphicsPiplineStateDesc.BlendState = blendDesc;                                                       // BlendState
	graphicsPiplineStateDesc.RasterizerState = rasterizerDesc;                                             // RasterizerState

	// 書き込むRTVの情報
	graphicsPiplineStateDesc.NumRenderTargets = 1; // 1つのRTVに書き込む　※２つ同時にしようと思えば出来る
	graphicsPiplineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	// 利用するトポロジ(形状)のタイプ。三角形
	graphicsPiplineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	// どのように画面に色を打ち込むかの設定（今気にしなくていい）
	graphicsPiplineStateDesc.SampleDesc.Count = 1;
	graphicsPiplineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	// 準備は整った。PSOを生成する
	pipelineState.Create(graphicsPiplineStateDesc);
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	KamataEngine::Initialize(L"LE3D_02_ウエノ_ユウキ");
	
	// DirectXCommonのインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	
	// DirectXCommonクラスが取得している、ウィンドウの幅と高さの値の取得
	int32_t w = dxCommon->GetBackBufferWidth();
	int32_t h = dxCommon->GetBackBufferHeight();
	DebugText::GetInstance()->ConsolePrintf(
		std::format("width: {},height: {}\n", w, h).c_str());
	
	// DirectXCommonクラスが管理している、コマンドリストの取得
	
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList(); 
	
	//-----------------RootSignatureの作成-----------------//
	RootSignature rs;
	rs.Create();
	
	//------------------VertexShaderをCompileする------------------//
	// コンパイル済みのShader、エラー時情報の格納場所の用意
	ID3DBlob* errorBlob = nullptr; //エラーオブジェクト
	
	//　頂点シェーダの読み込みとコンパイル
	Shader vs;
	vs.LoadDxc(L"Resources/shaders/TestVS.hlsl", L"vs_6_0"); // 変更
	assert(vs.GetDxcBlob() != nullptr); 
	 
	//------------------PixelShaderをCompileする------------------//
	// ピクセルシェーダの読み込みとコンパイル
	Shader ps;
	ps.LoadDxc(L"Resources/shaders/TestPS.hlsl", L"ps_6_0"); // 変更
	assert(ps.GetDxcBlob() != nullptr);                      
	//------------------PSOの生成------------------//
	PipelineState pipelineState;
	SetupPipelineState(pipelineState, rs, vs, ps);
	
	//------------------VertexResourceを生成する------------------//
	VertexBuffer vb;
	vb.Create(sizeof(Vector4) * 3, sizeof(Vector4));
	
	//------------------頂点リソースにデータを書き込む------------------//
	// 頂点リソースにデータを書き込む
	Vector4* vertexData = nullptr;
	vb.Get()->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	vertexData[0] = {-0.5f, -0.5f, 0.0f, 1.0f}; // 左下
	vertexData[1] = {0.0f, 0.5f, 0.0f, 1.0f};   // 上
	vertexData[2] = {0.5f, -0.5f, 0.0f, 1.0f};  // 右下
	// 頂点リソースのマップを解除する
	vb.Get()->Unmap(0, nullptr);
	
	// メインループ
	while (true) {
		//エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}
		//-------------------------- 描画
		// 描画開始
		dxCommon->PreDraw();
	
		// コマンドを読む
		commandList->SetGraphicsRootSignature(rs.Get());     // RootSignatureの設定
		commandList->SetPipelineState(pipelineState.Get());  // PSOの設定をする
		commandList->IASetVertexBuffers(0, 1, vb.GetView()); // VBVの設定をする	// トポロジの設定
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// 頂点数、インデックス数、インデックスの開始位置、インデックスのオフセット
		commandList->DrawInstanced(3, 1, 0, 0);
	
		// 描画終了
		dxCommon->PostDraw();
	}
	// 解放処理
	if (errorBlob) {
		errorBlob->Release();
	}
	//エンジンの終了処理
	KamataEngine::Finalize();
	
	return 0;
}

