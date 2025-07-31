#pragma once
#include <2d/Sprite.h>
#include <KamataEngine.h>

class Gauge {

public:
	Gauge();

	~Gauge();

	void Initialize();

	void Update();

	void Draw();

private:
	std::vector<KamataEngine::Sprite*> GaugeSprite_;

	uint32_t textureHandle_;

	int red = 0;
	int Green = 1;

	const int maxHP = 2;
	const KamataEngine::Vector2 startPos = {50, 50}; // 左上の開始位置
	const KamataEngine::Vector2 size = {100, 20};    // 各ゲージのサイズ
};