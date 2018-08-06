#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_POKEMON 6
#define hit 1
#define not 0

void poke_user_stat(int, int, int);
void swap(int *, int *);
void display_stats(int, int);
int atk_power(int, int, int);
int attack_type_modifier(int, int, int , int);
int check_critical(int);
void check_effectiveness(int, int);



char *types[] = {    /*0*/     /*1*/    /*2*/     /*3*/      /*4*/    /*5*/  /*6*/   /*7*/    /*8*/   /*9*/   /*10*/   /*11*/     /*12*/     /*13*/   /*14*/   /*15*/
                    "Normal", "Fight", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychc", "Ice", "Dragon"
                };

struct pokemon_list
{
    char name[31];
    int major_move;
    int minor_move_1;
    int minor_move_2;
    int hp;
    int atk;
    int def;
    int spd;
    int type_1;
    int type_2;
};

const struct pokemon_list pokemon[] = {
                                        {"Charmander", 0, 1, 2, 78, 116, 96, 65, 9, 9},
                                        {"Charmeleon", 3, 4, 5, 116, 158, 129, 80, 9, 9},
                                        {"Charizard",6, 7, 8, 156, 223, 176, 100, 9, 2},
                                        {"Squirtle", 9, 10, 11, 88, 94, 122, 43, 10, 10},
                                        {"Bulbasaur", 12, 13,  14, 90, 118, 118, 45, 11, 3},
                                        {"Pikachu", 15,  16, 5, 70, 112, 101, 90, 12, 12}
                                    };

struct move_list
{
    int id;
    char name[31];
    int dmg;
    int type;
};

const struct move_list move[] = {
                                    {0, "flamethrower", 90, 9},
                                    {1, "Ember", 10, 9},
                                    {2, "Scratch", 6, 0,},
                                    {3, "fireblast ", 140, 9},
                                    {4, "Fire Fang", 11, 9},
                                    {5, "Quick attack", 8, 0},
                                    {6, "Overheat", 160, 9},
                                    {7, "Fire Spin", 14,9},
                                    {8, "Air slash", 14, 2},
                                    {9, "Waterpulse", 70, 10},
                                    {10, "Water gun", 5, 10},
                                    {11, "Hiddenpower", 15 , 0},
                                    {12, "Bulletseed", 90, 11},
                                    {13, "Vine whip", 7, 11},
                                    {14, "Tackle", 5, 0},
                                    {15, "Thunder", 100, 12},
                                    {16, "Charge beam", 8, 12}
                                };
struct user_pokemon
{
    int id;
    int hp;
    int atk;
    int def;
    int spd;
    int type_1;
    int type_2;
    int charge;
}poke[2];

