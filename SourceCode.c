#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>

void startGame();
void menu() ;
void settings();
int rollDice();
int isDanger();
struct healCard defineStructs();
void Rand();
void addToAttack();
void addToHeal();
struct healCard getHeal();
struct attackCard getAttack();
struct monster getMonster();
void showBag();
void useHeal(struct monster newMonster);
struct monster useAttack(struct monster newMonster);
void fight(struct monster newMonster);
void pointCalc();
void store();
void useSupCards(struct monster newMosnter);
void printAbout() {
    printf("\nABOUT:\n-----------------------------------------\nWelcome to MonoWar strategy game. Your main purpose is to reach end of the path. You move forward or backward by randomly by using progress cards to move on the path. You will encounter many monsters as you progress along the path. You can defeat them easily thanks to the battle cards you collect. If the monster has damaged you, you can heal yourself using the food cards and continue your amazing journey. \n");
    printf("-----------------------------------------\n");
} 

struct monster {
    char *name;
    int health;
    int damageCap;
}crow, trex, akula;

struct attackCard {
    char *name;
    int attackCap;
} attack20, attack40, attack60,attack200;

struct healCard {
    char *name;
    int healCap;
}heal20, heal40, heal60, heal200;

struct character {
    int pos;
    int health;
    int point;
    int attackTurn;
    char* nickname;
    int choosenDif;
    int killCount;
    int gainedPoints;
    unsigned SupCards;
    struct monster monstersCh[100];
    struct attackCard myAttackCards[100];
    struct healCard myHealCards[100];
} adam;


void showStatistics() {
    printf("\nPos: %d, Health: %d, Name: %s\n", adam.pos,adam.health, adam.nickname);
} 

void startGame() {
    int check,a;
    char choice2, any, choice3;
    struct monster newMonster;
    newMonster = getMonster();
    char i;
    
    if (adam.pos >= 100) {
    printf("\n[Wow! You're amazing!]\n[You Won the Game! Good job!]\n");
    pointCalc();
   // exit(1);
    } 
  
    printf("\n--------GAME---------");
    printf("\n(1)ROLL DICE(1)");
    printf("\n(2)SUPERCARDS(2)");
    printf("\n(3)ENVANTORY(3)");
    printf("\n(0)BACK(0)");
    printf("\n---------------------");
    showStatistics();
    printf("---------------------");
    printf("\nChoose one of them:");
    int cell;
        scanf(" %c%*[^\n]", &choice2);
        switch(choice2) {
            case '1': cell = rollDice();
                    printf("\n\n[You moved forward %d cells]", cell) ;
                    adam.pos = adam.pos + cell;
                    addToHeal(getHeal());
                    addToAttack(getAttack());
                    sleep(1);
            if (adam.pos < 20) {
                a = 1;
            } else 
                a = isDanger();
            if (a==2){
            	printf("\n[Danger, there is a \"%s\"]", newMonster.name);
            	sleep(1);
            	do {
            if (adam.health <= newMonster.damageCap) {
            printf("\n[Oh, Monster killed you! :(] ");
            printf("\n\n\t\t~~GAME OVER~~");
            exit(1);
            } 
            
            printf("\n[Oh,%s attacked to you!]",newMonster.name);
            printf("\n[Your health decreased %d]\n",newMonster.damageCap);
            adam.health=adam.health-newMonster.damageCap;
            printf("\n------YourInfo-------");
            showStatistics();
            printf("------EnemyInfo------");
            printf("\nPower: %d, Health: %d, Name: %s", newMonster.damageCap,newMonster.health, newMonster.name);
            printf("\n---------------------\n");
            printf("(1)ATTACK(1)\n");
            printf("(2)HEAL(2)\n");
            printf("(3)ENVANTORY(3)\n");
            printf("---------------------\n");
            printf("Choose one of them:");
            scanf(" %c%*[^\n]", &choice2);
            switch (choice2) {
            case '1': newMonster = useAttack(newMonster) ;
            break;
            case '2': useHeal(newMonster);
            break;
            case '3': 
            showBag();
            adam.health=adam.health+newMonster.damageCap; 
            break;
            default: printf("\n!!Please Choose Again!!\n");adam.health=adam.health+newMonster.damageCap;
            } 
            		}
            		while(newMonster.health>0);
            	} else {
            		printf("\n[You're lucky there's no Monster at %d]\n", adam.pos); 
                        adam.gainedPoints = adam.gainedPoints + 10;
                        startGame();
            }

                        
                
            break;
            case '2': store(); startGame();
            break;
            case '3': showBag(); printf("\n:Please press any key:");scanf(" %c%*[^\n]", &any); startGame();
            break;
            case '0':  printf("\n[You're back!] \n"); menu() ;
            break;
            default: printf("\n!!Please Choose Again!!\n"); startGame(); 
            break;
        } 
        printf("\n[Congratulations! You killed Monster]"); 
        printf("\n[Now, you can continue your journey]\n");
        adam.killCount++;
        adam.gainedPoints = adam.gainedPoints + 10;
    
    
    
    startGame();
} 
void menu() {    
    printf("\n--------MENU--------");
    printf("\n(1)START(1)");
    printf("\n(2)SETTINGS(2)");
    printf("\n(3)ABOUT(3)");
    printf("\n(0)EXIT(0)\n");
    printf("---------------------");
    printf("\nChoose one of them:");
    char choice;
 
    scanf(" %c%*[^\n]",&choice);

    switch (choice) {
        case '1' :startGame();
        break;
        case '2': settings();
        break;
        case '3' : printAbout(); menu();
        break;
        case '0' : printf("\nSee you, %s!", adam.nickname); exit(0);
        break;
        default: 
            printf("\n!!Please Choose Again!!\n"); menu();
                   
    }
    
    
        
} 

