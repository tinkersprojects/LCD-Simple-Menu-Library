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



#### int getValue();


### Menu Variables
#### String name;




## Examples
### Examples 1:
```c++

```

### Examples 2:
```c++

```

### Examples 3:
```c++

```




## Current Bugs
- Back function is not working, its going back too far.


## To Be Developed 
- adding lists for files from SD card or varables.
