#include "Effect.h"
#include "DxLib.h"

Effect::Effect(int indexType):
	effectType_(indexType)
{
}

Effect::~Effect()
{
}

void Effect::Activate()
{
	if (effectType_ == static_cast<int>(EffectType::LTtoRB)) {
		for (int y = 0; y < WHEIGHT / (PRADIUS * 2); y++) {
			for (int x = 0; x < WWIDTH / (PRADIUS * 2); x++) {
				particles_.push_back(Particle{ Vector2(64 * x + PRADIUS, 64 * y + PRADIUS), PRADIUS, static_cast<int>(EffectType::LTtoRB) });
			}
		}
	}
	else if (effectType_ == static_cast<int>(EffectType::LTtoRB2)) {
		for (int y = 0; y < WHEIGHT / (PRADIUS * 2) / 2; y++) {
			for (int x = 0; x < WWIDTH / (PRADIUS * 2); x++) {
				particles_.push_back(Particle{ Vector2(64 * x + PRADIUS, 64 * y + PRADIUS), PRADIUS, static_cast<int>(EffectType::LTtoRB2) });
				particles_.push_back(Particle{ Vector2(WWIDTH - (64 * x + PRADIUS), WHEIGHT - (64 * y + PRADIUS)), PRADIUS, static_cast<int>(EffectType::LTtoRB2) });
			}
		}
	}
	startTime_ = GetNowCount();
	isPlay_ = true;
}

void Effect::SceneChange()
{
	if (isPlay_) {
		// --�G�t�F�N�g�J�n->�o�ߎ���-- //
		elapsedTime_ = (GetNowCount() - startTime_) / 1000.0f;

		if ((GetNowCount() - startTime_) % 1 == 0) {
			if (activeCount_ < particles_.size()) {
				particles_[activeCount_].Activate();
				activeCount_++;
			}
		}

		for (int i = 0; i < activeCount_; i++) {
			particles_[i].InOutBox();
		}

		// --�w�肳��Ă��鎞�Ԃ��߂�����-- //
		if (7.0f <= elapsedTime_) {
			isPlay_ = false;
		}
	}
}

void Effect::Reset()
{
	startTime_ = 0;
	elapsedTime_ = 0.0f;
	isPlay_ = false;
}
