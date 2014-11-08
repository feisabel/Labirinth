/*
Geral:
- nomes de classes, funções/métodos e variáveis em inglês;
- identação:
	- 1 tab por bloco
	- chave de abertura uma linha abaixo do início do bloco
	- comandos iniciam na linha abaixo da chave de abertura e terminam uma linha acima da chave de encerramento


Comentários / documentação:
- estilo doxygen, como requerido pelo professor.
  mais informações aqui: http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html


Funções:
- declaração de funções separadas de suas implementações
- ordem de declaração e implementação: por funcionalidade (especifique)


Classes/Structs:
- declaração de classes e seus membros separados das implementações
- inicie o arquivo de declaração da classe com uma breve descrição do que ela é/representa

- ordem de declaração e implementação dos membros:
 - por restrição de acesso:
	- public
	- protected
	- private
 - por funcionalidade:
 	- tipos
  	- construtores
  	- destrutor
  	- getter/setter
  	- outros: arbitrário (especifique critério de separação) 
  	- variáveis/constantes


exemplo de classe:
*/

class Type
{
public: // interface
	typedef int type1;
	enum enum1 {VALOR_1, VALOR_2};

	struct my_struct1 {
		my_type1 val;     // valor
	};


	// construtores
	Type();           // construtor padrão                       
	Type(type1);      // construtor (um parâmetro)
	Type(int, int);   // construtor (dois parâmetros)

	Type(Type&);      // construtor de cópia

	// destrutor
	~Type();

	// getter/setter
	type1& integer();              // getter/setter
	const type1& integer() const;  // const getter

	// alteração
	type1 operator+(int a);		   // especifique o que cada método faz, se não for óbvio:
	type1 my_func(int x, int y);   // multiplica x por y, armazena e retorna resultado


	// variáveis
	type1 value;
	enum1 e;

	// constantes
	const my_struct1 max_value;


protected: // interno (classes filhas)
	typedef double _type2;

	// construtor
	Type(_type2);

	// leitura
	void read();                   // lê os dados da entrada padrão
	void read_file(std::string);   // lê os dados de um arquivo


	// constantes
	static const int number_of_instances; 


private: // interno
	struct _my_struct2 {
		_type2 val;     // valor
	};

	// transformação
	my_struct1 _make_from2(_my_struct2);  // cria um my_struct1 a partir de um my_struct2
	_my_struct2 _make_from1(my_struct1);  // cria um my_struct2 a partir de um my_struct1

};