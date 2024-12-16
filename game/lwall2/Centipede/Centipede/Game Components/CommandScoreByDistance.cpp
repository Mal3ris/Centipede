#include "CommandScoreByDistance.h"
#include "ScoreManager.h"

CommandScoreByDistance::CommandScoreByDistance(int dn, int dm, int df,
	int vn, int vm, int vf)
	: dNear(dn), dMed(dm), dFar(df), vNear(vn), vMed(vm), vFar(vf), score(0)
{
}

void CommandScoreByDistance::Execute()
{
	ScoreManager::AddScore(score);
}

int CommandScoreByDistance::CalcDist(int dist) {
	if (dist <= dNear)
	{
		//printf("\t\tNear range detected:\n");
		score = vNear;
	}
	else if (dist <= dMed)
	{
		//printf("\t\tMedium range detected:\n");
		score = vMed;
	}
	else
	{
		//printf("\t\tFar range detected:\n");
		score = vFar;
	}

	return score;
}
