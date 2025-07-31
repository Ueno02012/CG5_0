#include "Number.h"
#include <iomanip>

using namespace KamataEngine;



Number::Number() {}

Number::~Number() {}

void Number::Initialize() {
	textureHandle_ = TextureManager::Load("./Resources/number.png");

	for (int i = 0; i < 5; i++) {
		// 各スプライトの表示位置（右から左へ並べる）
		Vector2 pos = {startPos.x - size.x * i, startPos.y};

		// スプライト生成
		Sprite* sprite = Sprite::Create(textureHandle_, pos);
		sprite->SetSize(size);
		sprite->SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		NumberSprite_.push_back(sprite);
	}
}

void Number::Update() {
	number_++;

	if (number_ >= 10000) {
		number_ = 0;
	}

	SetNumber(number_);
}

void Number::Draw() {
	for (int i = 0; i < NumberSprite_.size(); i++) {
		NumberSprite_[i]->Draw();
	}
}

void Number::SetNumber(int value) {
	number_ = value;

	// 数値を5桁のゼロ埋め文字列に変換
	std::stringstream ss;
	ss << std::setw(5) << std::setfill('0') << number_;
	std::string numStr = ss.str();

	// 各桁の数字をスプライトに反映
	for (int i = 0; i < NumberSprite_.size(); i++) {
		char digitChar = numStr[4 - i]; // 右から左に描画するため
		int digit = digitChar - '0';
		Vector2 texPos = {size.x * digit, 0.0f};
		NumberSprite_[i]->SetTextureRect(texPos, size);
	}
}
