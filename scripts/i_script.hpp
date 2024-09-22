#pragma once
namespace adonai
{

// ==> Interface Script <==
// Não é um objeto. Usamos para acessar funções padrões:
// start() e update()
//
// O propósito do script é condicionar e executar funções que existem no objeto que está sendo scriptado.
// Se preocupando apenas com o comportamento que aquele objeto deve possuir.
template <class Object>
class I_Script{
    public:
        // start() deve ser chamado no corpo do código fora do While(true){},
        // aonde será executado uma unica vez.
        virtual void start(Object&) = 0;
        // update() deve ser chamado todo frame dentro de um While(true){}.
        virtual void update(Object&) = 0;
    private:

};
    
}