#ifndef _GenericFactory_included_
#define _GenericFactory_included_

#include "EntityVector.h"
#include "Creature.h"
#include "Consumable.h"
#include "Armor.h"
#include "Weapon.h"
#include "Equipment.h"

using namespace std;

class GenericFactory
{
public:	
	static GenericFactory & instance();
	virtual ~GenericFactory();
	Creature * generateCreature(int iMinHealth, int iMaxHealth);
	Consumable * generateConsumable();
	Armor * generateArmor(int maxValue);
	Weapon * generateWeapon(int maxValue);
	Equipment * generateEquipment(char symbol);

private:
	GenericFactory();
	EntityVector<Creature> m_vCreatures;
	EntityVector<Consumable> m_vConsumables;
	EntityVector<Armor> m_vArmors;
	EntityVector<Weapon> m_vWeapons;
	EntityVector<Equipment> m_vEquipment;
};

#endif
