#include "shop.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>


int player_hp = 100;  //Player Hit Points
int enemy_hp = 100;  //Enemy Hiy points
int xp_cap = 100; //The Default amount of xp needed to level up
    int* player_hp_ptr = &player_hp;   //Pointers for the players hp and the enemies hp
    int* enemy_hp_ptr = &enemy_hp;   //Needed for later funtions
    int* drained_hp; //Drained hp used to add the amount the player heals durring the King slime boss fight
int enemy_type =0; //Used when deciding enemy type (slime, fox, king slime) 
int turn_timer=0; //Counts down the amount of turns the enemy is burned
int burn_timer =0;  // Counts down the smount of turns the player is bleeding

Shop s1; //Starts the shop 



void attack(int*&,char,int);
void battle(std::string);
void enemy(int*&,int*&,int);
void lvlup();
void moveinfo();

class Player{
    private: 
    int gold;
    int lvl;
    int xp;
    int max_hp; // Max hp of the player and caps over healing
    std::string name;
public:
    Player(){
        lvl = 1;
        xp = 0;
        name = "N/A";
        max_hp = 100;
        gold = 0;
    };

    int Getlvl(){return lvl;};
    int Getgold(){return gold;}
    int Getexp(){return xp;};
    int GetHpcap(){return max_hp;};
    std::string Getname(){return name;};
    void setGold(int gold){this->gold += gold;}
    void setLvl(int lvl){this->lvl +=lvl;};
    void setHpcap(int max_hp){this->max_hp +=max_hp;}
    void setExp(int xp){this-> xp +=xp;};
    void setName(std::string name){this-> name = name;};
    void Displayer(){
        char menu_stopper; // Is only used to halt the program so the player can read and menu_stopper's of type char are used for readablity
     sep();
        std::cout << this->name <<"'s stats: "<< std::endl;
        std::cout << "Level: " << this->lvl << std:: endl;
        std::cout << "HP: " << player_hp << "/"<< max_hp <<std:: endl;
        std::cout << "EXP: " << xp << "/"<< xp_cap <<std::endl;
        std::cout << "Gold: "<< gold;
        sep();
        std::cout << "Press any key and enter to continue: ";
        std::cin >> menu_stopper; // Paues the menu so the player can read it
    }
};

    
    Player* player_ptr; //A pointer used point at the methods within the Player class

int main(){
    
    int exit_menu =1; //Used to exit the menu loop, when exit_menu is equal to 2 the program ends
    char user_choice;
    char menu_stopper;
    
   std::string name;
   sep();
        std:: cout<<"Welcome to Brandon's WIP RPG"<<std::endl;
        std::cout<<"Name pending... ";
   sep();
   std::cout << "Please enter your Name: ";
         getline(std::cin,name);

    Player p1;
    player_ptr = &p1;
    p1.setName(name);
    
     sep(); 
  std::cout << "Your stats: "<<std::endl;
    std::cout << "Your player name is: "<< p1.Getname() <<std::endl;
    std::cout <<"Exp: " << p1.Getexp() <<"/" << xp_cap << std::endl;
   std::cout <<"Lvel: "<<  p1.Getlvl()<< std::endl;
    

    std::cout <<"Press any key and enter to continue: ";
    sep();
   std::cin >> menu_stopper;
    
    while(exit_menu == 1){ //This is the menu loop, if the user enters 5(Exit) as their user_choice the program exits the loop and the program ends
        sep();
    std::cout << "What would you like to do?"<<std::endl;
        std::cout << "1 = Battle" <<std::endl;
        std::cout << "2 = Rest(used to heal)" <<std::endl;
        std::cout << "3 = Show stats" <<std::endl;
        std::cout << "4 = Shop (Doesn'turn_timer work yet)" <<std::endl;
        std::cout << "5 = Exit";
    sep();

    std::cin >> user_choice;
   
        switch (user_choice)
        {
        case '1':
            *enemy_hp_ptr = 100;// Sets the emeny's hp to 100 if it wasn'turn_timer set alread
            battle(name);
           
            break;
        case '2':
                sep();
                std::cout << "You rested and full healed!";
                *player_hp_ptr =player_ptr->GetHpcap(); //Heals the player by setting the hp pointer equal to the players max hp
            break;

        case '3':
            
            player_ptr->Displayer();
            break;
        case '4':
             
            char shop_choice;
            s1.enterShop(); //Calls the shop. See shop.h for more detials
            std::cin>> shop_choice;
            s1.Choice(shop_choice);
            break;
        case '5':
                exit_menu++;
            break;

        default:
            std:: cout << "error"<<std::endl;
            break;
        }
    }
    std::cout << "Ending the program!" << std::endl;

return 0;
}





