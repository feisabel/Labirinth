
#include "../menu.h"
#include "../game.h"
#include "../classmain.h"
#include "../menucontinue.h"
#include "../scene.h"
#include "../scene_manager.h"
#include "../endgame.h"
#include "../enemy.h"
#include "../maze.h"
#include "../item.h"
#include "../position.h"

#include "../custom/stack.h"
using custom::stack;

#include <fstream>
#include <sstream>
#include <iostream>

// Função que forma o labririnto conforme as informações do arquivo de entrada e modifica entrance e exit
bool Game::read_from_file(int i = 1)
{
    std::ifstream entrada;                             // Conexão com o arquivo "entrada.txt".

    if(i == 1)
        entrada.open( "levels/entrada.txt", std::ifstream::in ); // Abre o arquivo "entrada.txt" correspondente ao primeiro level
    else if( i == 2 )
        entrada.open( "levels/entrada2.txt", std::ifstream::in ); //Abre o arquivo correspondente ao segundo level
    else
        entrada.open( "levels/entrada3.txt", std::ifstream::in ); //Abre o arquivo correspondente ao terceiro level

    if( entrada.is_open() )
    {
        int a, b;

        if( !(entrada >> a) ) //leitura da quantidade de colunas e linhas
        {
            entrada.close();
            std::cerr << "não leu a" << std::endl;
            return false;
        }
        if( !(entrada >> b) )
        {
            entrada.close();
            std::cerr << "não leu a" << std::endl;
            return false;
        }

        maze.init(a, b); //inicializa a matriz de blocos com a colunas e b colunas 

        int j;
        for (j=0; j<b; j++) //linhas 
        {
            for (int i=0; i<a; i++) //colunas
            {
                int x;
                entrada >> x; //lê um inteiro

                if (x == 1) maze[i][j].type() = Block::WALL; //verifica se é parede
                else
                {
                    maze[i][j].type() = Block::FLOOR; //se não define como chão

                    if (x == 2) maze.entrance() = Position(i, j); //define a posição da entrada
                    else if (x == 3) maze.exit() = Position(i, j); //define a posição da saída
                    else if (x == 4) 
                    {
                        Trap t;
                        t.pos() = Position(i, j); //adiciona uma armadilha à lista de armadilhas
                        traps.push_back(t);
                    }
                    else if (x == 5)
                    {
                        Enemy s(Enemy::SLEEP);
                        s.pos() = Position(i, j); //adiciona um inimigo à lista de inimigos
                        enemies.push_back(s);
                    }
                    else if (x == 6)
                    {
                        Item h(Item::HEAL);
                        h.pos() = Position(i, j); //adiciona um item do tipo HEAL à lista de medkit
                        hearts.push_back(h);
                    }
                    else if (x == 7)
                    {
                        Item a(Item::AMMO);
                        a.pos() = Position(i, j); //adiciona um item do tipo AMMO à lista de munições 
                        ammuns.push_back(a);
                    }
                    else if (x == 8)
                    {
                        Enemy e(Enemy::AWAKE);
                        e.pos() = Position(i, j); //adiciona um inimigo à lista de inimigos 
                        enemies.push_back(e);
                    }
                }
            }
        }

        // Verifica se a leitura da matriz ocorreu corretamente.
        if( j != b ) {
            std::cerr << "não leu matriz" << std::endl;
            entrada.close();
            return false;
        }
    }
    else {
        std::cerr << "não abriu arquivo" << std::endl; //mensagem caso tenha dado erro na leitura
        entrada.close();
        return false;
    }

    entrada.close();

    return verify_maze(maze); //retorna se o labirinto é válido ou não 
}

