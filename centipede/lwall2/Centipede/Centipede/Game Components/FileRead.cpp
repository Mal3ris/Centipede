#include "FileRead.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GridConstants.h"

using namespace std;


FileRead::FileRead() {
	ReadAllData();
}



void FileRead::ReadAllData() {

	ifstream f("Game Components\\inputFile.txt");

	if (!f.is_open()) {
		ConsoleMsg::WriteLine("FAILED TO FIND FILE");
		assert(false);
		
		return;
	}

	string s;
	bool flipFlop = false;
	bool wordInList;
	int wordLine;
	bool firstWave = true;
	bool newWave = false;
	bool fleaSpeed = false;
	bool centiSpeed = false;
	bool soloHeadPlayCount = false;

	int lineCount = 1;

	string lineInfo;
	
	while (getline(f, s)) {
		stringstream ss(s);
		string word;

		while (ss>>word) {
			if (flipFlop == false) {
				for (int i = 0; i < SIZEOFWAVE; i++) {
					if (possibleData[i][0] == toLowerCase(word)) {
						wordInList = true;
						wordLine = i;
						lineInfo = toLowerCase(word);
						break;
					}
					wordInList = false;
				}

				if (wordInList == false) {
					ConsoleMsg::WriteLine("NOT VIABLE WORD ON LINE " + Tools::ToString(lineCount));
					assert(false);
				}

				if (possibleData[wordLine][2] == "seen" && toLowerCase(word) != "wave") {
					ConsoleMsg::WriteLine("DOUBLE LOADING DATA ON LINE " + Tools::ToString(lineCount));
					assert(false);
				}
				else {
					possibleData[wordLine][2] = "seen";
				}

				if (toLowerCase(word) == "wave" && firstWave == false) {
					for (int i = 0; i < sizeof(possibleData) / sizeof(possibleData[0]); i++) {
						if (possibleData[i][2] == "not seen") {
							ConsoleMsg::WriteLine("NOT ENOUGH DATA IN WAVE " 
								+ Tools::ToString((lineCount-1)/(SIZEOFWAVE+1) + 1));
							assert(false);
						}
						else {
							possibleData[i][2] = "not seen";
						}
					}
					newWave = true;
					currWave++;
				}
				else if (toLowerCase(word) == "wave" && firstWave == true) {
					firstWave = false;
					newWave = true;
				}

				if (toLowerCase(word) == "fleaspeed") {
					fleaSpeed = true;
				}
				if (toLowerCase(word) == "centipedespeed") {
					centiSpeed = true;
				}
				if (toLowerCase(word) == "centipedesoloheadbottomcount") {
					soloHeadPlayCount = true;
				}
			}
			else {
				if (wordInList == true) {
					if (possibleData[wordLine][1] == "bool") {
						if (toLowerCase(word) != "true" && toLowerCase(word) != "false") {
							ConsoleMsg::WriteLine("NEED TRUE OR FALSE ON LINE " + Tools::ToString(lineCount));
							assert(false);
						}
					}
					else if (possibleData[wordLine][1] == "num") {
						for (char c : word) {
							if (!isdigit(c)) {
								ConsoleMsg::WriteLine("NEED POSITIVE INTEGER ON LINE " + Tools::ToString(lineCount));
								assert(false);
							}
						}
						if (stoi(word) == 0) {
							ConsoleMsg::WriteLine("NEED POSITIVE INTEGER ON LINE " + Tools::ToString(lineCount));
							assert(false);
						}
						if (newWave == true) {
							if (stoi(word) - 1 != currWave) {
								ConsoleMsg::WriteLine("WAVE SKIPPED ON LINE " + Tools::ToString(lineCount));
								assert(false);
							}
							newWave = false;
						}
						if (fleaSpeed == true) {
							int tempExp = stoi(word);
							while (tempExp % 2 == 0) {
								tempExp /= 2;
							}
							if (tempExp != 1 || stoi(word) > 16) {
								ConsoleMsg::WriteLine("SPEED NEEDS TO BE AN EXPONENT OF 2 AND LESS THAN 16 ON LINE " + Tools::ToString(lineCount));
								assert(false);
							}
							fleaSpeed = false;
						}
						if (centiSpeed == true) {
							//Doing this cause no speed control
							if (stoi(word) != GridConstants::HALFCELLSIZE) {
								ConsoleMsg::WriteLine("SPEED NEEDS TO BE " + Tools::ToString(GridConstants::HALFCELLSIZE) + " ON LINE " + Tools::ToString(lineCount));
								assert(false);
							}
							centiSpeed = false;
						}
						if (soloHeadPlayCount == true) {
							//Doing this cause of how I implement the alarm system for solo head spawning
							if (stoi(word) > MAXNUMSOLOHEADS) {
								ConsoleMsg::WriteLine("CANT HAVE MORE THAN " + Tools::ToString(MAXNUMSOLOHEADS) + " OF SOLO HEADS ON LINE " + Tools::ToString(lineCount));
								assert(false);
							}
							soloHeadPlayCount = false;
						}

					}
					else if (possibleData[wordLine][1] == "float") {
						bool singlePeriod = false;
						for (char c : word) {
							if ((!isdigit(c) && c != '.') || (c == '.' && singlePeriod == true)) {
								ConsoleMsg::WriteLine("NEED POSITIVE FLOAT ON LINE " + Tools::ToString(lineCount));
								assert(false);
							}
							if (c == '.') {
								singlePeriod = true;
							}
						}
						if (stof(word) == 0.0) {
							ConsoleMsg::WriteLine("NEED POSITIVE FLOAT ON LINE " + Tools::ToString(lineCount));
							assert(false);
						}
					}

					fillData(lineInfo, toLowerCase(word));
				}
			}
			flipFlop = !flipFlop;
		}
		lineCount++;
	}

	for (int i = 1; i < sizeof(possibleData) / sizeof(possibleData[0]); i++) {
		if (possibleData[i][2] == "not seen") {
			ConsoleMsg::WriteLine("NOT ENOUGH DATA IN WAVE "
				+ Tools::ToString((lineCount-1) / (SIZEOFWAVE+1) + 1));
			assert(false);
		}
		else {
			possibleData[i][2] = "not seen";
		}
	}

	f.close();
	
}