void battle(std::string name){
    
    char player_action; //Reads the players action
    int c;
    if(*player_hp_ptr!= player_ptr->GetHpcap()){ //Check if the player is at full hp
        std::cout<< "You aren'turn_timer at full hp!"<<std::endl;
    }
    else{
        sep();
        std::cout << "What would you like to fight?"<< std::endl;
        std::cout << "1 = Slime"<<std::endl;
        std::cout << "2 = Fox"<<std::endl;
        std::cout << "3 = King Slime (Boss)";
        sep();
            std::cin >> enemy_type; //Takes in the user_choice for enemy type
        
    switch(enemy_type)
    {
        case 1:
    sep();
    std::cout << "A Slime appears: " << std::endl;

    while(*player_hp_ptr > 0 && *enemy_hp_ptr > 0){
       
        std::cout << "Slime: "<< enemy_hp << "/100"; 
        if(turn_timer > 0){
            std::cout << "-Burned"<< std::endl;
        }
        else    
           std::cout << std::endl;
        std::cout << name << ": " << player_hp << "/"<<player_ptr->GetHpcap() << std::endl;
            std::cout << "Enter i to show move details."<< std::endl;
        std::cout << "What will you do?" << std::endl << "1 = Attack" << std::endl << "2 = Heavy Attack (low acc)";
        
        if(player_ptr->Getlvl() >= 2){
            std::cout << std::endl << "3 = Execute";
        }
        if(player_ptr->Getlvl() >= 3){
            std::cout << std::endl << "4 = Fireball";
        }
        sep();
        std::cin >> player_action;

            switch (player_action)
            {
            case '1': 
                attack(enemy_hp_ptr, player_action,enemy_type);
                
                break;
            case '2': 
                attack(enemy_hp_ptr, player_action,enemy_type);
                break;
            case '3':
                if(player_ptr->Getlvl() >= 2){
                attack(enemy_hp_ptr, player_action,enemy_type);
                }
                break;
            case '4':
                if(player_ptr->Getlvl() >= 3){
                attack(enemy_hp_ptr, player_action,enemy_type);
                }
                break;
            case 'i':
                moveinfo();
                break;
                
            default:
                break;
            }

    }
    turn_timer =0;
      if(*player_hp_ptr <= 0){
        sep();
       std::cout << "You died to the slime!";
       *player_hp_ptr =0;

    }
    else{
        sep();
        std::cout << "You won the battle! You got "<< 75 << " xp!"<< std::endl;
        std::cout << "And you got 10 gold";
        player_ptr->setGold(10);
        player_ptr->setExp(75);
        

    }

    if(player_ptr->Getexp() >= xp_cap){
        lvlup();
        }
        break;

          case 2:
    sep();
    std::cout << "A Fox appears: " << std::endl;

    while(*player_hp_ptr > 0 && *enemy_hp_ptr > 0){
       
        std::cout << "Fox: "<< enemy_hp << "/100"; 
        if(turn_timer > 0){
            std::cout << "-Burned"<< std::endl;
        }
        else    
           std::cout << std::endl;
        std::cout << name << ": " << player_hp << "/" <<player_ptr->GetHpcap()<< std::endl;
            std::cout << "Enter i to show move details."<< std::endl;
        std::cout << "What will you do?" << std::endl << "1 = Attack" << std::endl << "2 = Heavy Attack (low acc)";
        
        if(player_ptr->Getlvl() >= 2){
            std::cout << std::endl << "3 = Execute";
        }
        if(player_ptr->Getlvl() >= 3){
            std::cout << std::endl << "4 = Fireball";
        }
        sep();
        std::cin >> player_action;

            switch (player_action)
            {
            case '1': 
                attack(enemy_hp_ptr, player_action,enemy_type);
                
                break;
            case '2': 
                attack(enemy_hp_ptr, player_action,enemy_type);
                break;
            case '3':
                if(player_ptr->Getlvl() >= 2){
                attack(enemy_hp_ptr, player_action,enemy_type);
                }
                break;
            case '4':
                if(player_ptr->Getlvl() >= 3){
                attack(enemy_hp_ptr, player_action,enemy_type);
                }
                break;
            case 'i':
                moveinfo();
                break;
                
            default:
                break;
            }

    }
    turn_timer =0;
    burn_timer =0;
      if(*player_hp_ptr <= 0){
       std::cout << "You died to the Fox!";
       *player_hp_ptr =0;

    }
    else{
        std::cout << "You won the battle! You got "<< 75 << " xp!";
        std::cout << "And you got 10 gold";
        player_ptr->setGold(10);
        player_ptr->setExp(75);

    }

    if(player_ptr->Getexp() >= xp_cap){
        lvlup();
        }
        break;

    case 3:

          sep();
    std::cout << "The King Slime appears: " << std::endl;
        *enemy_hp_ptr = 300;
    while(*player_hp_ptr > 0 && *enemy_hp_ptr > 0){
       
        std::cout << "King Slime: "<< enemy_hp << "/300"; 
        if(turn_timer > 0){
            std::cout << "-Burned"<< std::endl;
        }
        else    
           std::cout << std::endl;
        std::cout << name << ": " << player_hp << "/" <<player_ptr->GetHpcap()<< std::endl;
            std::cout << "Enter i to show move details."<< std::endl;
        std::cout << "What will you do?" << std::endl << "1 = Attack" << std::endl << "2 = Heavy Attack (low acc)";
        
        if(player_ptr->Getlvl() >= 2){
            std::cout << std::endl << "3 = Execute";
        }
        if(player_ptr->Getlvl() >= 3){
            std::cout << std::endl << "4 = Fireball";
        }
        sep();
        std::cin >> player_action;

            switch (player_action)
            {
            case '1': 
                attack(enemy_hp_ptr, player_action,enemy_type);
                
                break;
            case '2': 
                attack(enemy_hp_ptr, player_action,enemy_type);
                break;
            case '3':
                if(player_ptr->Getlvl() >= 2){
                attack(enemy_hp_ptr, player_action,enemy_type);
                }
                break;
            case '4':
                if(player_ptr->Getlvl() >= 3){
                attack(enemy_hp_ptr, player_action,enemy_type);
                }
                break;
            case 'i':
                moveinfo();
                break;
                
            default:
                break;
            }

    }
    turn_timer =0;
    burn_timer =0;
      if(*player_hp_ptr <= 0){
        sep();
       std::cout << "You died to the King Slime!";
       *player_hp_ptr =0;

    }
    else{
        sep();
        std::cout << "You won the battle! You got "<< 200 << " xp!";
        std::cout << "And you got"<< 30 << "gold";
        player_ptr->setGold(30);
        player_ptr->setExp(200);

    }

    if(player_ptr->Getexp() >= xp_cap){
        lvlup();
        }

        break;

    default:
        std::cout << "Invalid" << std::endl;
        break;
        }
    }
}

