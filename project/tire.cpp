#include "tire.h"

void CTire::SetRotationLC(Vector3f param)
{
	rotationLC = param;

	// Keep us in the range of [-2PI, ... , 2PI]
	if(rotationLC.X() > (2.0f * PI_BOS)) {
		rotationLC.X() -= (2.0f * PI_BOS);
	}
	else if(rotationLC.X() < (-2.0f * PI_BOS)) {
		rotationLC.X() += (2.0f * PI_BOS);
	}

	if(rotationLC.Y() > (2.0f * PI_BOS)) {
		rotationLC.Y() -= (2.0f * PI_BOS);
	}
	else if(rotationLC.Y() < (-2.0f * PI_BOS)) {
		rotationLC.Y() += (2.0f * PI_BOS);
	}

	if(rotationLC.Z() > (2.0f * PI_BOS)) {
		rotationLC.Z() -= (2.0f * PI_BOS);
	}
	else if(rotationLC.Z() < (-2.0f * PI_BOS)) {
		rotationLC.Z() += (2.0f * PI_BOS);
	}
}