int main()
{
    printf("Welcome to MonoWar,\n\nEnter your nick:");
    char nick[10];
    scanf("%s%*[^\n]", nick);
    adam.nickname = nick;
    adam.health = 100;
    puts("");
    printf("Hello %s,\n", adam.nickname); 
    menu();
    
    
}

void settings() {
    puts("") ;
    printf("\n------SETTINGS-------\n");
    printf("(1)CHANGE NICKNAME(1)\n");
    printf("(2)CHANGE DIFFICULTY(2)\n");
    printf("(0)BACK(0)");
    printf("\n---------------------\n");
    int check=1;
    printf("Choose one of them:");
    char newNick[10];
    
    while (check) {
        char choice, choice2;
        scanf(" %c%*[^\n]", &choice);
        switch (choice) {
            case '1': printf("\nInput New Nickname:"); scanf("%s", newNick);adam.nickname = newNick; printf("[Nickname Changed to \"%s\"]\n", adam.nickname);menu() ;
            break;
            case '2': printf("\nChoose Difficulty (0-Peaceful/1-Hard): ");
            break;
            case '0': printf("\n[You Exited!]\n"); menu() ;
            break;
            default: printf("\n!!Please Choose Again!!"); settings();
        }
        scanf(" %c%*[^\n]", &choice2);
            if (choice2 == '0') {
                adam.choosenDif = 0;
                printf("\n[Difficulty set as \"Peaceful\"]\n");
                menu();
            } else if (choice2 == '1') {
                adam.choosenDif = 1;
                printf("\n[Difficulty set as \"Hard\"]\n");
                menu();
            } else {
                printf("\n!!Please Choose Again!!"); settings();
                
            }
    }
}
int rollDice() {
    int int1, int2,intTop;
    int j=0;
    srand(time(NULL));
    puts("");
    for (j; j<4; j++){
        int1 = 1 + rand()%6;
        int2 = 1 + rand()%6;
        sleep(1);
        if (j != 3) 
            printf("Rolling>> "); 
        else {
            printf("Rolled: ");
            intTop = int1 + int2;}
        printf("%d & %d", int1, int2);
        if (j != 3) 
            printf(" <<Rolling\n"); 
        
    }
    return intTop;
}
int isDanger(){
  srand(time(NULL));
  int int1;
  int1 = 1 + rand()%2;
  
  return int1;
}

struct monster getMonster() {

