#pragma once
#include <string>

struct CubeMapFilenames {
	std::string xpos, xneg;
	std::string ypos, yneg;
	std::string zpos, zneg;

	CubeMapFilenames(
		std::string xpos, std::string xneg,
		std::string ypos, std::string yneg,
		std::string zpos, std::string zneg);
};
