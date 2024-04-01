all:
	g++ -g project.cpp Tx.cpp TxEth.cpp  -o project -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ -pthread
	 
