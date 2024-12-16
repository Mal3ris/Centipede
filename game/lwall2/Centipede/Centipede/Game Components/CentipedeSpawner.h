#pragma once

#include "TEAL\CommonElements.h"
#include "FileRead.h"
#include "CritterStructs.h"

//Forward Decleration
class CentipedeFactory;
class CentiBodFactory;
class MushroomSpawner;
class CentipedeLoop;

class CentipedeSpawner
{
public:
	CentipedeSpawner(MushroomSpawner* pMS, CentipedeFactory* pCF, CentiBodFactory* pCBF);
	CentipedeSpawner(const CentipedeSpawner&) = delete;
	CentipedeSpawner& operator=(const CentipedeSpawner&) = delete;
	~CentipedeSpawner() = default;

	void SpawnCentipede(int length);
	void SpawnBottomCentipede();

	void Initialize();

	void waveSettings(CentipedeData& pCD);

	void startWave();

	void CancelAlarms();

private:
	static CentipedeFactory* myCentipedeFactory;
	static CentiBodFactory* myCentiBodFactory;
	static MushroomSpawner* myMushroomGrid;

	CentipedeLoop* myLittleLoop;

	float speed;
	int len;
	bool SoloStartActive;
	int numSoloStart;
	bool SoloBottomActive;
	int numSoloBottom;
	float SoloBottomFrequency;

};
