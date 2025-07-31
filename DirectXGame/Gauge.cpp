#include "Gauge.h"

using namespace KamataEngine;

Gauge::Gauge() {}

Gauge::~Gauge() { 
	for (auto sprite : GaugeSprite_) {
		delete sprite;
	}
	GaugeSprite_.clear(); 
}

void Gauge::Initialize() {
	textureHandle_ = TextureManager::Load("./Resources/white1x1.png");

	for (int i = 0; i < maxHP; ++i) {

		// 本体ゲージ（色つき）
		auto gauge = KamataEngine::Sprite::Create(textureHandle_, startPos);
		gauge->SetSize(size);

		if (i == red) {
			gauge->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f)); // 赤で表示
		} else if (i == Green) {
			gauge->SetColor({0.24f, 0.70f, 0.44f, 1.0f}); // ミドリで表示
		}
		GaugeSprite_.push_back(gauge);
	}
}

void Gauge::Update() {

	for (int i = 0; i < GaugeSprite_.size(); ++i) {

		if (i == Green) {
			GaugeSprite_[i]->SetSize(Vector2(GaugeSprite_[i]->GetSize().x - 1, GaugeSprite_[i]->GetSize().y));
			if (GaugeSprite_[i]->GetSize().x < 0) {
				GaugeSprite_[i]->SetSize(size);
			}
		}
	}
}

void Gauge::Draw() {

	// 次に現在HPに応じたゲージを描画
	for (int i = 0; i < maxHP; i++) {
		GaugeSprite_[i]->Draw();
	}
}