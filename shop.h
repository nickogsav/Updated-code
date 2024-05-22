#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include "Seperate.h"

class Shop{
private:
    std::string item_id[2]={"Sword 10G","Armor 10G"};
public: 

void enterShop(){
    sep();
    std::cout << "Welcome to the shop" << std::endl;
    std::cout << "What would you like to buy? Or enter i for info: " <<std::endl;
    std::cout << "1 = "<< item_id[0]<< std::endl<<"2 = "<< item_id[1];
    sep();
};

void Choice(char shop_choice){
    switch (shop_choice)
    {
    case '1':
        std::cout<<"Buy the "<< item_id[0]<< "? Y/N";
        break;

    case '2':
        std::cout <<"Buy the "<< item_id[1]<< "? Y/N";
        break;

    case 'i':
        break;
    
    default:
        break;
    }
    
}
   
};
#endif 
/*
Shop caller: 


char ch;
            Shop.enterShop();
            std::cin>> ch;
            Shop.Choice(ch);


*/

// How do we link the shop to the gold member in the player class 
