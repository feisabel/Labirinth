O que foi implementado:
	Esse projeto é uma versão do jogo labirinto, tendo como diferença a presença
	de inimigos que te perseguem e armadilhas que causam dano. Também possui um
	sistema de pontuação, determinado pela quantidade de vezes que o jogador foi
	atingido e pela quantidade de itens que foram pegos.



Como instalar a biblioteca gráfica:
http://sfml-dev.org/tutorials/2.1/#getting-started


Como compilar:

- entrar na pasta do projeto:
	cd [diretório]/Labirinto

- compilar:
	g++ -o game.o -c source/cppfiles/*.cpp
	g++ -o game game.o -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window 

  se instalou a biblioteca num diretório que não o padrão, então:
	g++ -o game.o -c source/cppfiles/*.cpp -I[diretório de instalação do sfml]/include
	g++ -o game game.o -L[diretório de instalação do sfml]/lib -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window


Como executar:

- entrar na pasta do projeto:
	cd [diretório]/Labirinto

- executar:
	./game

