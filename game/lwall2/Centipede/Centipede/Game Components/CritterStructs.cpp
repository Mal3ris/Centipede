#include "CritterStructs.h"
struct ScorpionData {
	bool active;
	float speed;
	float frequency;
};
struct SpiderData {
	bool active;
	float speed;
	float frequency;
};
struct FleaData {
	bool active;
	float speed;
	int threshold;
	int probability;
};
struct CentipedeData {
	float speed;
	int length;
	bool soloStartActive;
	int soloStartCount;
	bool soloPlayerActive;
	int soloPlayerCount;
	float soloPlayerFrequency;
};
struct WaveData {
	int WaveNum;
	ScorpionData scorpionData;
	SpiderData spiderData;
	FleaData fleaData;
	CentipedeData centipedeData;
};
