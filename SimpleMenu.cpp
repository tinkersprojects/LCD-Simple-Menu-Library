/**********************************************************************************************
 * Arduino LED RGB Library - version 2.0
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "SimpleMenu.h"

/******************* SETUP *******************/

SimpleMenu::SimpleMenu(int _numberMenuItems, SimpleMenu *_submenus) //defult
{
 numberMenuItems = _numberMenuItems;
 submenus = _submenus;
}

SimpleMenu::SimpleMenu(void (*_CallBack)()) //defult
{
  CallBack = _CallBack;
}


SimpleMenu::SimpleMenu( bool (*_ListCallBack)(int index), SimpleMenu *_subListmenus) //List menu with function
{
  subListmenus = _subListmenus;
  ListCallBack = _ListCallBack;
}

SimpleMenu::SimpleMenu( bool (*_ListCallBack)(int index), void (*_CallBack)()) //List menu with function
{
  CallBack = _CallBack;
  ListCallBack = _ListCallBack;
}

SimpleMenu::SimpleMenu(String _name,int _numberMenuItems, SimpleMenu *_submenus) //sub menu
{
 name = _name;
 numberMenuItems = _numberMenuItems;
 submenus = _submenus;
}

SimpleMenu::SimpleMenu(String _name,int *_value) //Value menu
{
 name = _name;
 value = _value;
}

SimpleMenu::SimpleMenu(String _name,int *_value, int _min, int _max) //Value menu
{
  name = _name;
  value = _value;
  min = _min;
  max = _max;
  minMaxSet = true;
}

SimpleMenu::SimpleMenu(String _name, void (*_CallBack)()) //function menu
{
  name = _name;
  CallBack = _CallBack;
}

SimpleMenu::SimpleMenu(String _name, bool (*_ListCallBack)(int index), SimpleMenu *_subListmenus) //List menu with function
{
  name = _name;
  subListmenus = _subListmenus;
  ListCallBack = _ListCallBack;
}

SimpleMenu::SimpleMenu(String _name, bool (*_ListCallBack)(int index), void (*_CallBack)()) //List menu with function
{
  name = _name;
  CallBack = _CallBack;
  ListCallBack = _ListCallBack;
}

void SimpleMenu::begin()
{
  selectMenu = false;
  menuLocation = 0;
  this->print();
}

void SimpleMenu::begin(void (*_displayCallBack)(SimpleMenu *_menu))
{
  selectMenu = false;
  menuLocation = 0;
  if(displayCallBack  == NULL)
    displayCallBack = _displayCallBack;
  this->print();
}

void SimpleMenu::begin(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu))
{
  selectMenu = false;
  menuLocation = 0;
  if(displayCallBack  == NULL)
    displayCallBack = _displayCallBack;
  if(valueCallBack  == NULL)
    valueCallBack = _valueCallBack;
  this->print();
}

void SimpleMenu::begin(SimpleMenu *_Top,void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu))
{
  selectMenu = false;
  menuLocation = 0;
  Top_menu = _Top;
  
  if(displayCallBack  == NULL)
    displayCallBack = _displayCallBack;
  if(valueCallBack  == NULL)
    valueCallBack = _valueCallBack;

  if(CallBack != NULL && ListCallBack == NULL)
  {
    CallBack();
    Top_menu->returned();
  }

  this->print();
}

void SimpleMenu::setFunctions(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu))
{
  displayCallBack = _displayCallBack;
  valueCallBack = _valueCallBack;
}

void SimpleMenu::home()
{
  if(subListmenus != NULL)
  {
    subListmenus->back();
  }
  if(submenus != NULL)
  {
    submenus[menuLocation].back();
  }
  if(selectMenu)
  {
    selectMenu=false;
  }
  this->print();
}

