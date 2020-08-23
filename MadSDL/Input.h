#pragma once
#include <SDL.h>

enum Axis { HORIZONTAL, VERTICAL };

class Input
{
public:
	inline static Input& get() 
	{
		if (s_instance == nullptr) {
			s_instance = new Input();
		}
		return *s_instance;
	}
	void Listen();
	bool GetKeyDown(SDL_Scancode key);

	int GetAxisKey(Axis axis);

private:
	Input();
	void KeyUp();
	void KeyDown();

	const Uint8* m_KeyStates;
	static Input* s_instance;

};