    // Monster - CROW
    crow.health = 25;
    crow.damageCap = 10;
    crow.name = "Crow";
    
    // Monster - T-REX
    trex.health = 50;
    trex.damageCap = 20;
    trex.name = "T-Rex";
    
    // Monster - AKULA
    akula.health = 75;
    akula.damageCap = 30;
    akula.name = "Akula";
    
    srand(time(NULL)*3);
    int rand1;
    if (adam.choosenDif == 0){
    rand1 = 0 + rand()%2;
    }
    
    if (adam.choosenDif == 1){
    rand1 = 1 + rand()%2;
    }
    
    // Monster Array
    struct monster monsters[3] = {crow, trex, akula};
    return monsters[rand1];
} 

 struct attackCard getAttack() { 
    // Attack - attack20
    attack20.name = "attack20";
    attack20.attackCap = 20;
    
    // Attack - attack40
    attack40.name = "attack40";
    attack40.attackCap = 40;
    
    // Attack - attack60
    attack60.name = "attack60";
    attack60.attackCap = 60;
    
    srand(time(NULL));
    int rand1;
    rand1 = 0 + rand()%3;
    
    // Attack Card Array
    struct attackCard attackCards[] = {attack20, attack40, attack60};
    return attackCards[rand1];
       
} 

struct healCard getHeal() {
    // Heal - heal20
    heal20.name = "heal20";
    heal20.healCap = 20;
    
    // Heal - heal40
    heal40.name = "heal40";
    heal40.healCap = 40;
    
    // Heal - heal60
    heal60.name = "heal60";
    heal60.healCap = 60;
    
    srand(time(NULL)*2);
    int rand2;
    rand2 = 0 + rand()%3;
    
    
    // Heal Card Array
    struct healCard healCards[] = {heal20, heal40, heal60};
    return healCards[rand2];
}

void addToAttack(struct attackCard newAttackCard) {
    int i = 0,check=1;
    while (check) {
    if (adam.myAttackCards[i].name == NULL) {
    adam.myAttackCards[i] = newAttackCard;
    printf("\n[You got: %s]\n",adam.myAttackCards[i].name);
    check=0; 
    }  else
            i++;
   } 
}
void addToHeal(struct healCard newHealCard) {
    int i = 0,check=1;
    while (check) {
    if (adam.myHealCards[i].name == NULL) {
    adam.myHealCards[i] = newHealCard;
    printf("\n[You got: %s]",adam.myHealCards[i].name);
    check=0; 
    }  else
            i++;
   } 
}

void showBag() {
    printf("\n------ENVANTORY-----\n");
    int i,j;
    printf("  Your HEAL Cards:\n");  
    for (i=0; i<100; i++) {
        if (adam.myHealCards[0].name == NULL){ 
            printf("There is no any HEAL Card\n");
            break;} 
        printf("%s\n", adam.myHealCards[i].name);
        if (adam.myHealCards[i+1].name == NULL)
            break;
    }
    printf("\n  Your ATTACK Cards:\n");  
    for (i=0; i<100; i++) {
        if (adam.myAttackCards[0].name == NULL){ 
            printf("There is no any ATTACK Card\n");
            break;
            }
        printf("%s\n",adam.myAttackCards[i].name);
        if (adam.myAttackCards[i+1].name == NULL)
            break;
    }
    
    printf("---------------------");
    
}

