#pragma once

//Responsible for All constants relating to Grid

class GridConstants{
public:
	static const int GRIDWIDTH = 30;
	static const int GRIDHEIGHT = 30;

	static const int PLAYZONE = GRIDHEIGHT - 7;
	static const int BOTTOMZONE = GRIDHEIGHT+1;

	static const int CELLSIZE = 16;
	static const int HALFCELLSIZE = CELLSIZE / 2;
	

};
