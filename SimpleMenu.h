
#ifndef SimpleMenu_h
#define SimpleMenu_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

class SimpleMenu
{
    public:
        SimpleMenu(int _numberMenuItems, SimpleMenu *_submenus); //defult
        SimpleMenu(String _name,int _numberMenuItems, SimpleMenu *_submenus); //sub menu
        SimpleMenu(String _name,int *_value); //Value menu
        SimpleMenu(String _name,int *_value, int _min, int _max); //Value menu with min and max
        SimpleMenu(String _name, void (*_CallBack)()); //function menu

        void begin(void (*_displayCallBack)(SimpleMenu *_menu));
        void begin(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu));

        void select();
        void back();
        void returned();
        void returnedSecond();
        void up();
        void down();
        void index(int _index);

        SimpleMenu *next();
        SimpleMenu *next(int index);
        int getValue();
        void print();
            
        String name;

    private:
        void begin(SimpleMenu *_Top,void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu));
        

        int menuLocation = 0;
        bool selectMenu = false;
        SimpleMenu *Top_menu = NULL;

        int numberMenuItems;
        SimpleMenu *submenus = NULL;
        int *value = NULL;
        void (*CallBack) () = NULL;
        void (*displayCallBack)(SimpleMenu *_menu) = NULL;
        void (*valueCallBack)(SimpleMenu *_menu) = NULL;

        int min;
        int max;
        bool minMaxSet = false;
};

#endif 
