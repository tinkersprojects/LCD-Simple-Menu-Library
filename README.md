# LCD-Simple-Menu
this library is still under testing

[https://tinkersprojects.com/](https://tinkersprojects.com/)

This is a simple LCD Menu Library for Arduino to make menus to control robots and machines.

Menu Systems on an LCD has always been a thing that has gotten in the way of developing software for robots and machines. It always takes too long to implement and debug. sometimes most of the bugs are from the menu. This library is here to try and simplify the LCD menu but still giving control to the software.


## How It Works




## Functions and Varables
### Menu/Sub-Menu Setup
Different menus, sub-menus or menu items have different setup requiaments. the different types are listed below.

#### SimpleMenu(int _numberMenuItems, SimpleMenu *_submenus);
**used as Top Menu**



#### SimpleMenu(String _name,int _numberMenuItems, SimpleMenu *_submenus); 
**used as Sub-Menu**



#### SimpleMenu(String _name,int *_value);
**used as Value Menu Item**



#### SimpleMenu(String _name,int *_value, int _min, int _max);
**used as Value Menu Item with min and max**



#### SimpleMenu(String _name, void (*_CallBack)());
**used as function Menu Item**




### Menu Setup
#### void begin(void (*_displayCallBack)(SimpleMenu *_menu));



#### void begin(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu));




### Menu Controls
#### void select();



#### void back();



#### void up();



#### void down();



#### void index(int _index);




### Menu Functions
#### SimpleMenu *next();



#### SimpleMenu *next(int index);



#### void print();



#### int hasValue();

#### int getValue();


### Menu Variables
#### String name;




## Examples
### Examples 1:
```c++
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
```

### Examples 2:
```c++
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


```

### Examples 3:
```c++
#include <SimpleMenu.h>
#include <LiquidCrystal.h>

#define LCD_RS 2
#define LCD_EN 4
#define LCD_D4 5
#define LCD_D5 6
#define LCD_D6 7
#define LCD_D7 8

int valueA, valueB, valueC, mainValue=5;
void function();

SimpleMenu MenuSub[3] = {
  SimpleMenu("varable A",&valueA),
  SimpleMenu("varable B",&valueB),
  SimpleMenu("varable C",&valueC)
};

SimpleMenu Menu[4] = {
  SimpleMenu("varable",&mainValue,3,10),
  SimpleMenu("functions",function),
  SimpleMenu("sub menu A",3,MenuSub),
  SimpleMenu("sub menu B",3,MenuSub)
};

SimpleMenu TopMenu(4,Menu);
LiquidCrystal lcd = LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void display(SimpleMenu *_menu)
{
  lcd.clear();
  lcd.print(">");
  lcd.print(_menu->name);

  SimpleMenu *next = TopMenu.next();
  if(next != NULL)
  {
    lcd.setCursor(1,1);
    lcd.print(next->name);
  }
}

void displayValue(SimpleMenu *_menu)
{
  lcd.clear();
  lcd.print(_menu->name);
  lcd.setCursor(0,1);
  lcd.print(_menu->getValue());
}


void setup()
{
  Serial.begin(9600);
  Serial.println("start");
  delay(100);
  
  lcd.begin(16, 2);
  TopMenu.begin(display,displayValue);
}

void loop() 
{
  while (Serial.available()) 
  {
    switch( (char)Serial.read())
    {
      case 'w':
        TopMenu.up();
        break;
      case 's':
        TopMenu.down();
        break;
      case 'a':
        TopMenu.back();
        break;
      case 'd':
        TopMenu.select();
        break;
    }
  }
}

void function()
{
  lcd.clear();
  lcd.print("function");
  Serial.print("function");
  delay(3000);
}

```




## Current Bugs
- Back function is not working, its going back too far.


## To Be Developed 
- adding lists for files from SD card or varables.