int main()
{
    system("color f1");
    int i, flag, attack_no, poke_num;
    int attacker, defender, level;
    char choice, poke_name[31];
    int move_damage, atk_def_damage;
    int speed_diff, random_no;
    puts("Choose pokemons from the following list:");
    /*
    for (i = 0; i < TOTAL_POKEMON; i++)
    {
        printf("%s\n", pokemon[i].name);
        printf("Major Move = %s\n", pokemon[i].major_move);
        printf("Major Move Damage = %d\n", pokemon[i].major_dmg);
        printf("Minor Move = %s\n", pokemon[i].minor_move);
        printf("Minor Move Damage = %d\n", pokemon[i].minor_dmg);
        printf("HP = %d\t\t", pokemon[i].hp);
        printf("ATK = %d\t\t", pokemon[i].atk);
        printf("DEF = %d\t\t", pokemon[i].def);
        printf("SPD = %d\n", pokemon[i].spd);
        printf("Type = %s", types[pokemon[i].type_1]);
        if (pokemon[i].type_2 == 0)
            printf("\n");
        else
            printf(", %s\n\n", types[pokemon[i].type_2]);
    }
    */
    for (i = 0; i < TOTAL_POKEMON; i++)
        printf("%-29s ", pokemon[i].name);
    puts("\n");

    for(poke_num=0;poke_num<2;poke_num++)
    {
        do
        {
            do
            {
                flag = 0;
                if(poke_num == 0)
                    printf("Enter the name of the FIRST pokemon: ");
                else
                    printf("Enter the name of the SECOND pokemon: ");
                fseek(stdin, 0, 0);
                gets(poke_name);
                for (i = 0; i < TOTAL_POKEMON; i++)
                    if (strcmpi(poke_name, pokemon[i].name) == 0)
                    {
                        printf("Enter %s`s level: ",poke_name);
                        scanf("%d",&level);
                        poke_user_stat(poke_num, i, level);
                        flag = 1;
                        break;
                    }
            }while (flag == 0);

            display_stats(poke[poke_num].id, poke_num);
            printf("Use this pokemon [Y/N]: ");
            fseek(stdin, 0, 0);
            scanf("%c", &choice);
            if (choice >= 'a' && choice <= 'z')
                choice -= 32;
            printf("\n");
        }while (choice == 'N');
    }



    if (pokemon[poke[0].id].spd >=  pokemon[poke[1].id].spd)
    {
        attacker = 0;
        defender = 1;
    }
    else
    {
        attacker = 1;
        defender = 0;
    }

    puts("\nPress any key to begin battle...");
    getch();
    system("cls");
    printf("%s has %d HP \t\t ", pokemon[poke[0].id].name, poke[0].hp);
    printf("%s has %d HP\n", pokemon[poke[1].id].name, poke[1].hp);
    puts("\n\t\t\tBATTLE BEGINS\n");

    while (1)
    {

        if (poke[attacker].charge >= 4)
        {
            printf("which attack will %s use ???\n",pokemon[poke[attacker].id].name);
            printf("1)%s\t2)%s\t3)%s \n)",move[pokemon[poke[attacker].id].minor_move_1].name,move[pokemon[poke[attacker].id].minor_move_2].name,move[pokemon[poke[attacker].id].major_move].name);
            printf("Attack Number : ");
             do
            {
               scanf("%d",&attack_no);
            }while(attack_no!=1 && attack_no!=2 && attack_no!=3);
        }
        else
        {
            printf("which attack will %s use ???\n",pokemon[poke[attacker].id].name);
            printf("1)%s\t2)%s\n",move[pokemon[poke[attacker].id].minor_move_1].name,move[pokemon[poke[attacker].id].minor_move_2].name);
            printf("Attack Number : ");
            do
            {
                scanf("%d",&attack_no);
            }while(attack_no!=1 && attack_no!=2);
        }
        srand(time(0));
        speed_diff=(0.1 * (poke[defender].spd - poke[attacker].spd));
        random_no=rand()%10;


        if(attack_no==1)
        {
            printf("%s uses %s\n", pokemon[poke[attacker].id].name, move[pokemon[poke[attacker].id].minor_move_1].name);
            if(speed_diff == random_no)
                printf("%s dodged\n",pokemon[poke[defender].id].name);
            else
            {
                atk_def_damage = atk_power(move[pokemon[poke[attacker].id].minor_move_1].dmg, poke[attacker].atk, poke[defender].def);
                move_damage = attack_type_modifier(atk_def_damage, move[pokemon[poke[attacker].id].minor_move_1].type,pokemon[poke[defender].id].type_1,pokemon[poke[defender].id].type_2);
                srand(time(0));
                if(check_critical(rand()%100) == hit)
                    {
                        poke[defender].hp -= (move_damage * 1.5);
                        printf("Critical Hit!!!\n");
                    }
                else
                    poke[defender].hp -= move_damage;
                check_effectiveness(move_damage, atk_def_damage);
                poke[attacker].charge++;
            }

        }
        else if(attack_no==2)
        {
            printf("%s uses %s\n", pokemon[poke[attacker].id].name,  move[pokemon[poke[attacker].id].minor_move_2].name);
            if (speed_diff == random_no)
                printf("%s dodged\n",pokemon[poke[defender].id].name);
            else
            {
                atk_def_damage = atk_power(move[pokemon[poke[attacker].id].minor_move_2].dmg, poke[attacker].atk, poke[defender].def);
                move_damage = attack_type_modifier( atk_def_damage, move[pokemon[poke[attacker].id].minor_move_2].type,pokemon[poke[defender].id].type_1,pokemon[poke[defender].id].type_2);
                srand(time(0));
                if(check_critical(rand()%100) == hit)
                {
                    poke[defender].hp -= (move_damage * 1.5);
                    printf("Critical Hit!!!\n");
                }
                else
                    poke[defender].hp -= move_damage;
                check_effectiveness(move_damage, atk_def_damage);
                poke[attacker].charge++;
            }
        }
        else if(attack_no==3)
        {
            printf("%s uses %s\n", pokemon[poke[attacker].id].name,  move[pokemon[poke[attacker].id].major_move].name);
            if(speed_diff == random_no)
                printf("%s dodged\n",pokemon[poke[defender].id].name);
            else
            {
                atk_def_damage = atk_power(move[pokemon[poke[attacker].id].major_move].dmg, poke[attacker].atk, poke[defender].def);
                move_damage = attack_type_modifier(atk_def_damage, move[pokemon[poke[attacker].id].major_move].type,pokemon[poke[defender].id].type_1,pokemon[poke[defender].id].type_2);
                srand(time(0));
                if(check_critical(rand()%100) == hit)
                {
                    poke[defender].hp -= (move_damage * 1.5);
                    printf("Critical Hit!!!\n");
                }
                else
                    poke[defender].hp -= move_damage;
                check_effectiveness(move_damage,atk_def_damage);
                poke[attacker].charge -= 4;
            }
        }


        if (poke[defender].hp <= 0)
        {
            poke[defender].hp = 0;
            printf("%s has %d HP \t\t", pokemon[poke[0].id].name, poke[0].hp);
            printf("%s has %d HP\n\n", pokemon[poke[1].id].name, poke[1].hp);
            break;
        }
            printf("%s has %d HP \t\t", pokemon[poke[0].id].name, poke[0].hp);
            printf("%s has %d HP\n\n", pokemon[poke[1].id].name, poke[1].hp);

        swap(&attacker, &defender);
        getch();
    }

    printf("\n%s wins.\n",pokemon[poke[attacker].id].name);

    return 0;
}

