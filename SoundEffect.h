#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H
#include "Resource.h"
#include "Asset.h"
class SoundEffect : public Resource
{
public:
	//contructors/destructors
	SoundEffect();
	virtual ~SoundEffect();

	//methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;

	//members
	static ObjectPool<SoundEffect>* Pool;
private:
	Asset* m_effect;

};

#endif