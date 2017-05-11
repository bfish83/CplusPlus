OBJECTS = armor.o character.o consumable.o creature.o dungeonlevel.o entity.o equipment.o genericfactory.o item.o parser.o player.o tile.o tools.o weapon.o xmlserializable.o

HEADERS = Armor.h Character.h Consumable.h Creature.h DungeonLevel.h Entity.h EntityVector.h Equipment.h GenericFactory.h Item.h Parser.h Player.h Tile.h Tools.h Weapon.h XMLSerializable.h

pa4: $(OBJECTS) main.o
	g++ -o pa4 $^ -lncurses

%.o: %.cpp $(HEADERS)
	g++ -std=c++0x -c $< -o $@

clean:
	rm -f *.o
