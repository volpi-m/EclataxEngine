/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Module interface
*/

namespace Module {

    class IModule {
    public:
        virtual bool isInitialised() = 0;
    private:
        virtual void init() = 0;
    };
}
