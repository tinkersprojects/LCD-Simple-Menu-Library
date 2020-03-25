#include <SimpleMenu.h>
int valueA, valueB, valueC, mainValue;
void function();

SimpleMenu MenuSub[3] = {
  SimpleMenu("varable A",&valueA),
  SimpleMenu("varable B",&valueB),
  SimpleMenu("varable C",&valueC)
};

SimpleMenu Menu[4] = {
  SimpleMenu("varable",&mainValue),
  SimpleMenu("functions",function),
  SimpleMenu("sub menu A",3,MenuSub),
  SimpleMenu("sub menu B",3,MenuSub)
};

SimpleMenu TopMenu(4,Menu);

void display(SimpleMenu *_menu)
{
  Serial.print("name: ");
  Serial.println(_menu->name);

  SimpleMenu *next = TopMenu.next();
  Serial.print("next name: ");
  Serial.println(next->name);
}

void displayValue(SimpleMenu *_menu)
{
  Serial.println("123");
}


void setup()
{
  Serial.begin(9600);
  Serial.println("start");
  delay(100);
  TopMenu.begin(display,displayValue);
  Serial.println();
  TopMenu.select();
  Serial.println();
  TopMenu.select();
  Serial.println();
  TopMenu.up();
  Serial.println();
  TopMenu.up();
  Serial.println();
  TopMenu.up();
  Serial.println();
  TopMenu.select();
  Serial.println();
  
  Serial.println("finish");
}

void loop() 
{
  
}

void function()
{
  
  Serial.println("function");
}

