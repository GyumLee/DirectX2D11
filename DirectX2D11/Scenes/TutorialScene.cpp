#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    //rect = new TestRect(Float2(CENTER_X, CENTER_Y), Float2(300.0f, 200.0f));
    circle = new TestCircle(Float2(CENTER_X, CENTER_Y), 100);

    world = new MatrixBuffer();
    view = new MatrixBuffer();
    projection = new MatrixBuffer();

    Matrix orthographic = XMMatrixOrthographicOffCenterLH(
        0.0f, WIN_WIDTH, WIN_HEIGHT, 0, -1.0f, 1.0f);

    projection->Set(orthographic);
}

TutorialScene::~TutorialScene()
{
    //delete rect;
    delete circle;

    delete world;
    delete view;
    delete projection;
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
    world->SetVS(0);
    view->SetVS(1);
    projection->SetVS(2);

    //rect->Render();
    circle->Render();
}