void attack(int*& hp, char player_action,int enemy_name){
    int accuracy;
    int damage;
    int burn;
    std::string type;
    if(enemy_name == 1){
        type = " slime ";
    }
        if(enemy_name== 2){
            type =" fox ";
        }
            if(enemy_name ==3){
                type = " King Slime ";
            }
        if(player_action == '1'){
        srand(time(NULL));

    accuracy = rand() % 9 + 1;
    damage = rand() % 19 + 1;
        drained_hp = &damage;
        if(accuracy > 3){
        std::cout << "You hit the" << type << "for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
        enemy(player_hp_ptr,hp,enemy_type);
        }
        else {
            std::cout << "You missed!";
            sep();
            enemy(player_hp_ptr, hp,enemy_type);
        }
     }
     if(player_action == '2'){
      srand(time(NULL));

    accuracy = rand() % 9 + 1;
    damage = rand() % 40 + 10;
        drained_hp = &damage;
        if(accuracy > 6){
        std::cout << "You hit the"<< type << "for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
        enemy(player_hp_ptr,hp,enemy_type);
        }
        else {
            std::cout << "You missed!";
            sep();
            enemy(player_hp_ptr,hp,enemy_type);
        }

     }
     if(player_action == '3'){
        srand(time(NULL));

    accuracy = rand() % 99 +1;
    damage = 9999;
        drained_hp = &damage;
        if(accuracy<=5){
        std::cout << "You hit the"<< type <<"for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
        enemy(player_hp_ptr,hp,enemy_type);
        }
        else {
            std::cout << "You missed!";
            sep();
            enemy(player_hp_ptr, hp,enemy_type);
        }
     }
     if(player_action == '4'){
         srand(time(NULL));

    accuracy = rand() % 9 + 1;
    damage = rand() % 40 + 10;
    burn = rand() % 3 + 1;
    drained_hp = &damage;
        if(accuracy > 4){
        std::cout << "You hit the"<< type << "for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
         if(burn == 4){
            std::cout <<"You burned the" << type << std::endl;
            
            turn_timer=3;
         }
        
        enemy(player_hp_ptr,hp,enemy_type);
        }
        else {
            std::cout << "You missed!";
            sep();
            enemy(player_hp_ptr,hp,enemy_type);
        }
     }
     
}
void enemy(int*& hp,int*& enemy_hp,int enemy_type){
    int accuracy;
    int damage;
    int c;

        if(enemy_type == 1){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1,10);


if(*enemy_hp > 0){
    accuracy = dist(gen);
    damage = dist(gen)% 20 +6;
    if(turn_timer > 0){
        int burn_damage;
        burn_damage = rand() % 15 +3;
        std::cout << "The slime took " << burn_damage <<" damage from burn.";
        sep();
        *enemy_hp = *enemy_hp - burn_damage;
        turn_timer--;
    }
        if(accuracy > 3){
        std::cout << "The slime hit you for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
        }
        else {
            std::cout << "The slime missed!";
            
            sep();
        }

    }
        }

    if(enemy_type == 2){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1,10);


