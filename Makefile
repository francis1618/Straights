CXX = g++ 						# variables and initialization
CXXFLAGS = -g -Wall -MMD 		# builds dependency lists in .d ﬁles
OBJECTS = Command.o Card.o Deck.o Player.o StraightStrategy.o HumanStrategy.o ComputerStrategy.o Game.o
DEPENDS = ${OBJECTS:.o=.d} 		# substitute ".o" with ".d"
EXEC = exec

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}