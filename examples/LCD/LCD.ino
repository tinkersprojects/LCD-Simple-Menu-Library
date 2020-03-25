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
