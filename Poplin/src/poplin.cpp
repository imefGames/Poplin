#include <poplin/engine/gameengine.h>

int main()
{
	Poplin::GameEngineConfig config{};
	//TODO: edit config using config file

	Poplin::GameEngine engine{ config };
	engine.RunGameLoop();

	return 0;
}