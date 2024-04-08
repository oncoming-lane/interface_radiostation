all:
	g++ -g project.cpp RxEth.cpp TxEth.cpp -o project -lsfml-graphics -lsfml-window -lsfml-system 

	#g++ -g project_copy.cpp Tx.cpp Rx.cpp -o project -lsfml-graphics -lsfml-window -lsfml-system 