if(*enemy_hp > 0){
    c = dist(gen)% 3 + 1;
    accuracy = dist(gen);
    damage = dist(gen)% 20 +6;
    if(turn_timer > 0){
        int burn_damage;
        burn_damage = rand() % 15 +3;
        std::cout << "The Fox took " << burn_damage <<" damage from burn.";
        sep();
        *enemy_hp = *enemy_hp - burn_damage;
        turn_timer--;
    }
        if(accuracy > 3){
        std::cout << "The Fox hit you for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
         if(c == 4){
             std:: cout << "The fox scratched you!"<< std:: endl;
             std:: cout << "You are now bleeding!";
         }
        }
        else {
            std::cout << "The Fox missed!";
            
            sep();
            }
        }
    }

    if(enemy_type == 3){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1,10);


if(*enemy_hp > 0){
    if(*enemy_hp <=150 && *enemy_hp>=100){
        
        std::cout << "The King Slime is in a weaked state, your next attacks will heal you!";
        sep();

        *hp =*hp + *drained_hp;
        if(*hp> player_ptr->GetHpcap()){
            *hp = player_ptr->GetHpcap();
        }
    }  
    else{
    accuracy = dist(gen);
    damage = dist(gen)% 30 +6;
    if(turn_timer > 0){
        int burn_damage;
        burn_damage = rand() % 15 +3;
        std::cout << "The King Slime took " << burn_damage <<" damage from burn.";
        sep();
        *enemy_hp = *enemy_hp - burn_damage;
        turn_timer--;
    }
        if(accuracy > 3){
        std::cout << "The King Slime hit you for: " << damage << " damage.";
         *hp = *hp -damage;
         sep();
        }
        else {
            std::cout << "The King Slime missed!";
            
            sep();
                }
            }
        
        }
    }
}
void lvlup(){
    while(player_ptr->Getexp() >= xp_cap){
    player_ptr->setExp(-xp_cap);
    xp_cap +=100;
    player_ptr->setLvl(1);
    player_ptr->setHpcap(10);

    sep();

    std::cout << "You leveled up!"<< std::endl;
    std::cout << "You are now level: "<< player_ptr->Getlvl()<< std::endl;
    std::cout << "And you gained 10 exrta hitpoints.";
    
    if(player_ptr->Getlvl() == 2){
        std::cout << std::endl << "You unlocked Execution!";
    }
    if(player_ptr->Getlvl()== 3){
        std::cout << std::endl << "You unlocked Fireball!";
    }

    }
}

void moveinfo(){
    int info_choice;
    int exit_menu =0;
    char turn_timer;
    while(exit_menu==0){
        info_choice =0;
    sep();
    std::cout << "What move do you want info on?" <<std::endl;
    std::cout << "1 = Attack"<<std::endl;
    std::cout << "2 = Heavy attack"<<std::endl;
    std::cout << "3 = Execute"<<std::endl;
    std::cout << "4 = Fallball"<<std::endl;
    std::cout << "5 = Exit";
    sep();
    std::cin >> info_choice;


    switch (info_choice)
    {
    case 1:
        std::cout<<"Does ok damage and, has a 70"<< "% "<< "chance to hit the target.";
        sep();
        std::cout << "Press any key and enter to continue: ";
        std::cin >> turn_timer;
        break;
    case 2:
        std::cout << "Does heavy damage and, has a 40" << "% "<< "chance to hit the target.";
        sep();
        std::cout << "Press any key and enter to continue: ";
        std::cin >> turn_timer;
        break;

    case 3:
        std::cout << "Has a 5" << "% "<< " chance to hit the target, but always kills.";
        sep();
        std::cout << "Press any key and enter to continue: ";
        std::cin >> turn_timer;
        break;

    case 4:
        std::cout << "Does heavy damage and, has a 60" << "% "<< " chance to hit the target. Also has a 25"<< "% "<< "chance to burn.";
        sep();
        std::cout << "Press any key and enter to continue: ";
        std::cin >> turn_timer;
        break;

    case 5:
        exit_menu++;
        sep();
        break;

    default:
        break;
    }

    }
}
