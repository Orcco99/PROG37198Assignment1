#include "SoundEffect.h"

ObjectPool<SoundEffect>* SoundEffect::Pool = nullptr;

SoundEffect::SoundEffect() {
	m_effect = nullptr;
}

SoundEffect::~SoundEffect() {

}

void SoundEffect::AssignNonDefaultValues() {
	m_effect = AssetController::Instance().GetAsset("chunk0.bin");
	Resource::AssignNonDefaultValues();

}

void SoundEffect::Serialize(std::ostream& _stream) {
	SerializeAsset(_stream, m_effect);
	Resource::Serialize(_stream);

}
void SoundEffect::Deserialize(std::istream& _stream) {
	DeserializeAsset(_stream, m_effect);
	Resource::Deserialize(_stream);
}

void SoundEffect::ToString() {
	cout << "Sound Effect" << endl;
	m_effect->ToString();
	Resource::ToString();

}