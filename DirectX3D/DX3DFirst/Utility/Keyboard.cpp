#include "Framework.h"
#include "Keyboard.h"


Keyboard::Keyboard()
{
	ZeroMemory(_keyState,    sizeof(_keyState));
	ZeroMemory(_keyOldState, sizeof(_keyOldState));
	ZeroMemory(_keyMap,      sizeof(_keyMap));
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	memcpy(_keyOldState, _keyState, sizeof(_keyState));

	ZeroMemory(_keyState, sizeof(_keyState));
	ZeroMemory(_keyMap,   sizeof(_keyMap));

	if (!GetKeyboardState(_keyState))
		return;

	for (int i = 0; i < MAX_KEY; i++)
	{
		byte key = _keyState[i] & 0x80;
		_keyState[i] = key ? 1 : 0;

		byte old = _keyOldState[i];
		byte cur = _keyState[i];

		if (old == 0 && cur == 1)      
			_keyMap[i] = DOWN;
		else if (old == 1 && cur == 0) 
			_keyMap[i] = UP;
		else if (old == 1 && cur == 1) 
			_keyMap[i] = PRESS;
		else
			_keyMap[i] = NONE;
	}
}
