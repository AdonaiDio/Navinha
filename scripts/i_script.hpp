#pragma once

#include "bn_log.h"

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
        virtual void start(Object*) = 0;
        // update() deve ser chamado todo frame dentro de um While(true){}.
        virtual void update(Object*) = 0;
        //codigo para juntar o script a um objeto existente e executar o start()
        // virtual void script_binder(Object& o) = 0;
    private:

};

}
/*
---------------------------
Se você veio aqui procurando respostas de porquê que as coisas do Script parecem 
tão complicadas e confusas, espero poder esclarecer algo. Tentei usar uma interface 
para criar a regra de todo script possuir start e update. 

Além disso a existencia de uma interface do script permite que eu possa fazer uma lista/vector 
contendo todos os tipo de scripts, se não fosse isso guarar as listas de scripts dentro do ator 
seria uma dor de cabeça maior.

Como eu não sei qual vai ser o ator que vai ser usado pelo script, 
então a interface precisa de um Template de classe, ex: template <class Object>
Por conseguencia eu tenho que passar dentro da classe inteface basica o valor da classe que 
ele vai estar usando ex: public I_Script<Enemy>

O codigo fica bem feioso quando vamos chamar um codigo disso e tal.
Por isso a necessidade de uma função que adicione o script ao ator quando chamado pelo ator.
-----------------------------
*/