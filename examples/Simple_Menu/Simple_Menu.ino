#include <SimpleMenu.h>
int valueA, valueB, valueC, mainValue;
void function();

SimpleMenu MenuSub[3] = {
  SimpleMenu("varable A",&valueA),
  SimpleMenu("varable B",&valueB),
  SimpleMenu("varable C",&valueC)
};

SimpleMenu Menu[3] = {
  SimpleMenu("varable",&mainValue),
  SimpleMenu("functions",&function),
  SimpleMenu("sub menu",MenuSub)
};

SimpleMenu TopMenu(3,Menu);


void setup()
{
  TopMenu.begin(display,displayValue);
}

void loop() 
{
  
}

void function()
{
  
}


void display(SimpleMenu *_menu)
{

}

void displayValue(SimpleMenu *_menu)
{

}