string FileRead::toLowerCase(const std::string& str) {
	string lowerStr = str;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return tolower(c); });
	return lowerStr;
}

void FileRead::fillData(string s, string val) {
	if (s == "wave") {
		waves[currWave].WaveNum = stoi(val);
	} else if (s.find("active") != string::npos) {
		bool tempBool;
		if (val == "false") {
			tempBool = false;
		}
		else {
			tempBool = true;
		}
		if (s.find("scorpion") != string::npos) {
			waves[currWave].scorpionData.active = tempBool;
		}
		else if (s.find("spider") != string::npos) {
			waves[currWave].spiderData.active = tempBool;
		}
		else if (s.find("flea") != string::npos) {
			waves[currWave].fleaData.active = tempBool;
		}else if (s.find("start") != string::npos) {
			waves[currWave].centipedeData.soloStartActive = tempBool;
		}else if (s.find("bottom") != string::npos) {
			waves[currWave].centipedeData.soloPlayerActive = tempBool;
		}
	}
	else if (s.find("speed") != string::npos) {
		float tempFloat = stof(val);
		if (s.find("scorpion") != string::npos) {
			waves[currWave].scorpionData.speed = tempFloat;
		}
		else if (s.find("spider") != string::npos) {
			waves[currWave].spiderData.speed = tempFloat;
		}
		else if (s.find("flea") != string::npos) {
			waves[currWave].fleaData.speed = tempFloat;
		}
		else if (s.find("centipede") != string::npos) {
			waves[currWave].centipedeData.speed = tempFloat;
		}
	}
	else if (s.find("frequency") != string::npos) {
		float tempFloat = stof(val);
		if (s.find("scorpion") != string::npos) {
			waves[currWave].scorpionData.frequency = tempFloat;
		}
		else if (s.find("spider") != string::npos) {
			waves[currWave].spiderData.frequency = tempFloat;
		}
		else if (s.find("centipede") != string::npos) {
			waves[currWave].centipedeData.soloPlayerFrequency = tempFloat;
		}
	}
	else if (s == "fleamushroomthreshold") {
		waves[currWave].fleaData.threshold = stoi(val);
	}
	else if (s == "fleamushroomprobability") {
		waves[currWave].fleaData.probability = stoi(val);
	}
	else if (s == "centipedelength") {
		waves[currWave].centipedeData.length = stoi(val);
	}
	else if (s == "centipedesoloheadstartcount") {
		waves[currWave].centipedeData.soloStartCount = stoi(val);
	}
	else if (s == "centipedesoloheadbottomcount") {
		waves[currWave].centipedeData.soloPlayerCount = stoi(val);
	}
}

WaveData FileRead::getWave(int waveNum) {
	if (waveNum > NUMOFWAVE) {
		return waves[NUMOFWAVE - 1];
	}
	return waves[waveNum - 1];
}