#include "GenericFactory.h"
#include "EntityVector.h"
#include "Parser.h"
#include "Creature.h"
#include "Consumable.h"
#include "Armor.h"
#include "Weapon.h"
#include "Equipment.h"
#include <map>
#include <functional>
#include <string>

using namespace std;

GenericFactory & GenericFactory::instance()
{
	static GenericFactory factory;
	return factory;
}

GenericFactory::GenericFactory()
{
	map<string, function<XMLSerializable*()>> mConstructors;
	
	mConstructors["Creature"] = []() { return new Creature; };
	mConstructors["Consumable"] = []() { return new Consumable; };
	mConstructors["Armor"] = []() { return new Armor; };
	mConstructors["Weapon"] = []() { return new Weapon; };
	mConstructors["Equipment"] = []() { return new Equipment; };

	vector<XMLSerializable*> vObjects;

    parseXML(mConstructors, "world.xml", vObjects);

	m_vCreatures.constructVector(vObjects);
	m_vConsumables.constructVector(vObjects);
	m_vArmors.constructVector(vObjects);
	m_vWeapons.constructVector(vObjects);
	m_vEquipment.constructVector(vObjects);
}

GenericFactory::~GenericFactory()
{
}

Creature * GenericFactory::generateCreature(int iMinHealth, int iMaxHealth)
{
	return m_vCreatures.generate( [=](Creature * pCreature) { return ((pCreature->getHealth() > iMinHealth)&&(pCreature->getHealth() < iMaxHealth)); });
}

Consumable * GenericFactory::generateConsumable()
{
	return m_vConsumables.generate([](Consumable * pConsumable) { return true; });
}

Armor * GenericFactory::generateArmor(int maxValue)
{
	return m_vArmors.generate([=](Armor * pArmor) { return (pArmor->getValue() < maxValue); });
}

Weapon * GenericFactory::generateWeapon(int maxValue)
{
	return m_vWeapons.generate([=](Weapon * pWeapon) { return (pWeapon->getValue() < maxValue); });
}

Equipment * GenericFactory::generateEquipment(char symbol)
{
	return m_vEquipment.generate( [=](Equipment * pEquipment) { return (pEquipment->getSymbol() == symbol); });
}