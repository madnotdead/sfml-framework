#include "managers/GameManager.h"
#include "hud/Hud.h"

int main()
{
	Game::GameManager gameManager;
	Game::Hud h(gameManager);
	gameManager.Run();
}
