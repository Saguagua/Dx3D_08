#pragma once

#define MAX_KEY 256

typedef unsigned char byte;

enum KeyState
{
	NONE,
	DOWN,
	UP,
	PRESS
};

class Keyboard : public Singleton<Keyboard>
{
	friend class Singleton;
private:
	Keyboard();
	~Keyboard();

public:
	void Update();

	bool  Down(DWORD key) { return _keyMap[key] == DOWN; }
	bool    Up(DWORD key) { return _keyMap[key] == UP; }
	bool Press(DWORD key) { return _keyMap[key] == PRESS; }

private:
	byte _keyState[MAX_KEY];
	byte _keyOldState[MAX_KEY];
	byte _keyMap[MAX_KEY];
};
