#include "Framework.h"
#include "SoundScene.h"

SoundScene::SoundScene()
{
	System_Create(&soundSystem);
	soundSystem->init(1, FMOD_INIT_NORMAL, nullptr);

	soundSystem->createStream("Sounds/drumloop.wav", FMOD_LOOP_NORMAL, nullptr, &sound);
	soundSystem->playSound(sound, nullptr, false, &channel);
	channel->setVolume(1.0f);
}

SoundScene::~SoundScene()
{
	sound->release();

	soundSystem->release();
}

void SoundScene::Update()
{
	//if (KEY_DOWN(VK_F1))
	if (Keyboard::Get()->AnyKey())
		SceneManager::Get()->Change("Knight");

	soundSystem->update();
}

void SoundScene::Render()
{
}

void SoundScene::Start()
{
}

void SoundScene::End()
{
	channel->stop();
}
