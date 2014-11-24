
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
        entrada.open( "levels/entrada.txt", std::ifstream::in ); // Abre o arquivo "entrada.txt".
    else if( i == 2 )
        entrada.open( "levels/entrada2.txt", std::ifstream::in );
    else
        entrada.open( "levels/entrada3.txt", std::ifstream::in );

    if( entrada.is_open() )
    {
        int a, b;

        if( !(entrada >> a) )
        {
            entrada.close();
            std::cout << "não leu a" << std::endl;
            return false;
        }
        if( !(entrada >> b) )
        {
            entrada.close();
            std::cout << "não leu a" << std::endl;
            return false;
        }

        maze.init(a, b);

        int j;
        for (j=0; j<b; j++)
        {
            for (int i=0; i<a; i++)
            {
                int x;
                entrada >> x;

                if (x == 1) maze[i][j].type() = Block::WALL;
                else
                {
                    maze[i][j].type() = Block::FLOOR;

                    if (x == 2) maze.entrance() = Position(i, j);
                    else if (x == 3) maze.exit() = Position(i, j);
                    else if (x == 4)
                    {
                        Trap t;
                        t.pos() = Position(i, j);
                        traps.push_back(t);
                    }
                    else if (x == 5)
                    {
                        Enemy s(Enemy::SLEEP);
                        s.pos() = Position(i, j);
                        enemies.push_back(s);
                    }
                    else if (x == 6)
                    {
                        Item h(Item::HEAL);
                        h.pos() = Position(i, j);
                        hearts.push_back(h);
                    }
                    else if (x == 7)
                    {
                        Item a(Item::AMMO);
                        a.pos() = Position(i, j);
                        ammuns.push_back(a);
                    }
                    else if (x == 8)
                    {
                        Enemy e(Enemy::AWAKE);
                        e.pos() = Position(i, j);
                        enemies.push_back(e);
                    }
                }
            }
        }

        // Verifica se a leitura da matriz ocorreu corretamente.
        if( j != b ) {
            std::cout << "não leu matriz" << std::endl;
            entrada.close();
            return false;
        }
    }
    else {
        std::cout << "não abriu arquivo" << std::endl;
        entrada.close();
        return false;
    }

    entrada.close();

    return verify_maze(maze);
}


bool Game::verify_maze(Maze& maze)
{
    stack<Position> dfs;
    stack<Position> marked;

    dfs.push(maze.entrance());

    while (!dfs.empty() && dfs.top() != maze.exit())
    {
        marked.push(dfs.top());

        Position left = get_adjacent(dfs.top(), LEFT);
        Position right = get_adjacent(dfs.top(), RIGHT);
        Position up = get_adjacent(dfs.top(), UP);
        Position down = get_adjacent(dfs.top(), DOWN);

        if (maze.in_bounds(left) && maze[left.x][left.y].type() == Block::FLOOR && !marked.includes(left))
            dfs.push(left);
        else if (maze.in_bounds(right) && maze[right.x][right.y].type() == Block::FLOOR && !marked.includes(right))
            dfs.push(right);
        else if (maze.in_bounds(up) && maze[up.x][up.y].type() == Block::FLOOR && !marked.includes(up))
            dfs.push(up);
        else if (maze.in_bounds(down) && maze[down.x][down.y].type() == Block::FLOOR && !marked.includes(down))
            dfs.push(down);
        else dfs.pop();
    }

    return !dfs.empty();
}