// verifica se um labirinto é válido 
bool Game::verify_maze(Maze& maze)
{
    stack<Position> marked;     // pilha que armazena os caminhos já visitados
    stack<Position> dfs;        // pilha que determina a ordem em que os caminhos vão ser visitados

    dfs.push(maze.entrance());  // coloca a posição da entrada do labirinto na pilha

    while (!dfs.empty() && dfs.top() != maze.exit())    // enquanto houver caminhos a serem visitados e não encontrar a saída
    {
        marked.push(dfs.top());                         // coloca o caminho atual na pilha de caminhos visitados

        Position left = get_adjacent(dfs.top(), LEFT);      // pega os caminhos adjacentes
        Position right = get_adjacent(dfs.top(), RIGHT);
        Position up = get_adjacent(dfs.top(), UP);
        Position down = get_adjacent(dfs.top(), DOWN);

        // coloca o primeiro caminho adjacente válido que ainda não foi verificado na pilha
        if (maze.in_bounds(left) && maze[left.x][left.y].type() == Block::FLOOR && !marked.includes(left))
            dfs.push(left);
        else if (maze.in_bounds(right) && maze[right.x][right.y].type() == Block::FLOOR && !marked.includes(right))
            dfs.push(right);
        else if (maze.in_bounds(up) && maze[up.x][up.y].type() == Block::FLOOR && !marked.includes(up))
            dfs.push(up);
        else if (maze.in_bounds(down) && maze[down.x][down.y].type() == Block::FLOOR && !marked.includes(down))
            dfs.push(down);
        else dfs.pop();     // se não houver, retira esse caminho da pilha
    }

    return !dfs.empty(); // se a pilha estiver vazia, então não encontrou rota até a saída, e vice-versa
}


