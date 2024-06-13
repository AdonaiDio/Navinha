#pragma once


namespace adonai
{
    class Player; //definindo o player como promessa de ter o player no .cpp
    
    class Controller
    {
        private:
        public:
            Controller();
            void InputAction_Move(adonai::Player& player);
            void InputAction_Shoot(adonai::Player& player);
    };
}
