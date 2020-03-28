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

void SimpleMenu::begin(void (*_displayCallBack)(SimpleMenu *_menu))
{
  selectMenu = false;
  menuLocation = 0;
  displayCallBack = _displayCallBack;
  this->print();
}

void SimpleMenu::begin(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu))
{
  selectMenu = false;
  menuLocation = 0;
  displayCallBack = _displayCallBack;
  valueCallBack = _valueCallBack;
  this->print();
}

void SimpleMenu::begin(SimpleMenu *_Top,void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu))
{
  selectMenu = false;
  menuLocation = 0;
  Top_menu = _Top;
  displayCallBack = _displayCallBack;
  valueCallBack = _valueCallBack;

  if(CallBack != NULL)
  {
    CallBack();
    Top_menu->returnedSecond();
  }

  this->print();
}

void SimpleMenu::select()
{
  if(selectMenu && submenus != NULL)
  {
    submenus[menuLocation].select();
  }
  else if(submenus != NULL)
  {
    selectMenu = true;
    submenus[menuLocation].begin(this,displayCallBack,valueCallBack);
  }
  else if(value != NULL && Top_menu != NULL)
  {
    Top_menu->returnedSecond();
  }
  this->print();
}

void SimpleMenu::back()
{
  if(selectMenu && submenus != NULL)
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
  if(Top_menu != NULL)
  {
    Top_menu->returnedSecond();
  }
  selectMenu = false;
  this->print();
}

void SimpleMenu::returnedSecond()
{
  selectMenu = false;
  this->print();
}

void SimpleMenu::up()
{
  if(selectMenu)
  {
    submenus[menuLocation].up();
  }
  else if(value != NULL)
  {
    *value = *value + 1;
  }
  else
  {
    menuLocation++;
  }
  this->print();
}

void SimpleMenu::down()
{
  if(selectMenu)
  {
    submenus[menuLocation].down();
  }
  else if(value != NULL)
  {
    *value = *value - 1;
  }
  else
  {
    menuLocation--;
  }
  this->print();
}

void SimpleMenu::index(int _index)
{
  if(selectMenu)
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
    submenus[menuLocation].next(index);
  }
  else if(menuLocation+index<0 || menuLocation+index >= numberMenuItems)
  {
    return NULL;
  }
  else if(submenus != NULL)
  {
    return  &submenus[menuLocation+index];
  }
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

  if(menuLocation<0)
  {
    menuLocation = 0;
  }

  if(menuLocation >= numberMenuItems)
  {
    menuLocation = numberMenuItems-1;
  }

  if(selectMenu && submenus != NULL)
  {
    submenus[menuLocation].print();
  }
  else if(value != NULL)
  {
    valueCallBack(this);
  }
  else if(submenus != NULL)
  {
    displayCallBack(&submenus[menuLocation]);
  }
}


int SimpleMenu::getValue()
{
  return *value;
}