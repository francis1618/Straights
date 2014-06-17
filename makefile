CXX = g++ # variables and initialization
CXXFLAGS = -g -Wall -MMD # builds dependency lists in .d ﬁles
OBJECTS = Card.o Command.o ComputerStrategy.o Deck.o Game.o HumanStrategy.o Player.o
DEPENDS = ${OBJECTS:.o=.d} # substitute ".o" with ".d"
EXEC = UserAccount

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}