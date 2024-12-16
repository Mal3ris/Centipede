#pragma once
#include "TEAL\CommonElements.h"
#include "CritterStructs.cpp"

class FileRead
{
public:
	FileRead();
	FileRead(const FileRead&) = delete;
	FileRead& operator=(const FileRead&) = delete;
	~FileRead() = default;

	void ReadAllData();

	void fillData(std::string s, std::string val);

	std::string toLowerCase(const std::string& str);
	
	WaveData getWave(int waveNum);

private:

	const static int SIZEOFWAVE = 18;
	const static int NUMOFWAVE = 5;
	const static int MAXNUMSOLOHEADS = 5;
	int currWave = 0;

	std::string possibleData[SIZEOFWAVE][3] = { {"wave", "num", "not seen"},
	{"scorpionactive", "bool", "not seen"} , {"scorpionspeed", "num", "not seen"}, {"scorpionfrequency", "float", "not seen"},
	{"spideractive", "bool", "not seen"} , {"spiderspeed", "num", "not seen"}, {"spiderfrequency", "float", "not seen"},
	{"fleaactive", "bool", "not seen"} , {"fleaspeed", "num", "not seen"}, {"fleamushroomthreshold", "num", "not seen"}, {"fleamushroomprobability", "num", "not seen"},
	{"centipedespeed", "num", "not seen"},  {"centipedelength", "num", "not seen"},
	{"centipedesoloheadstartactive", "bool", "not seen"}, {"centipedesoloheadstartcount", "num", "not seen"},
	{"centipedesoloheadbottomactive", "bool", "not seen"}, {"centipedesoloheadbottomcount", "num", "not seen"}, {"centipedesoloheadbottomfrequency", "float", "not seen"} };

	WaveData waves[NUMOFWAVE];
};