Game::Game()
: timer(1000000.0/FPS), inited(true), circle(3, 15), level(1)
{
    if (!read_from_file()) inited = false;

    if (!font.loadFromFile("resources/fonts/Fixedsys500c.ttf"))
    {
        std::cout << "erro de fonte" << std::endl;
    }

    circle.setFillColor(sf::Color::Red);

    player_hp.setCharacterSize(20);
    player_hp.setFont(font);
    player_hp.setColor(sf::Color::White);

    std::stringstream ss;
    ss << player.hp() << "hp";
    player_hp.setString(ss.str());

    player_hp.setPosition(sf::Vector2f(50, 30));

    player_ammo.setCharacterSize(20);
    player_ammo.setFont(font);
    player_ammo.setColor(sf::Color::White);

    std::stringstream ss1;
    ss1 << player.ammo() <<"ammo";
    player_ammo.setString(ss1.str());

    player_ammo.setPosition(sf::Vector2f(150, 30));

	player_level.setCharacterSize(20);
    player_level.setFont(font);
    player_level.setColor(sf::Color::White);

    std::stringstream ss3;
    ss3 << "level" << level;
    player_level.setString(ss3.str());

    player_level.setPosition(sf::Vector2f(250, 30));


	if (!cross.loadFromFile("resources/images/cross.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!map.loadFromFile("resources/images/map.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!h1.loadFromFile("resources/images/heart1.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!h2.loadFromFile("resources/images/heart2.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!h3.loadFromFile("resources/images/heart3.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!h4.loadFromFile("resources/images/heart4.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!h5.loadFromFile("resources/images/heart5.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!music.openFromFile("resources/sounds/maze_music.ogg"))
    {
        std::cout << "erro" << std::endl;
    }

    if (!gunfire.loadFromFile("resources/sounds/gunfire_effect.ogg"))
    {
        std::cout << "erro" << std::endl;
    }

    if (!musicplayON.loadFromFile("resources/images/volume.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!musicplayOFF.loadFromFile("resources/images/mudo.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!bufferZombieAwake.loadFromFile("resources/sounds/alive_effect.flac"))
    {
        std::cout << "erro" << std::endl;
    }

    if (!bufferZombieDead.loadFromFile("resources/sounds/dead_effect.flac"))
    {
        std::cout << "erro" << std::endl;
    }

    if (!fade_out.loadFromFile("resources/images/fade_out.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!exit.loadFromFile("resources/images/exit.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!floor.loadFromFile("resources/images/floor1.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!trap_off.loadFromFile("resources/images/trap_off3.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!trap_on.loadFromFile("resources/images/trap_on3.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!spawn.loadFromFile("resources/images/spawn1.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!monster_front.loadFromFile("resources/images/skeleton_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!monster_back.loadFromFile("resources/images/skeleton_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!monster_left.loadFromFile("resources/images/skeleton_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!monster_right.loadFromFile("resources/images/skeleton_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!ammo.loadFromFile("resources/images/ammo.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!med.loadFromFile("resources/images/medkit.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!character_back.loadFromFile("resources/images/char_back.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!character_front.loadFromFile("resources/images/char_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!character_left.loadFromFile("resources/images/char_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!character_right.loadFromFile("resources/images/char_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!bullet_down.loadFromFile("resources/images/bullet_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!bullet_up.loadFromFile("resources/images/bullet_up.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!bullet_left.loadFromFile("resources/images/bullet_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

    if (!bullet_right.loadFromFile("resources/images/bullet_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_left.loadFromFile("resources/images/wall_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_left_right.loadFromFile("resources/images/wall_left_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_left_up.loadFromFile("resources/images/wall_left_up.png"))
    {
        std::cout << "erro de textura" << std::endl;

    }
    if (!wall_left_down.loadFromFile("resources/images/wall_left_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_left_right_up.loadFromFile("resources/images/wall_left_right_up.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_left_right_down.loadFromFile("resources/images/wall_left_right_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_down.loadFromFile("resources/images/wall_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_full.loadFromFile("resources/images/wall_full.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_unlit.loadFromFile("resources/images/wall_unlit.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_up.loadFromFile("resources/images/wall_up.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_up_down.loadFromFile("resources/images/wall_up_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_right.loadFromFile("resources/images/wall_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_right_up.loadFromFile("resources/images/wall_right_up.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_right_down.loadFromFile("resources/images/wall_right_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_left_up_down.loadFromFile("resources/images/wall_left_up_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }
    if (!wall_right_up_down.loadFromFile("resources/images/wall_right_up_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
    }

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

    soundGunfire.setBuffer(gunfire);
    soundGunfire.setVolume(40);

    player.pos() = maze.entrance();

    spriteCross.setPosition(sf::Vector2f(430+7*maze.exit().x/5, 80+7*maze.exit().y/5));
    changeXY();

    zombie_awake.setBuffer(bufferZombieAwake);
    zombie_dead.setBuffer(bufferZombieDead);

    music.setLoop(true);
}

void Game::update()
{
    player.start();
    sf::Event event;

    while(timer.tick());
    timer.reboot();

    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) //fecha o jogo caso aperte esc
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                SceneManager::change_scene(Main::menucontinue);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                spriteCharacter.setTexture(character_left);
                if( player.direction() == LEFT)
                {
                    player.x()--;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()++;
                }
                player.direction() = LEFT;
                changeXY();

                b_redraw = true;
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                spriteCharacter.setTexture(character_right);
                if( player.direction() == RIGHT)
                {
                    player.x()++;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.x()--;
                }
                player.direction() = RIGHT;
                changeXY();

                b_redraw = true;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                spriteCharacter.setTexture(character_front);
                if( player.direction() == DOWN)
                {
                    player.y()++;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()--;
                }
                player.direction() = DOWN;
                changeXY();

                b_redraw = true;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                spriteCharacter.setTexture(character_back);
                if( player.direction() == UP)
                {
                    player.y()--;
                    if (!maze.in_bounds(player.pos()) || maze[player.x()][player.y()].type() == Block::WALL) player.y()++;
                }
                player.direction() = UP;
                changeXY();

                b_redraw = true;
            }
            else if (event.key.code == sf::Keyboard::Z)
            {
                useAmount();
                player.add_points(30);
                b_redraw = true;
            }
            else if (event.key.code == sf::Keyboard::Space && bullet_course.empty())
            {
                if(player.ammo() > 0)
                {
                    player.ammo_fire();
                    fire();
                }

                b_redraw = true;
            }
            if(player.pos() == maze.exit())
            {
                if(level == 3 )
                {
                    playMusic(false);
                    player.end();
                    player.add_points(100);
                    SceneManager::change_scene(Main::endgame);
                }
                else
                {
                changeLevel(level+1);
                                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(event.mouseButton.x > 520 && event.mouseButton.x < 544 && event.mouseButton.y > 25 && event.mouseButton.y < 40)
                {
                    if(playing){
                        playMusic(false);
                        spriteMusic.setTexture(musicplayOFF);
                    }
                    else{
                        playMusic(true);
                        spriteMusic.setTexture(musicplayON);
                    }
                    b_redraw = true;
                }
            }
        }
    }

    list<Enemy>::iterator it;
    for (it = enemies.begin(); it != enemies.end();)
    {
        if (it->hit_player())
        {
            player.add_points(-30);

            enemies.erase(it++);

            int value = 100*(4-(player.pos().distance_to(it->pos())-1))/4;
            zombie_dead.setVolume(value);

            if (playing) zombie_dead.play();

            b_redraw = true;
        }
        else if (it->hit_bullet())
        {
            player.add_points(20);

            enemies.erase(it++);
            bullet_course.clear();

            int value = 100*(4-(player.pos().distance_to(it->pos())-1))/4;
            zombie_dead.setVolume(value);

            if (playing) zombie_dead.play();

            b_redraw = true;
        }
        else
        {
            if (it->is_chasing())
            {
                it->chase(player, maze, bullet_course);
                b_redraw = true;
            }
            else if (player.can_see(*it))
            {
                if (!it->inited_awake()) it->init_awake();
                else if (!it->is_awake())
                {
                    it->awake();
                    b_redraw = true;
                }
                else if (!it->is_chasing()) it->init_chase();

                if (it->is_awake())
                {
                    int value = 100/(player.pos().distance_to(it->pos())-1);

                    zombie_awake.setVolume(value);
                    if (playing) zombie_awake.play();
                }
            }

            ++it;
        }
    }

    if (!bullet_course.empty() && !player.can_see(bullet_course.front()))
        bullet_course.pop();

    if (player.hp() <= 0)
    {
        playMusic(false);
        changeLevel(1);
        player.end();
        player.add_points(-100);
        SceneManager::change_scene(Main::endgame);
        restart();
    }

    int old_hp;
    std::stringstream ss(player_hp.getString());
    ss >> old_hp;
    if (old_hp != player.hp())
    {
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

        player_hp.setString(ss1.str());

        b_redraw = true;
    }

    active_traps();
    for(list<Trap>::iterator it = traps.begin(); it != traps.end(); it++)
    {
        if(it->pos() == player.pos())
        {
            player.add_points(-10);
            player.hp()--;
        }
    }
}


void Game::useAmount()
{
    int i;
    Item t(Item::HEAL);
    list<Item>::iterator it;
    for(it = hearts.begin(), i = 0; it != hearts.end(); it++, i++)
    {
        t = *it;
        if(t.pos() == player.pos())
        {
            t = hearts.erase(i);
            player.get(t);

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
            ss << player.hp() << "hp";
            player_hp.setString(ss.str());

            return;
        }
    }
    for(it = ammuns.begin(), i = 0; it != ammuns.end(); it++, i++)
    {
        t = *it;
        if(t.pos() == player.pos())
        {
            t = ammuns.erase(i);
            player.get(t);

            std::stringstream ss;
            ss << player.ammo() << "ammo";
            player_ammo.setString(ss.str());

            return;
        }
    }
}

void Game::active_traps()
{
    for(list<Trap>::iterator i = traps.begin(); i != traps.end(); i++)
    {
        if(i->is_active())
        {
            i->disactivate();
        }
        else{
            i->activate();
        }
        b_redraw = true;
    }
}


bool Game::showMonster(int i, int j)
{
    Position a(i, j);
    for(list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
        if(i->pos() == a && i->is_awake())
        {
            if (i->direction() == UP) spriteMonster.setTexture(monster_back);
            else if (i->direction() == DOWN) spriteMonster.setTexture(monster_front);
            else if (i->direction() == LEFT) spriteMonster.setTexture(monster_left);
            else if (i->direction() == RIGHT) spriteMonster.setTexture(monster_right);

            return true;
        }
    }
    return false;
}

bool Game::showSpawn(int i, int j)
{
    Position a(i, j);
    for(list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); i++)
    {
        if(i->pos() == a && !i->is_awake()) return true;
    }
    return false;
}


bool Game::showMed(int i, int j)
{
    Position a(i, j);
    for(list<Item>::iterator i = hearts.begin(); i != hearts.end(); i++)
    {
        if(i->pos() == a) return true;
    }
    return false;
}

bool Game::showTrap(int i, int j)
{
    Position a(i, j);
    for(list<Trap>::iterator i = traps.begin(); i != traps.end(); i++)
    {
        if(i->pos() == a && !i->is_active())
        {
            spriteTrap.setTexture(trap_on);
            return true;
        }
        else if(i->pos() == a && i->is_active())
        {
            spriteTrap.setTexture(trap_off);
            return true;
        }
    }
    return false;
}

bool Game::showAmmo(int i, int j)
{
    Position a(i, j);
    for(list<Item>::iterator i = ammuns.begin(); i != ammuns.end(); i++)
    {
        if(i->pos() == a) return true;
    }
    return false;
}

void Game::fire()
{
    if (playing)
        soundGunfire.play();

    Entity bullet(player.x(), player.y());

    Position pos;
    if (player.direction() == LEFT)
    {
        spriteBullet.setTexture(bullet_left);
        bullet.x()--;
        while (maze.in_bounds(bullet.pos()) && maze[bullet.x()][bullet.y()].type() != Block::WALL)
        {
            bullet_course.push( bullet.pos() );
            bullet.x()--;
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
    player_ammo.setString(ss1.str());
}

void Game::define_wall (int i, int j)
{
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
            spriteWall.setTexture(wall_unlit);
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

void Game::redraw()
{
    if (b_redraw)
    {
        window.clear(sf::Color(51, 34, 60));

        int y = (WINDOW_HEIGHT - 9*56)/2;
        for( int j = player.y()-4; j <= player.y()+4; j++, y+=56 )
        {
            window.clear(sf::Color(51, 34, 60));

            int y = (WINDOW_HEIGHT - 9*56)/2;
            for( int j = player.y()-4; j <= player.y()+4; j++, y+=56 )
            {
            	int x = (WINDOW_WIDTH - 9*56)/2;
                for( int i = player.x()-4; i <= player.x()+4; i++, x+=56 )
                {
                    if( maze.in_bounds(Position(i, j)) )
                    {
                        if (maze[i][j].type() == Block::FLOOR)
                        {
                            spriteFloor.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteFloor);
                        }
                        else
                        {
                            define_wall(i, j);
                            spriteWall.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteWall);
                        }
//a partir daqui
                        if(showSpawn(i, j))
                        {
                            spriteSpawn.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteSpawn);
                        }

                        Position a(i, j);
                        if(maze.exit() == a)
                        {
                            spriteExit.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteExit);
                        }

                        if(showAmmo(i, j))
                        {
                            spriteAmmo.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteAmmo);
                        }

                        if(showMed(i, j))
                        {
                            spriteMed.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteMed);
                        }

                        if(showTrap(i, j))
                        {
                            spriteTrap.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteTrap);
                        }

                        if(!bullet_course.empty() && bullet_course.front().x == i && bullet_course.front().y == j)
                        {
                            spriteBullet.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteBullet);
                            bullet_course.pop();
                        }

                        if(showMonster(i, j))
                        {
                            spriteMonster.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteMonster);
                        }

                        if(player.x() == i && player.y() == j)
                        {
                            spriteCharacter.setPosition(sf::Vector2f(x, y));
                            window.draw(spriteCharacter);
                        }
                    }
                }
            }

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

        b_redraw = false;
    }
}

void Game::restart()
{
    ammuns.clear();    // A definir.
	hearts.clear();
	traps.clear();
	enemies.clear();
    bullet_course.clear();

    player.pos() = maze.entrance();
    player.direction() = UP;
    player.hp() = Player::max_hp;
    player.ammo() = Player::max_ammo;

    std::stringstream ss;
    ss << player.hp() << "hp";
    player_hp.setString(ss.str());

    std::stringstream ss1;
    ss1 << player.ammo() << "ammo";
    player_ammo.setString(ss1.str());

    spriteCharacter.setTexture(character_back);
    spriteHeart.setTexture(h5);
    read_from_file();
}

void Game::changeXY()
{
    xX = 7*player.x()/5;
    yY = 7*player.y()/5;
    circle.setPosition(sf::Vector2f(430+xX, 80+yY));
}

void Game::changeLevel(int lvl)
{
    if(lvl != 1)
    {
        player.p_end();
        player.add_points(player.end()- player.start());
    }
    level = lvl;
    ammuns.clear();    // A definir.
    hearts.clear();
    traps.clear();
    enemies.clear();
    bullet_course.clear();
    maze.maze_null();
    if(!read_from_file(level))
    {
        std::cout << "erro com a entrada" << std::endl;
        Main::quit = true;
    }
    player.pos() = maze.entrance();
    player.direction() = UP;

    std::stringstream ss;
    ss << player.hp() << "hp";
    player_hp.setString(ss.str());

    std::stringstream ss1;
    ss1 << player.ammo() << "ammo";
    player_ammo.setString(ss1.str());

    std::stringstream ss2;
    ss2 << "level" << level;
    player_level.setString(ss2.str());
    spriteCross.setPosition(sf::Vector2f(430+7*maze.exit().x/5, 80+7*maze.exit().y/5));
    spriteCharacter.setTexture(character_back);
}
