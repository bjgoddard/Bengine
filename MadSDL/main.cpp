#include "Engine.h"
#include "Timer.h"

int main(int argc, char** argv)
{
	Engine& engine = Engine::get();
	engine.Init();

	while (engine.IsRunning())
	{
		engine.Events();
		engine.Update();
		engine.Render();
		Timer::get()->Tick();
	}

	engine.Clean();
	return 0;
}