void useHeal(struct monster newMonster) {
    if (adam.health == 100) {
        printf("\n[Your health is full]\n"); 
        startGame();
    }
    struct healCard newHeal20;
    struct healCard newHeal40;
    struct healCard newHeal60;
    newHeal20.name = "heal20";
    newHeal20.healCap = 20;
    newHeal40.name = "heal40";
    newHeal40.healCap = 40;
    newHeal60.name = "heal60";
    newHeal60.healCap = 60;
    char i;
    int a,b, count=0, pos=0;
    printf("\n---------HEAL--------\n");
    printf("(1)HEAL20(1)\n");
    printf("(2)HEAL40(2)\n");
    printf("(3)HEAL60(3)\n");
    printf("(4)SUPERHEALCARD(4)\n");
    printf("(0)BACK(0)\n");
    printf("---------------------");
    printf("\nChoose one of them:");
    scanf(" %c%*[^\n]", &i);
    
    switch (i) {
        case '1': 
            for (a=0; a<100; a++) {
                if(adam.myHealCards[a].name == newHeal20.name){
                    count++;
                    pos = a;
                    break;
                }        
            } 
        
            if (count == 0) {
                printf("\n[You don't have any HEAL20 Card]\n");
                useHeal(newMonster);
            }
            
            for (a=pos; a<100; a++) {
                adam.myHealCards[a] = adam.myHealCards[a+1];
            }
            
            
            if (adam.health < 100) {
                adam.health = adam.health + newHeal20.healCap;
                if (adam.health > 100) 
                    adam.health = 100;
            }
        break;
        case '2':
            for (a=0; a<100; a++) {
                if(adam.myHealCards[a].name == newHeal40.name){
                    count++;
                    pos = a;
                    break;
                }        
            } 
        
            if (count == 0) {
                printf("\n[You don't have any HEAL40 Card]\n");
                useHeal(newMonster);
            }
            
            for (a=pos; a<100; a++) {
                adam.myHealCards[a] = adam.myHealCards[a+1];
            }
            
            
            if (adam.health < 100) {
                adam.health = adam.health + newHeal40.healCap;
                if (adam.health > 100) 
                    adam.health = 100;
            }
            
        break;
        case '3':
            for (a=0; a<100; a++) {
                if(adam.myHealCards[a].name == newHeal60.name){
                    count++;
                    pos = a;
                    break;
                }        
            } 
        
            if (count == 0) {
                printf("\n[You don't have any HEAL60 Card]\n");
                useHeal(newMonster);
            }
            
            for (a=pos; a<100; a++) {
                adam.myHealCards[a] = adam.myHealCards[a+1];
            }
            
            
            if (adam.health < 100) {
                adam.health = adam.health + newHeal60.healCap;
                if (adam.health > 100) 
                    adam.health = 100;
            }
            
        break;
        
        case '4': 
        	if (adam.myHealCards[99].name != NULL){
            				adam.health = adam.health + adam.myHealCards[99].healCap;
            				adam.myHealCards[99].name = NULL;
						} else {
							printf("You don't have any SuperHealthCard");
							useHeal(newMonster);
						}
		break;
        case '0': adam.health=adam.health+newMonster.damageCap;
        break;
        default: printf("\n!!Please Choose Again!!\n"); useHeal(newMonster);
                
    }
}

struct monster useAttack(struct monster newMonster) {
	struct attackCard newAttack20;
	struct attackCard newAttack40;
	struct attackCard newAttack60;

	newAttack20.name = "attack20";
	newAttack20.attackCap = 20;
	
	newAttack40.name = "attack40";
	newAttack40.attackCap = 40;
	
	newAttack60.name = "attack60";
	newAttack60.attackCap = 60;

int a, pos, count=0;
	
