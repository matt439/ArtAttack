#ifndef SOUNDBANKOBJECT_H
#define SOUNDBANKOBJECT_H

#include "SoundBank.h"
#include "ResourceManager.h"

class SoundBankObject
{
public:
	SoundBankObject() = default;
	SoundBankObject(std::string sound_bank_name, ResourceManager* resource_manager);
protected:
	SoundBank* get_sound_bank() const;
	SoundBank* get_sb();

	void play_wave(const std::string& wave_name,
		float volume = 1.0f, float pitch = 0.0f, float pan = 0.0f);
	void play_effect(const std::string& effect_name,
		bool loop = false, float volume = 1.0f, float pitch = 0.0f, float pan = 0.0f);
	void stop_effect(const std::string& effect_name, bool immediate = false);
	void pause_effect(const std::string& effect_name);
	void resume_effect(const std::string& effect_name);
	void set_effect_volume(const std::string& effect_name, float volume);
	void set_effect_pitch(const std::string& effect_name, float pitch);
	void set_effect_pan(const std::string& effect_name, float pan);
	DirectX::SoundState get_effect_state(const std::string& effect_name);
	bool is_effect_looping(const std::string& effect_name);

	DirectX::SoundEffectInstance* get_sound_effect_instance(const std::string& instance_name);
	DirectX::SoundEffectInstance* get_sei(const std::string& instance_name);
	
	void set_sound_bank_name(const std::string& sound_bank_name);
private:
	std::string _sound_bank_name = "";
	ResourceManager* _resource_manager = nullptr;
};
#endif // !SOUNDBANKOBJECT_H
