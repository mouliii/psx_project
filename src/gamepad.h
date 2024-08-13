#pragma once
#include <cstdint>
#include <psxpad.h>
#include <psxapi.h>
#include <psxgte.h>


class GamePad
{
public:
	GamePad();
	PADTYPE* GetController(std::int8_t player);
	void UpdateBuffer();
	bool IsControllerConnected(std::int8_t player);
	bool IsButtonPressed(std::int8_t player, std::uint16_t button);
	bool IsButtonJustPressed(std::int8_t player, std::uint16_t button);
	std::uint8_t* GetAnalogRaw();
	
	// is just released
	// get_vector
	bool wtf = false;
private:
	uint8_t padBuffer[2][34] = { 0 };
	uint16_t prevBtnState[2] = { 0 };
};