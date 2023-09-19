#include <iostream>
#include <bitset>
#include <typeindex>
#include <unordered_map>
#include <vector>

#define MAX_COMPONENTS 32
#define String std::string

#ifndef ECS_SCOPE
#define ECS_SCOPE
	/*
	* Essa defini��o de tipo cria um alias (apelido) para std::unique_ptr<T>. Isso permite que voc� use o nome Scope<T> no lugar de std::unique_ptr<T>, o que pode tornar o c�digo mais leg�vel e conciso. Um std::unique_ptr � usado para gerenciar a propriedade exclusiva de um objeto alocado dinamicamente.
	*/
	template<typename T>
	using scope = std::unique_ptr<T>;
	/*
	* Essa fun��o de modelo cria e retorna um objeto Scope<T> (ou seja, std::unique_ptr<T>) usando a fun��o std::make_unique. A fun��o CreateScope aceita qualquer n�mero de argumentos (Args&& ... args) que s�o perfeitamente encaminhados (forwarded) para o construtor de T. Ela � usada para criar um Scope gerenciando a propriedade exclusiva de um objeto alocado dinamicamente.
	*/
	template<typename T, typename ... Args>
	constexpr scope<T> createScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args) ...);
	}

	/*
	* Essa defini��o de tipo cria um alias (apelido) para std::shared_ptr<T>. Isso permite que voc� use o nome Ref<T> no lugar de std::shared_ptr<T>, o que pode tornar o c�digo mais leg�vel e conciso. Um std::shared_ptr � usado para gerenciar a propriedade compartilhada de um objeto alocado dinamicamente.
	*/
	template<typename T>
	using ref = std::shared_ptr<T>;

	/*
	* Essa fun��o de modelo cria e retorna um objeto Ref<T> (ou seja, std::shared_ptr<T>) usando a fun��o std::make_shared. A fun��o CreateRef aceita qualquer n�mero de argumentos (Args&& ... args) que s�o perfeitamente encaminhados (forwarded) para o construtor de T. Ela � usada para criar um Ref gerenciando a propriedade compartilhada de um objeto alocado dinamicamente.
	*/
	template<typename T, typename ... Args>
	constexpr ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
#endif // !ECS_SCOPE

