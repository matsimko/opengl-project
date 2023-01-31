#include "SceneWithPlayerView.h"
#include "App.h"
#include "Crosshair.h"

PlayerView* SceneWithPlayerView::getPlayerView()
{
	return playerView;
}

SceneWithPlayerView::SceneWithPlayerView()
{
	playerView = nullptr;
}

SceneWithPlayerView::~SceneWithPlayerView()
{
	delete playerView;
}

void SceneWithPlayerView::doLoad()
{
	App& app = App::getInstance();
	//tell the window that this scene wants the cursor to be captured
	//app.getWindow()->captureCursor();

	playerView = new PlayerView(camera, 5.f, 0.15f, 0.15f);
	addUpdatable(playerView);

	ui->addUIElement(new Crosshair(glm::vec4(1.f, 0.f, 1.f, 1.f), 1.5f, 1.f));
}