void SimpleMenu::select()
{
  if(menuLocation == -1)
  {
    Top_menu->returned();
  }
  else if(CallBack != NULL && ListCallBack != NULL)
  {
    CallBack();
  }
  else if(selectMenu && submenus != NULL)
  {
    submenus[menuLocation].select();
  }
  else if(submenus != NULL)
  {
    selectMenu = true;
    submenus[menuLocation].begin(this,displayCallBack,valueCallBack);
  }
  else if(selectMenu && subListmenus != NULL)
  {
    subListmenus->select();
  }
  else if(subListmenus != NULL)
  {
    selectMenu = true;
    subListmenus->begin(this,displayCallBack,valueCallBack);
  }
  else if(value != NULL && Top_menu != NULL)
  {
    Top_menu->returned();
  }
  this->print();
}

void SimpleMenu::back()
{
  if(selectMenu && subListmenus != NULL && subListmenus->selectMenu)
  {
    subListmenus->back();
  }
  else if(selectMenu && submenus != NULL && submenus[menuLocation].selectMenu)
  {
    submenus[menuLocation].back();
  }
  else if(submenus != NULL)
  {
    selectMenu = false;
  }
  else if(Top_menu != NULL)
  {
    Top_menu->returned();
  }
  this->print();
}

void SimpleMenu::returned()
{
  selectMenu = false;
  this->print();
}

void SimpleMenu::up()
{
  if(selectMenu && subListmenus != NULL)
  {
    subListmenus->up();
  }
  else if(selectMenu)
  {
    submenus[menuLocation].up();
  }
  else if(value != NULL)
  {
    *value = *value + 1;
  }
  else
  {
    menuLocation--;
  }
  this->print();
}

void SimpleMenu::down()
{
  if(selectMenu && subListmenus != NULL)
  {
    subListmenus->down();
  }
  else if(selectMenu)
  {
    submenus[menuLocation].down();
  }
  else if(value != NULL)
  {
    *value = *value - 1;
  }
  else
  {
    menuLocation++;
  }
  this->print();
}

void SimpleMenu::index(int _index)
{
  
  if(selectMenu && subListmenus != NULL)
  {
    subListmenus->index(_index);
  }
  else if(selectMenu)
  {
    submenus[menuLocation].index(_index);
  }
  else if(value != NULL)
  {
    *value = _index;
  }
  else
  {
    menuLocation = _index;
  }
  this->print();
}

SimpleMenu *SimpleMenu::next()
{
  return this->next(1);
}

SimpleMenu *SimpleMenu::next(int index)
{
  if(selectMenu && submenus != NULL)
  {
    return  submenus[menuLocation].next(index);
  }
  else if(menuLocation+index>=0 && menuLocation+index < numberMenuItems)
  {
    return  &submenus[menuLocation+index];
  }
  else if(selectMenu && subListmenus != NULL)
  {
    return  subListmenus->next(index);
  }
  return NULL;
}

void SimpleMenu::print()
{
  if(minMaxSet && *value<min)
  {
    *value = min;
  }

  if(minMaxSet && *value>max)
  {
    *value = max;
  }

  if(/*ListCallBack == NULL &&*/ menuLocation<0)
  {
    menuLocation = 0;
  }
  

  if(submenus != NULL && menuLocation >= numberMenuItems)
  {
    menuLocation = numberMenuItems-1;
  }

  if(selectMenu && submenus != NULL )
  {
    submenus[menuLocation].print();
  }
  else if(selectMenu && subListmenus != NULL && ListCallBack != NULL )
  {
    subListmenus->print();
  }
  else if(value != NULL)
  {
    valueCallBack(this);
  }
  else if(ListCallBack != NULL)
  {
    bool LocationExists = ListCallBack(menuLocation);
    while(LocationExists == false && menuLocation > -1 )
    {
      menuLocation--;
      LocationExists = ListCallBack(menuLocation);
    }
    
    if(menuLocation < -1)
    {
      menuLocation = -1;
      this->back();
    }
  }
  else if(submenus != NULL)
  {
    displayCallBack(&submenus[menuLocation]);
  }
  
}

bool SimpleMenu::hasValue()
{
  return value != NULL
}

int SimpleMenu::getValue()
{
  return *value;
}


int SimpleMenu::getIndex()
{
  return menuLocation;
}