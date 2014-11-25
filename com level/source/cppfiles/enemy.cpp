#include "../enemy.h"
#include "../maze.h"

#include "../custom/queue.h"
using custom::queue;

#include "../custom/stack.h"
using custom::stack;


// construtores

// construtor padrão
Enemy::Enemy()
: state(AWAKE), dir(UP), set_awake(false), chasing(false), hit_p(false), hit_b(false)
{
}

// construtor com um State
Enemy::Enemy(State s)
: state(s), dir(UP), set_awake(false), chasing(false), hit_p(false), hit_b(false)
{
}



// getter/setter

// retorna a direção do inimigo
Direction& Enemy::direction()
{
	return dir;
}

// retorna a direção do inimigo (const)
Direction Enemy::direction() const
{
	return dir;
}


// inicia a troca de SLEEP pra AWAKE
void Enemy::init_awake()
{
	set_awake = true;
}

// se já iniciou a troca
bool Enemy::inited_awake() const
{
	return set_awake;
}


// troca de estado pra AWAKE
void Enemy::awake()
{
	if (set_awake) state = AWAKE;
}

// se o estado é AWAKE
bool Enemy::is_awake() const
{
	return state == AWAKE;
}


// inicia a perseguição do player
void Enemy::init_chase()
{
	chasing = true;
}

// indica estado de perseguição ou de inatividade
bool Enemy::is_chasing() const
{
	return chasing;
}


// indica se o inimigo está atacando o player no loop atual
bool Enemy::hit_player() const
{
	return hit_p;
}

// indica se o inimigo foi atingido por um tiro no loop atual
bool Enemy::hit_bullet() const
{
	return hit_b;
}



// perseguição

// traça a rota de perseguição a ser tomada pelo inimigo para alcançar o jogador
bool Enemy::trace_route(Player& player, Maze& maze)
{
	stack<Position> visited;		// pilha que armazena todos os caminhos já visitados

	queue<Position> bfs;			// fila que gerencia a ordem pela qual os caminhos vão ser visitados 
	
	bfs.push(_pos);					// coloca a posição atual na fila
	
	while (!bfs.empty() && bfs.front() != player.pos()) 	// enquanto exisitirem caminhos a serem visitados e a posição atual não for a do player
	{	
		list<Position> tmp = get_adjacents(bfs.front());	// pega todos os adjacentes do caminho atual

		while (!tmp.empty())								// para cada adjacente
		{	
			Position p = tmp.pop_front();			 
			if (maze.in_bounds(p) && maze[p.x][p.y].type() != Block::WALL && !visited.includes(p))
				bfs.push(p);								// se é um caminho válido do labirinto que ainda não foi visitado, coloca na fila
		}

		visited.push(bfs.pop()); 	// coloca o caminho atual na pilha de visitados
	}
	
	if (!bfs.empty()) 				// se encontrou a posição do player
	{
		stack<Position> path;		// cria uma pilha pra armazenar a rota que o inimigo tem que percorrer
		path.push(bfs.pop());		// coloca a posição do player na pilha
		while (!visited.empty())	// para cada caminho visitado
		{
			Position x = visited.pop();	
			if (x.adjacent_to(path.top()))  // se for adjacente ao último caminho colocado na pilha da rota
			{
				path.push(x);				// coloca esse caminho na pilha da rota
			}
		}									

		path.pop();							// remove a posição atual do inimigo da rota

		while (!path.empty())				// transfere os caminhos que estão na pilha para a rota do inimigo
		{
			route.push(path.pop());			
		}

		return true;				// retorna verdadeiro, pois encontrou uma rota até o player
	}
	else return false;				// se não, retorna falso
}


// a função que faz com que o inimigo persiga o jogador, leva em consideração a trajetória da bala (se houver)
bool Enemy::chase(Player& player, Maze& maze, queue<Position>& bullet_course)
{
	if (chasing)				// se estiver perseguindo
	{
		if (!route.empty())		// se já traçou uma rota
		{
			Position old_pos = _pos;	
			_pos = route.pop();			// move-se para o próximo caminho da rota
            
			if (_pos == get_adjacent(old_pos, LEFT)) dir = LEFT;		// troca a direção do inimigo de acordo com 
			else if (_pos == get_adjacent(old_pos, RIGHT)) dir = RIGHT; // a direção de deslocamento
			else if (_pos == get_adjacent(old_pos, UP)) dir = UP;
			else if (_pos == get_adjacent(old_pos, DOWN)) dir = DOWN;

			if (collided_with(player))	// se encontrou o jogador
			{
				route.clear();			// limpa a rota
				_pos = old_pos;			// retorna à posição anterior, para não sobrepôr o jogador
                
				player.receive_dmg(1);	// dá dano no jogador
                
				chasing = false;		// pára de perseguir
				hit_p = true;			// troca o valor da variável, acertou o player
			}
            else if (!bullet_course.empty() && collided_with(bullet_course.front()))  // se o jogador atirou e o inimigo colidiu com a bala
            {
                route.clear();	 // limpa a rota
                _pos = old_pos;	 // retorna à posição anterior, 
                
                chasing = false; // pára de perseguir
                hit_b = true;	 // troca o valor da variável, colidiu com a bala
            }
		}
		else 	// se não traçou uma rota
		{
			bool found_route = trace_route(player, maze);  // traça a rota
			return found_route; 	// retorna true se encontrou uma rota, false se não
		}
	}
    
	return chasing;     // retorna true se está perseguindo, false caso contrário
}