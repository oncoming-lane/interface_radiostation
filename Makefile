all:
	#g++ -g project.cpp RxEth.cpp TxEth.cpp -o project -lsfml-graphics -lsfml-window -lsfml-system 
	g++ -o project project_thread.cpp TxEth.cpp RxEth.cpp buttons.cpp -std=c++11 -pthread -lsfml-graphics -lsfml-window -lsfml-system -lX11