void poke_user_stat(int j, int i, int level)
{
    poke[j].id = i;
    poke[j].hp = 15 + (level/100.0) * pokemon[i].hp;
    if(poke[j].hp>pokemon[i].hp)
        poke[j].hp=pokemon[i].hp;
    poke[j].atk = 8 + (level/100.0) * pokemon[i].atk;
    if(poke[j].atk>pokemon[i].atk)
        poke[j].atk=pokemon[i].atk;
    poke[j].def = 5 + (level/100.0) * pokemon[i].def;
    if(poke[j].def>pokemon[i].def)
        poke[j].def=pokemon[i].def;
    poke[j].spd = 8 + (level/100.0) * pokemon[i].spd;
    if(poke[j].spd>pokemon[i].spd)
        poke[j].spd=pokemon[i].spd;
    poke[j].charge = 0;
}
//To change the attackers turn//
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// To print the pokemons status//
void display_stats(int i, int j)
{
    printf("Major Move = %-20s     Damage = %d\n", move[pokemon[i].major_move].name, move[pokemon[i].major_move].dmg);
    printf("Minor Move (1) = %-20s Damage = %d\n", move[pokemon[i].minor_move_1].name, move[pokemon[i].minor_move_1].dmg);
    printf("Minor Move (2) = %-20s Damage = %d\n", move[pokemon[i].minor_move_2].name, move[pokemon[i].minor_move_2].dmg);
    printf("HP = %-3d \t ATK = %-3d \t DEF = %-3d \t SPD = %-3d\n", poke[j].hp, poke[j].atk, poke[j].def, poke[j].spd);
    if(pokemon[i].type_2 == pokemon[i].type_1)
        printf("Type : %s\n ", types[pokemon[i].type_1]);
    else
        printf("Type : %s, %s\n", types[    pokemon[i].type_1], types[pokemon[i].type_2]);
}

int atk_power(int atk_damage, int attacker_atk, int defender_def)
{
    int atk_def_damage;

    atk_def_damage = atk_damage + 0.1*(attacker_atk - defender_def);
    if(atk_def_damage<2)
                    return 2;
    else
        return atk_def_damage;
}
//to calculate the damage according to type of pokemon and the attack//
int attack_type_modifier(int move_damage, int move_type, int defender_type_1, int defender_type_2)
{
    float dmg_multiplying_table[16][16]={

                                        /*1Normal*/1, 1, 1, 1, 1, 0.5, 1, 0, 0.5, 1, 1, 1, 1, 1, 1, 1,
                                        /*2Fight*/ 2, 1, 0.5, 0.5, 1, 2, 0.5, 0, 2, 1, 1, 1, 1 ,0.5, 2, 1,
                                        /*3Flying*/1, 2, 1, 1, 1, 0.5, 2, 1, 0.5, 1, 1, 2, 0.5, 1, 1, 1,
                                        /*4Poison*/1, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 0, 1, 1, 2, 1, 1, 1, 1,
                                        /*5Ground*/1, 1, 0, 2, 1, 2, 0.5, 1, 2, 2, 1, 0.5, 2, 1, 1, 1,
                                        /*6Rock*/  1, 0.5, 2, 1, 0.5, 1, 2, 1, 0.5, 2, 1, 1, 1, 1, 2, 1,
                                        /*7Bug*/   1, 0.5, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 0.5, 1, 2, 1, 2, 1, 1,
                                        /*8Ghost*/ 0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1,
                                        /*9Steel*/ 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 1, 2, 1,
                                        /*10Fire*/  1, 1, 1, 1, 1, 0.5 , 2, 1, 2, 0.5, 0.5, 2, 1, 1, 2, 0.5,
                                        /*11Water*/ 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 0.5,
                                        /*12Grass*/ 1, 1, 0.5, 0.5, 2, 2, 0.5, 1, 0.5, 0.5, 2, 0.5, 1, 1, 1, 0.5,
                                        /*13Electr*/1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 0.5,
                                        /*14Psychc*/1, 2, 1, 2, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 0.5, 1, 1,
                                        /*15Ice*/   1, 1, 2, 1, 2, 1, 1, 1, 0.5, 0.5, 0.5, 2, 1, 1,0.5, 2,
                                        /*16Dragon*/1, 1, 1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 1, 1, 2
                                        };
	move_damage *= dmg_multiplying_table[move_type][defender_type_1] ;
	if(defender_type_2 != defender_type_1)
        move_damage *= dmg_multiplying_table[move_type][defender_type_2 ];
	return (move_damage);
}

//to check probability for critical//
int check_critical(int random)
{
    int i;
    for(i=11;i<100;i+=11)
        if(random==i)
            return hit;
    return not;
}

//to print super effective Not so Effective or Not Effective!!!//
void check_effectiveness(int move_damage, int initial_move_damage)
{
    if(move_damage>initial_move_damage)
        printf("Super Effective!!!\n");
    else if (move_damage<initial_move_damage)
        printf("Not so Effective!!!\n");
    else if (move_damage==0)
        printf("Not Effective!!!\n");

}
