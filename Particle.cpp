#include "Particle.h"
#include <cassert>
#include "DxLib.h"

Particle::Particle(Vector2 pos, float radius, int indexType) :
	pos_(pos),
	radius_(radius),
	effectType_(indexType)
{
}

Particle::~Particle()
{
}

void Particle::Activate()
{
	startTime_ = GetNowCount();
	isPlay_ = true;
}

void Particle::InOutBox()
{
	if (isPlay_) {
		if (effectType_ == static_cast<int>(EffectType::LTtoRB)) {
			// --エフェクト開始->経過時間-- //
			elapsedTime_ = (GetNowCount() - startTime_) / 1000.0f;

			if (elapsedTime_ <= 0.15f) {
				DrawBoxAA(
					pos_.x - radius_, pos_.y - radius_,
					pos_.x + radius_, pos_.y + radius_,
					0x000000, true, 1.0f
				);
				DrawBoxAA(
					pos_.x - (radius_ - 3), pos_.y - (radius_ - 3),
					pos_.x + (radius_ - 3), pos_.y + (radius_ - 3),
					0xffffff, true, 1.0f
				);
			}

			if (0.15f <= elapsedTime_ && elapsedTime_ <= 2.5f) {
				DrawBoxAA(
					pos_.x - (radius_ + 4), pos_.y - (radius_ + 4),
					pos_.x + (radius_ + 4), pos_.y + (radius_ + 4),
					0x000000, true, 1.0f
				);
			}

			if (2.5f <= elapsedTime_ && elapsedTime_ <= 2.8f) {
				DrawBoxAA(
					pos_.x - (radius_ + 4), pos_.y - (radius_ + 4),
					pos_.x + (radius_ + 4), pos_.y + (radius_ + 4),
					0x000000, true, 1.0f
				);
			}

			if (2.8f <= elapsedTime_ && elapsedTime_ <= 3.5f) {
				shrinkSize_ - 4 <= radius_ ? SetRadius(radius_ - shrinkSize_) : SetRadius(-4.0f);

				DrawBoxAA(
					pos_.x - (radius_ + 4), pos_.y - (radius_ + 4),
					pos_.x + (radius_ + 4), pos_.y + (radius_ + 4),
					0x000000, true, 1.0f
				);
			}

			// --指定されている時間が過ぎたら-- //
			if (3.5f <= elapsedTime_) {
				isPlay_ = false;
			}
		}
		else if (effectType_ == static_cast<int>(EffectType::LTtoRB2)) {
			// --エフェクト開始->経過時間-- //
			elapsedTime_ = (GetNowCount() - startTime_) / 1000.0f;

			if (elapsedTime_ <= 0.15f) {
				DrawBoxAA(
					pos_.x - radius_, pos_.y - radius_,
					pos_.x + radius_, pos_.y + radius_,
					0x000000, true, 1.0f
				);
				DrawBoxAA(
					pos_.x - (radius_ - 3), pos_.y - (radius_ - 3),
					pos_.x + (radius_ - 3), pos_.y + (radius_ - 3),
					0xffffff, true, 1.0f
				);
			}

			if (0.15f <= elapsedTime_ && elapsedTime_ <= 2.5f) {
				DrawBoxAA(
					pos_.x - (radius_ + 4), pos_.y - (radius_ + 4),
					pos_.x + (radius_ + 4), pos_.y + (radius_ + 4),
					0x000000, true, 1.0f
				);
			}

			if (2.5f <= elapsedTime_ && elapsedTime_ <= 2.8f) {
				DrawBoxAA(
					pos_.x - (radius_ + 4), pos_.y - (radius_ + 4),
					pos_.x + (radius_ + 4), pos_.y + (radius_ + 4),
					0x000000, true, 1.0f
				);
			}

			if (2.8f <= elapsedTime_ && elapsedTime_ <= 3.5f) {
				shrinkSize_ - 4 <= radius_ ? SetRadius(radius_ - shrinkSize_) : SetRadius(-4.0f);

				DrawBoxAA(
					pos_.x - (radius_ + 4), pos_.y - (radius_ + 4),
					pos_.x + (radius_ + 4), pos_.y + (radius_ + 4),
					0x000000, true, 1.0f
				);
			}

			// --指定されている時間が過ぎたら-- //
			if (3.5f <= elapsedTime_) {
				isPlay_ = false;
			}
		}
	}
}

void Particle::Reset()
{
	startTime_ = 0;
	elapsedTime_ = 0.0f;
	isPlay_ = false;
}
