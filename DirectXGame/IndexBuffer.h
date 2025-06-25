#pragma once
#include<d3d12.h>

class IndexBuffer {
public:

	void Create(const UINT size, const UINT stride);
	// ゲッター
	ID3D12Resource* Get();               // 頂点バッファ
	D3D12_INDEX_BUFFER_VIEW* GetView(); // 頂点バッファービュー
	// コンストラクタ
	IndexBuffer();
	// デストラクタ
	~IndexBuffer();

private:
	ID3D12Resource* indexBuffer_ = nullptr;      // インデックスバッファ
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{}; // インデックスバッファビュー
};