// Construtor padrão
Game::Game()
: timer(1000000.0/FPS), inited(true), circle(3, 15), level(1) 
{
    if (!read_from_file()) //verificação da leitura correta do arquivo de entrada
    {
        std::cerr << "erro: não foi possível carregar labirinto" << std::endl;
		inited = false;
		return;
    }

    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf")) //inicializa a fonte
    {
        std::cerr << "erro de fonte" << std::endl;
		inited = false;
		return;
    }

    circle.setFillColor(sf::Color::Red); //define a cor do ponto que oritenta o player como vermelho

    player_hp.setCharacterSize(20); //define tamanho da letra
    player_hp.setFont(font); //define o tipo da fonte 
    player_hp.setColor(sf::Color::White); //define a cor do texto

    std::stringstream ss;
    ss << player.hp() << "hp"; //converte a informação hp int para string
    player_hp.setString(ss.str()); //define o texto de player_hp 

    player_hp.setPosition(sf::Vector2f(50, 30)); //define a posição 

    player_ammo.setCharacterSize(20); //define tamanho da letra
    player_ammo.setFont(font); //define fonte
    player_ammo.setColor(sf::Color::White); //define cor

    std::stringstream ss1;
    ss1 << player.ammo() <<"ammo"; //converte a informação ammo int para string
    player_ammo.setString(ss1.str()); //define o texto de player_ammo 

    player_ammo.setPosition(sf::Vector2f(150, 30)); //define a posição de player_ammo

	player_level.setCharacterSize(20); //define tamanho da fonte
    player_level.setFont(font); //define a fonte
    player_level.setColor(sf::Color::White); //define a cor

    std::stringstream ss3; 
    ss3 << "level" << level; //converte level de int para string
    player_level.setString(ss3.str()); //define o conteúdo de player_level

    player_level.setPosition(sf::Vector2f(250, 30)); //define a posição de player_level

    //carrega as texturas com suas respectivas imagens
	if (!cross.loadFromFile("resources/images/cross.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!map.loadFromFile("resources/images/map.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!h1.loadFromFile("resources/images/heart1.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!h2.loadFromFile("resources/images/heart2.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!h3.loadFromFile("resources/images/heart3.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!h4.loadFromFile("resources/images/heart4.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!h5.loadFromFile("resources/images/heart5.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!music.openFromFile("resources/sounds/maze_music.ogg"))
    {
        std::cerr << "erro" << std::endl;
		inited = false;
		return;
    }

    if (!gunfire.loadFromFile("resources/sounds/gunfire_effect.ogg"))
    {
        std::cerr << "erro" << std::endl;
		inited = false;
		return;
    }

    if (!bufferPlayerDmg.loadFromFile("resources/sounds/char_damage.ogg"))
    {
        std::cerr << "erro" << std::endl;
		inited = false;
		return;
    }

    if (!musicplayON.loadFromFile("resources/images/volume.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!musicplayOFF.loadFromFile("resources/images/mudo.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!bufferZombieAwake.loadFromFile("resources/sounds/alive_effect.flac"))
    {
        std::cerr << "erro" << std::endl;
		inited = false;
		return;
    }

    if (!bufferZombieDead.loadFromFile("resources/sounds/dead_effect.flac"))
    {
        std::cerr << "erro" << std::endl;
		inited = false;
		return;
    }

    if (!fade_out.loadFromFile("resources/images/fade_out.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!exit.loadFromFile("resources/images/exit.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!floor.loadFromFile("resources/images/floor1.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!trap_off.loadFromFile("resources/images/trap_off3.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!trap_on.loadFromFile("resources/images/trap_on3.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!spawn.loadFromFile("resources/images/spawn1.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!monster_front.loadFromFile("resources/images/skeleton_front.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!monster_back.loadFromFile("resources/images/skeleton_front.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!monster_left.loadFromFile("resources/images/skeleton_left.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!monster_right.loadFromFile("resources/images/skeleton_right.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!ammo.loadFromFile("resources/images/ammo.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!med.loadFromFile("resources/images/medkit.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!character_back.loadFromFile("resources/images/char_back.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!character_front.loadFromFile("resources/images/char_front.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!character_left.loadFromFile("resources/images/char_left.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!character_right.loadFromFile("resources/images/char_right.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!bullet_down.loadFromFile("resources/images/bullet_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!bullet_up.loadFromFile("resources/images/bullet_up.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!bullet_left.loadFromFile("resources/images/bullet_left.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    if (!bullet_right.loadFromFile("resources/images/bullet_right.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_left.loadFromFile("resources/images/wall_left.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_left_right.loadFromFile("resources/images/wall_left_right.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_left_up.loadFromFile("resources/images/wall_left_up.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;

    }
    if (!wall_left_down.loadFromFile("resources/images/wall_left_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_left_right_up.loadFromFile("resources/images/wall_left_right_up.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_left_right_down.loadFromFile("resources/images/wall_left_right_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_down.loadFromFile("resources/images/wall_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_full.loadFromFile("resources/images/wall_full.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_unlit.loadFromFile("resources/images/wall_unlit.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_up.loadFromFile("resources/images/wall_up.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_up_down.loadFromFile("resources/images/wall_up_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_right.loadFromFile("resources/images/wall_right.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_right_up.loadFromFile("resources/images/wall_right_up.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_right_down.loadFromFile("resources/images/wall_right_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_left_up_down.loadFromFile("resources/images/wall_left_up_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }
    if (!wall_right_up_down.loadFromFile("resources/images/wall_right_up_down.png"))
    {
        std::cerr << "erro de textura" << std::endl;
		inited = false;
		return;
    }

    //carrega os sprites com as texturas
    spriteCross.setTexture(cross);
    spriteMap.setTexture(map);
    spriteMap.setPosition(sf::Vector2f(415, 66));
    spriteAmmoToSee.setTexture(ammo);
    spriteAmmoToSee.setPosition(sf::Vector2f(100, 10));
    spriteHeart.setTexture(h5);
    spriteHeart.setPosition(sf::Vector2f(15, 20));
    spriteFadeOut.setTexture(fade_out);
    spriteMusic.setTexture(musicplayON);
    spriteMusic.setPosition(sf::Vector2f(504, 5));
    spriteExit.setTexture(exit);
    spriteWall.setTexture(wall_full);
    spriteFloor.setTexture(floor);
    spriteTrap.setTexture(trap_off);
    spriteSpawn.setTexture(spawn);
    spriteMonster.setTexture(monster_front);
    spriteAmmo.setTexture(ammo);
    spriteMed.setTexture(med);
    spriteCharacter.setTexture(character_back);
    spriteBullet.setTexture(bullet_down);

    soundGunfire.setBuffer(gunfire); //carrega som
    soundGunfire.setVolume(40); //define volume

    zombie_awake.setBuffer(bufferZombieAwake); 
    zombie_dead.setBuffer(bufferZombieDead); 

    player_dmg.setBuffer(bufferPlayerDmg);

    player.pos() = maze.entrance(); //define posição do player na entrada do labirinto

    spriteCross.setPosition(sf::Vector2f(430+7*maze.exit().x/5, 80+7*maze.exit().y/5));
    changeXY();

    music.setLoop(true); //define que a música de fundo deve ser reproduzida em loop
}

void Game::update()
{
    player.start();
    sf::Event event; //declara evento

    while(timer.tick());
    timer.reboot();

    while(window.pollEvent(event)) //recebe os eventos e trata de forma conveniente
    {
        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::Escape) //fecha o esc
            {
                SceneManager::change_scene(Main::menucontinue);
            }
            else if (event.key.code == sf::Keyboard::Left) //quando aperta a seta esquerda
            {
                spriteCharacter.setTexture(character_left); //define textura do personagem para esquerda
                if( player.direction() == LEFT) //se a direção já é esquerda muda a posição do personagem
                {
                    player.x()--;
                    //verifica se é realmente possível se mover para essa posição
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()++;
                }
                player.direction() = LEFT; //muda a direção para esquerda 
                changeXY(); //muda as coordenadas do ponto de orientação

                b_redraw = true; //informa que precisa de update
            }
            else if (event.key.code == sf::Keyboard::Right) //quanto aperta a seta direita 
            {
                spriteCharacter.setTexture(character_right); //define textura do personagem para direita
                if( player.direction() == RIGHT) //se a direção já é esquerda muda a posição do personagem
                {
                    player.x()++;
                    //verifica se é realmente possível se mover para essa posição
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()--;
                }
                player.direction() = RIGHT; //muda a direção para direita
                changeXY(); //muda as coordenadas do ponto de orientação

                b_redraw = true; //informa que precisa de update
            }
            else if (event.key.code == sf::Keyboard::Down) //quando aperta a seta para baixo
            {
                spriteCharacter.setTexture(character_front); //define a textura do personagem para frente
                if( player.direction() == DOWN) //se a direção já é para baixo muda a posição do personagem
                {
                    player.y()++; 
                    //verifica se é realmente possível se mover para essa posição
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()--;
                }
                player.direction() = DOWN; //muda direção para baixo
                changeXY(); //muda as coordenadas do ponto de orientação

                b_redraw = true; //informa que precisa de update
            }
            else if (event.key.code == sf::Keyboard::Up) //quando aperta a seta para cima 
            {
                spriteCharacter.setTexture(character_back); //define a textura do personagem para cima
                if( player.direction() == UP) //se a direção já é para cima muda a posição do personagem
                {
                    player.y()--;
                    //verifica se é realmente possível se mover para essa posição
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()++;
                }
                player.direction() = UP; //muda direção para cima
                changeXY(); //muda as coordenadas do ponto de orientação 

                b_redraw = true; //informa que precisa de update
            }
            else if (event.key.code == sf::Keyboard::Z) //para pegar um item
            {
                useAmount(); //função que pega o item caso haja um na posição atual do personagem
       
                b_redraw = true; //informa que precisa de update
            }
            else if (event.key.code == sf::Keyboard::Space && bullet_course.empty()) //atira apertando no space
            {
                if(player.ammo() > 0) //se tiver munição
                {
                    player.ammo_fire(); //altera a quantidade de munĩção
                    fire(); //função que atira
                }

                b_redraw = true; //informa que precisa de update
            }
            if(player.pos() == maze.exit()) //caso a posição do personagem seja a saída
            {
                if(level == 3 ) //se ele já estiver no level 3 então o jogo termina e ele ganhou
                {
                    playMusic(false); //para de tocar a música
                    player.end(); //registra o momento que terminou o jogo
                    player.add_points(100); //adiciona pontos por ter terminado
                    SceneManager::change_scene(Main::endgame); //muda a cena para o endgame
                }
                else
                {
                	changeLevel(level+1); //chama método que muda o level
                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //se apertar no botão do som
                if(event.mouseButton.x > 520 && event.mouseButton.x < 544 && event.mouseButton.y > 25 && event.mouseButton.y < 40)
                {
                    if(playing){ //muda para mudo caso esteja com som
                        playMusic(false); //função que torna mudo
                        spriteMusic.setTexture(musicplayOFF); //muda a textura
                    }
                    else{ //muda para reproduzir som caso esteja mudo
                        playMusic(true); //função que passa a reproduzir
                        spriteMusic.setTexture(musicplayON); //muda a textura
                    }
                    b_redraw = true; //necessário update
                }
            }
        }
    }

    list<Enemy>::iterator it; //declaração de iterador do tipo Enemy
    for (it = enemies.begin(); it != enemies.end();)
    {
        if (it->hit_player()) //se algum monstro estiver em choque com o player
        {
            player.add_points(-30); //perde pontos

            enemies.erase(it++); //tira o monstro da lista

            if (playing) //se tiver som 
            {
                int value = 100*(4-(player.pos().distance_to(it->pos())-1))/4; //alteração do volume conforme aproximação do monstro
                zombie_dead.setVolume(value);
                zombie_dead.play(); //toca o som

                player_dmg.play();
            }

            b_redraw = true; //precisa de update
        }
        else if (it->hit_bullet()) //se a bala atinge um monstro
        {
            player.add_points(20); //adiciona pontos

            enemies.erase(it++); //tira o monstro da lista
            bullet_course.clear(); //limpa a trajetória da bala

            if (playing) //se tiver som ativo
            {
                int value = 100*(4-(player.pos().distance_to(it->pos())-1))/4; //altera o volume conforme posição da bala
                zombie_dead.setVolume(value);
                zombie_dead.play(); //toca o som
            }

            b_redraw = true; //precisa de update
        }
        else
        {
            if (it->is_chasing()) //se está perseguindo 
            {
                it->chase(player, maze, bullet_course); 
                b_redraw = true;
            }
            else if (player.can_see(*it)) //se está no campo de visão do player 
            {
                if (!it->inited_awake()) it->init_awake(); 
                else if (!it->is_awake())
                {
                    it->awake();
                    b_redraw = true;
                }
                else if (!it->is_chasing()) it->init_chase();

                if (it->is_awake() && playing)
                {
                    int value = 100*(4-(player.pos().distance_to(it->pos())-1))/4;
                    zombie_awake.setVolume(value);
                    zombie_awake.play();
                }
            }

            ++it;
        }
    }

    if (!bullet_course.empty() && !player.can_see(bullet_course.front())) 
        bullet_course.pop();

    if (player.hp() <= 0) //se o hp chegar a zero
    {
        playMusic(false); //tira a música
        changeLevel(1); //muda o level
        player.end(); //registra o tempo
        player.add_points(-100); //tira pontos por ter perdido
        SceneManager::change_scene(Main::endgame); //muda a cena para endgame
        restart(); //reinicia as informações do jogo
    }

    int old_hp;
    std::stringstream ss(player_hp.getString());
    ss >> old_hp; //converte hp string para int
    if (old_hp != player.hp()) //se for diferente do anterior
    {
        //muda a textura do coração 
        if (0 < player.hp() && player.hp() <= Player::max_hp/5)
            spriteHeart.setTexture(h1);
        else if (Player::max_hp/5 < player.hp() && player.hp() <= 2*Player::max_hp/5)
            spriteHeart.setTexture(h2);
        else if (2*Player::max_hp/5 < player.hp() && player.hp() <= 3*Player::max_hp/5)
            spriteHeart.setTexture(h3);
        else if (3*Player::max_hp/5 < player.hp() && player.hp() <= 4*Player::max_hp/5)
            spriteHeart.setTexture(h4);
        else if (4*Player::max_hp/5 < player.hp() && player.hp() <= Player::max_hp)
            spriteHeart.setTexture(h5);

        std::stringstream ss1;
        ss1 << player.hp() << "hp";

        player_hp.setString(ss1.str()); //define a string de player_hp

        b_redraw = true; //precisa de update
    }

    active_traps(); //função que ativa/desativa armadilhas
    for(list<Trap>::iterator it = traps.begin(); it != traps.end(); it++) //percorre a lista de armadilhas
    {
        if(it->is_active() && it->pos() == player.pos()) //caso o personagem esteja na mesma posição de uma armadilha ativa
        {
            player.add_points(-10); //tira pontos
            player.hp()--; //tira hp
            player_dmg.play(); //áudio 
        }
    }
}

//Método que verifica se tem um item na posição do personagem
void Game::useAmount()
{
    int i;
    Item t(Item::HEAL);
    list<Item>::iterator it;
    for(it = hearts.begin(), i = 0; it != hearts.end(); it++, i++) //percorre a lista de medkit
    {
        t = *it;
        if(t.pos() == player.pos()) //se está na posição do personagem
        {
            t = hearts.erase(i); //tira esse item da lista
            player.get(t); //pega o item para o player (muda quantidade de hp)

            //altera a textura do coração conforme quantidade de hp
            if (0 < player.hp() && player.hp() <= Player::max_hp/5)
                spriteHeart.setTexture(h1);
            else if (Player::max_hp/5 < player.hp() && player.hp() <= 2*Player::max_hp/5)
                spriteHeart.setTexture(h2);
            else if (2*Player::max_hp/5 < player.hp() && player.hp() <= 3*Player::max_hp/5)
                spriteHeart.setTexture(h3);
            else if (3*Player::max_hp/5 < player.hp() && player.hp() <= 4*Player::max_hp/5)
                spriteHeart.setTexture(h4);
            else if (4*Player::max_hp/5 < player.hp() && player.hp() <= Player::max_hp)
                spriteHeart.setTexture(h5);

            std::stringstream ss;
            ss << player.hp() << "hp"; //reescreve hp
            player_hp.setString(ss.str());
            player.add_points(30); //adiciona pontos por pegar item
            return;
        }
    }
    for(it = ammuns.begin(), i = 0; it != ammuns.end(); it++, i++) //percorre a lista de munições 
    {
        t = *it;
        if(t.pos() == player.pos()) //caso tenha uma munição na posição atual do player
        {
            t = ammuns.erase(i); //tira a munição da lista
            player.get(t); //pega a munição para o player (altera a quantidade)
            player.add_points(30); //adiciona pontos por pegar item
            std::stringstream ss;
            ss << player.ammo() << "ammo"; //reescreve ammo
            player_ammo.setString(ss.str());

            return;
        }
    }
}

//Método que ativa/desativa as armadilhas
void Game::active_traps()
{
    for(list<Trap>::iterator i = traps.begin(); i != traps.end(); i++) //percorre a lista de armadilhas
    {
        if(i->is_active()) //caso esteja ativada
        {
            i->disactivate(); //desativa
        }
        else{ //se não 
            i->activate(); //ativa
        }
        b_redraw = true; //precisa de update
    }
}

//Retorna verdadeiro caso na posição i, j haja um monstro
bool Game::showMonster(int i, int j)
{
    Position a(i, j);
    for(list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); i++) //percorre a lista de monstros
    {
        if(i->pos() == a && i->is_awake()) //se estiver acordado
        {
            if (i->direction() == UP) spriteMonster.setTexture(monster_back); //muda a textura conforme direção
            else if (i->direction() == DOWN) spriteMonster.setTexture(monster_front);
            else if (i->direction() == LEFT) spriteMonster.setTexture(monster_left);
            else if (i->direction() == RIGHT) spriteMonster.setTexture(monster_right);

            return true; //retorna verdadeiro
        }
    }
    return false; 
}

//Retorna verdadeiro caso haja um spawn na posição i, j
bool Game::showSpawn(int i, int j)
{
    Position a(i, j);
    for(list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); i++) //percorre a lista de enemies
    {
        if(i->pos() == a && !i->is_awake()) return true; 
    }
    return false;
}

//Retorna verdadeiro caso haja um medkit na posição i, j
bool Game::showMed(int i, int j)
{
    Position a(i, j);
    for(list<Item>::iterator i = hearts.begin(); i != hearts.end(); i++) //percorre a lista de medkits
    {
        if(i->pos() == a) return true;
    }
    return false;
}

//Retorna verdadeiro se tiver uma armadilha na posição i, j
bool Game::showTrap(int i, int j)
{
    Position a(i, j);
    for(list<Trap>::iterator i = traps.begin(); i != traps.end(); i++)
    {
        if(i->pos() == a && !i->is_active()) //se estiver ativa
        {
            spriteTrap.setTexture(trap_on); //muda a textura para ativada
            return true;
        }
        else if(i->pos() == a && i->is_active())
        {
            spriteTrap.setTexture(trap_off); //muda a textura para desativada
            return true;
        }
    }
    return false;
}

//Retorna verdadeiro caso haja uma munição na posição i, j
bool Game::showAmmo(int i, int j)
{
    Position a(i, j);
    for(list<Item>::iterator i = ammuns.begin(); i != ammuns.end(); i++) //percorre a lista de ammuns
    {
        if(i->pos() == a) return true;
    }
    return false;
}

//Método que atira (e define o percurso da bala)
void Game::fire()
{
    if (playing) //ativa só caso não esteja mudo
        soundGunfire.play();

    Entity bullet(player.x(), player.y()); // cria uma entidade para representar a bala, inicializando-a com a posição do jogador

    // de acordo com a direção do jogador, a direção da bala e seu percurso são definidos. o percurso é uma fila de posições que começa na adjacente ao jogador e termina na que precede uma parede (todas as posições do corredor que a bala vai percorrer).
    if (player.direction() == LEFT)
    {
        spriteBullet.setTexture(bullet_left); // define o sprite correspondente a direção da bala
        bullet.x()--; // passa a posição da bala, que estava como a mesma do jogador, para a adjacente a esta na direção correta (primeira posição do percurso da bala)
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            bullet_course.push( bullet.pos() ); // enquanto a posição da bala está em um caminho (faz parte do percurso), ela é adicionada à fila
            bullet.x()--; // posição da bala é atualizada para a seguinte na direção correta
        }
    }
    else if (player.direction() == RIGHT)
    {
        spriteBullet.setTexture(bullet_right);
        bullet.x()++;
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            bullet_course.push( bullet.pos() );
            bullet.x()++;
        }
    }
    else if (player.direction() == UP)
    {
        spriteBullet.setTexture(bullet_up);
        bullet.y()--;
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            bullet_course.push( bullet.pos() );
            bullet.y()--;
        }
    }
    else
    {
        spriteBullet.setTexture(bullet_down);
        bullet.y()++;
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            bullet_course.push( bullet.pos() );
            bullet.y()++;
        }
    }
    std::stringstream ss1;
    ss1 << player.ammo() << "ammo";
    player_ammo.setString(ss1.str()); //muda a quantidade de munição para o player ver
}

//Método que define qual parede deve ser usada na posição i, j
void Game::define_wall (int i, int j)
{
    
    // são definidas 4 variáveis booleanas (l, r, u, d) que indicam se as 4 posições adjacentes à que eu que eu quero definir são paredes (true) ou não (false)
    Position pos(i-1, j);
    bool l = false, r = false, u = false, d = false;
    if (!maze.in_bounds(pos) || maze[i-1][j].type() == Block::WALL)
        l = true;
    pos.x += 2;
    if (!maze.in_bounds(pos) || maze[i+1][j].type() == Block::WALL)
        r = true;
    pos.x--;
    pos.y--;
    if (!maze.in_bounds(pos) || maze[i][j-1].type() == Block::WALL)
        u = true;
    pos.y += 2;
    if (!maze.in_bounds(pos) || maze[i][j+1].type() == Block::WALL)
        d = true;
    
    
    // existem 16 casos diferentes de paredes (com nenhuma parede em volta, com paredes 4 paredes em volta, com 1 parede em cima, com 2 paredes sendo uma em cima e outra do lado, etc). para cada um desses casos, existe um sprite diferente, que é definido a seguir (checando as paredes em volta):
    if (u)
    {
        if (!l && !r && !d)
            spriteWall.setTexture(wall_left_right_down);
        else if (!l && r && !d)
            spriteWall.setTexture(wall_left_down);
        else if (!l && !r && d)
            spriteWall.setTexture(wall_left_right);
        else if (!l && r && d)
            spriteWall.setTexture(wall_left);
        else if (l && !r && !d)
            spriteWall.setTexture(wall_right_down);
        else if (l && r && !d)
            spriteWall.setTexture(wall_down);
        else if (l && r && d)
            spriteWall.setTexture(wall_unlit); // exemplo: nesse caso, todas as variáveis são verdadeiras, indicando que há paredes nas 4 posições adjacentes. o sprite é então definido para o correspondente a esse caso
        else if(l && !r && d)
            spriteWall.setTexture(wall_right);
    }
    else if (!u && d)
    {
        if (!l && !r)
            spriteWall.setTexture(wall_left_right_up);
        else if (l && !r)
            spriteWall.setTexture(wall_right_up);
        else if (!l && r)
            spriteWall.setTexture(wall_left_up);
        else if (l && r)
            spriteWall.setTexture(wall_up);
    }
    else if (!u && !d)
    {
        if (l && r)
            spriteWall.setTexture(wall_up_down);
        else if (l && !r)
            spriteWall.setTexture(wall_right_up_down);
        else if (!l && r)
            spriteWall.setTexture(wall_left_up_down);
        else if (!l && !r)
            spriteWall.setTexture(wall_full);
    }

}

//Método que redesenha na janela tudo que foi alterado
void Game::redraw()
{
    if (b_redraw)
    {
        window.clear(sf::Color(51, 34, 60));

        int y = (WINDOW_HEIGHT - 9*56)/2;
        for( int j = player.y()-4; j <= player.y()+4; j++, y+=56 ) //detenha na janela de 4 blocos antes do player a 4 blocos depois do player
        {
            window.clear(sf::Color(51, 34, 60)); //limpa a tela com a cor definida por RGB

            int y = (WINDOW_HEIGHT - 9*56)/2; //cálculo do valor de y
            for( int j = player.y()-4; j <= player.y()+4; j++, y+=56 )
            {
            	int x = (WINDOW_WIDTH - 9*56)/2;
                for( int i = player.x()-4; i <= player.x()+4; i++, x+=56 )
                {
                    if( maze.in_bounds(Position(i, j)) )
                    {
                        if (maze[i][j].type() == Block::FLOOR) //se for chão 
                        {
                            spriteFloor.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteFloor);
                        }
                        else
                        { //se for parede
                            define_wall(i, j);
                            spriteWall.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteWall);
                        }
                        if(showSpawn(i, j)) //desenha spawn caso haja um
                        {
                            spriteSpawn.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteSpawn);
                        }

                        Position a(i, j);
                        if(maze.exit() == a) //desenha a saída
                        {
                            spriteExit.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteExit);
                        }

                        if(showAmmo(i, j)) //desenha munição
                        {
                            spriteAmmo.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteAmmo);
                        }

                        if(showMed(i, j)) //desenha medkit
                        {
                            spriteMed.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteMed);
                        }

                        if(showTrap(i, j)) //desenha armadilha
                        {
                            spriteTrap.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteTrap);
                        }

                        if(!bullet_course.empty() && bullet_course.front().x == i && bullet_course.front().y == j) //desenha bala
                        {
                            spriteBullet.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteBullet);
                            bullet_course.pop(); //tira uma posição percorrida pela bala
                        }

                        if(showMonster(i, j)) //mostra monstro
                        {
                            spriteMonster.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteMonster);
                        }

                        if(player.x() == i && player.y() == j) //mostra player
                        {
                            spriteCharacter.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteCharacter);
                        }
                    }
                }
            }
            //desenha os sprites
			window.draw(spriteMap);
			window.draw(spriteCross);
			window.draw(circle);
			window.draw(spriteFadeOut);
            window.draw(player_hp);
            window.draw(player_ammo);
            window.draw(spriteMusic);
			window.draw(spriteHeart);
			window.draw(spriteAmmoToSee);
            window.draw(player_level);
            window.display();
        }

        b_redraw = false; //não precisa de update 
    }
}

//Método que reinicia o jogo
void Game::restart()
{
    ammuns.clear(); //limpa as listas
	hearts.clear();
	traps.clear();
	enemies.clear();
    bullet_course.clear();

    player.pos() = maze.entrance(); //muda a posição do player
    player.direction() = UP; //muda direção
    player.hp() = Player::max_hp; //muda quantidade de hp 
    player.ammo() = Player::max_ammo; //muda quantidade de munição

    std::stringstream ss;
    ss << player.hp() << "hp"; //muda a quantidade de hp (que aparece na tela)
    player_hp.setString(ss.str()); //define o conteúdo de player_hp

    std::stringstream ss1;
    ss1 << player.ammo() << "ammo"; //muda a quantidade de ammo (qua aparece na tela)
    player_ammo.setString(ss1.str()); //define o conteúdo de player_ammo

    spriteCharacter.setTexture(character_back); //muda a textura do sprite do player
    spriteHeart.setTexture(h5); //muda a textura do coração 
    read_from_file(); //faz releitura do arquivo 
}

//Método que calcula a posição do ponto vermelho que orienta o player no labirinto
void Game::changeXY()
{
    xX = 7*player.x()/5;
    yY = 7*player.y()/5;
    circle.setPosition(sf::Vector2f(430+xX, 80+yY));
}

//Método que muda o level do jogo
void Game::changeLevel(int lvl) //recebe int que indica o level
{
    if(lvl != 1) //se level diferente de 1
    {
        player.p_end(); //adiciona pontos, pois o player passou de fase
        player.add_points(player.end()- player.start());
    }
    level = lvl; //muda o valor de level
    ammuns.clear(); //limpa as listas 
    hearts.clear();
    traps.clear();
    enemies.clear();
    bullet_course.clear();
    maze.maze_null(); //torna a matriz do maze nula novamente

    if(!read_from_file(level)) //leitura do arquivo
    {
        std::cerr << "erro com a entrada" << std::endl; //caso haja erro informa no terminal essa mensagem
        Main::quit = true; //fecha o jogo
    }

    player.pos() = maze.entrance(); //muda posição do player
    player.direction() = UP; //muda a direção

    std::stringstream ss;
    ss << player.hp() << "hp"; 
    player_hp.setString(ss.str()); //define o conteúdo de player_hp

    std::stringstream ss1;
    ss1 << player.ammo() << "ammo";
    player_ammo.setString(ss1.str()); //define o conteúdo de player_ammo

    std::stringstream ss2;
    ss2 << "level" << level;
    player_level.setString(ss2.str()); //define o conteúdo de player_level
    changeXY(); //muda a posição do ponto vermelho de orientação
    spriteCross.setPosition(sf::Vector2f(430+7*maze.exit().x/5, 80+7*maze.exit().y/5)); //muda o x que indica onde fica a saída no mini mapa
    spriteCharacter.setTexture(character_back); //muda a textura do sprite do player
}
