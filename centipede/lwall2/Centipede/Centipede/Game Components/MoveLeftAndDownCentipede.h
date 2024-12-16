#include "TEAL\CommonElements.h"
#include "MoveStateCentipede.h"
#include "Centipede.h"

class MoveLeftAndDownCentipede: public MoveStateCentipede
{
public:
	MoveLeftAndDownCentipede();
	MoveLeftAndDownCentipede(const MoveLeftAndDownCentipede&) = default;
	MoveLeftAndDownCentipede& operator=(const MoveLeftAndDownCentipede&) = default;
	~MoveLeftAndDownCentipede() = default;

	virtual const sf::Vector2f GetScale(int i) const override;
	virtual const MoveStateCentipede* GetNextState(Centipede* centi,
		MushroomSpawner* mushGrid) const override;
	virtual const void createMushroom(sf::Vector2f location,
		MushroomSpawner* mushGrid) const override;
private:

};
