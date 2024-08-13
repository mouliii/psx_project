#pragma once
#include <cstdint>
#include <psxpad.h>
#include <psxapi.h>
#include <stdlib.h> // abs


class Controller
{
public:
	Controller();
	PADTYPE* GetController();
	void UpdateBuffer();
	bool IsControllerConnected();
	bool IsButtonPressed(std::uint16_t button);
	bool IsButtonJustPressed(std::uint16_t button);
	bool IsButtonJustReleased(std::uint16_t button);
	int8_t GetLeftAnalogX();
	int8_t GetLeftAnalogY();
	int8_t GetRightAnalogX();
	int8_t GetRightAnalogY();
	uint16_t GetAnalogInputRaw(bool left);
public:
	PADTYPE* pad;
	uint8_t padBuffer[34] = { 0 };
	uint16_t padPrevBuffer = 0;
	uint8_t deadZone = 15;
	// int acceptedPadTypes;
};