#pragma once


namespace adonai
{
    class Player; //definindo o player como promessa de ter o player no .cpp
    
    class Controller
    {
        private:
            adonai::Player& _player;
        public:
            Controller(adonai::Player &player);
            void InputAction_Move();
            void InputAction_Shoot();
            void start_shoot();
            void update();
    };
}
