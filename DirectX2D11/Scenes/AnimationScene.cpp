#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
	Audio::Get()->Add("bgm", "Sounds/drumloop.wav", true);
	Audio::Get()->Add("jump", "Sounds/jump.wav");
	Audio::Get()->Add("attack", "Sounds/attack.wav");

	Audio::Get()->Play("bgm", 0.1f);

	mario = new Mario();
	mario->position = { CENTER_X, CENTER_Y };

	knight = new Knight();
}

AnimationScene::~AnimationScene()
{
	delete mario;
	delete knight;
}

void AnimationScene::Update()
{
	mario->Update();
	knight->Update();
}

void AnimationScene::Render()
{
	mario->Render();
	knight->Render();
}