    printf("\n(1)ATTACK20(1)\n");
    printf("(2)ATTACK40(2)\n");
    printf("(3)ATTACK60(3)\n");
    printf("(4)SUPERATTACKCARD(4)\n");
    printf("(0)BACK(0)");
    printf("\n---------------------");
    printf("\nChoose one of them:");
    char choice;
    scanf(" %c%*[^\n]", &choice);
    switch (choice) {
    case '1': 
    for (a=0; a<100; a++) {
                if(adam.myAttackCards[a].name == newAttack20.name){
                    count++;
                    pos = a;
                    break;
                }        
            }
    if (count == 0) {
        printf("\n[You dont have any ATTACK20 Card]\n");
        return useAttack(newMonster);
    }
           
            for (a=pos; a<100; a++) {
                adam.myAttackCards[a] = adam.myAttackCards[a+1];
            }
    
    newMonster.health = newMonster.health-newAttack20.attackCap;
    break;
    
    case '2': 
    for (a=0; a<100; a++) {
                if(adam.myAttackCards[a].name == newAttack40.name){
                    count++;
                    pos = a;
                    break;
                }        
            }
    if (count == 0) {
        printf("\n[You dont have any ATTACK40 Card]\n");
        return useAttack(newMonster);
    }
           
            for (a=pos; a<100; a++) {
                adam.myAttackCards[a] = adam.myAttackCards[a+1];
            }
    
    newMonster.health = newMonster.health-newAttack40.attackCap;
    break;
    
    case '3': 
    for (a=0; a<100; a++) {
                if(adam.myAttackCards[a].name == newAttack60.name){
                    count++;
                    pos = a;
                    break;
                }        
            }
    if (count == 0) {
        printf("\n[You dont have any ATTACK60 Card]\n");
        return useAttack(newMonster);
    }
           
            for (a=pos; a<100; a++) {
                adam.myAttackCards[a] = adam.myAttackCards[a+1];
            }
    
    newMonster.health = newMonster.health-newAttack60.attackCap;
    break;
    
    case '4' : 
    	if (adam.myAttackCards[99].name != NULL){
            				newMonster.health = newMonster.health - adam.myAttackCards[99].attackCap;
            				adam.myAttackCards[99].name = NULL;
						} else {
							printf("\n[You don't have any SuperAttackCard]\n");
    						return useAttack(newMonster);
						}
	break;
    case '0': adam.health = adam.health + newMonster.damageCap;
    break;
    
    default: printf("\n!!Please Choose Again!!\n");
    useAttack(newMonster);
    }
    
    if (adam.myAttackCards[0].name == NULL && newMonster.health > 0) {
            printf("\n[You don't have Attack Card to kill Monster]");
            printf("\n\n\t\t~~GAME OVER~~");
            sleep(1); 
            exit(1);
            } 
    
    return newMonster;
   
} 

void pointCalc() {
    adam.gainedPoints = adam.gainedPoints + adam.killCount*15;
    printf("[You gained %d points, Well done!]\n", adam.gainedPoints);
}

void store(){
	int a,b,answer1;
	int c,d,answer2;
	struct healCard heal200;
	heal200.name = "SuperHealCard";
	heal200.healCap = 200;
	struct attackCard attack200;
	attack200.name = "SuperAttackCard";
	attack200.attackCap = 200;
	
	if (adam.SupCards != 0){
		printf("\n[Sorry, you have already used SuperCards]\n");
		startGame();
	}
	
	printf("\n|You will see questions and if you answer correctly, you will get SuperCards|\n");
	
	a = rand(), b = rand();
	c = rand(), d = rand();
	
	
	// SuperHealth
	printf("\nQuestion for SuperHealthCard:\n");
	printf("a = %d, b = %d\na + b = ? = ",a,b);
	
	while ( scanf(" %d", &answer1) == 0 && scanf(" %c%*[^\n]", &answer1) == 1 ){
		printf("\n!!Please Input Integer!!\n\n");
	    printf("|Question for SuperHealthCard:|\n");
		printf("a = %d, b = %d\na + b = ? = ",a,b);
	}
	if (answer1 == a+b){
		printf("\n[You are awesome, you got SuperHealthCard]\n");
		adam.myHealCards[99] = heal200;
	} else 
		printf("\n[Sorry, your answer is not correct :( ]\n");
	

	// SuperAttack	
	printf("\n|Question for SuperAttackCard:|\n");
	printf("c = %d, d = %d\nc x d= ? = ",c,d);
	
	while ( scanf(" %d", &answer2) == 0 && scanf(" %c%*[^\n]", &answer2) == 1 ){
	    printf("\n!!Please Input Integer!!\n");
		printf("\n|Question for SuperAttackCard:|\n");
		printf("c = %d, d = %d\nc x d= ? = ",c,d);
	}
	if (answer2 == c * d){
		printf("\n[You are awesome, you got SuperAttackCard]\n");
		adam.myAttackCards[99] = attack200;
	} else 
		printf("\n[Sorry, your answer is not correct :( ]\n");
	
	adam.SupCards = 1;
}

    // MonoWar		14 Oct 2022 - 4:18    (version 1.0.0)
	// AU - Aliyev Ulvi	(creator)














    
    
