#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

struct leftChange
{
    unsigned int nom;
    unsigned int left = 400;
};

struct merch
        {
        char* name;
        unsigned int cost;
        unsigned int amount = 15;
        };

void setMerch (struct merch* mlist)
        {
        mlist[0].name = "9x18mm\0";
        mlist[1].name = "9x19mm Parabellum\0";
        mlist[2].name = "5.7x28mm\0";
        mlist[3].name = "6,35x15mm Browning\0";
        mlist[4].name = ".45 ACP\0";
        mlist[5].name = "0.50 AE\0";

        mlist[6].name = "Glock-18\0";
        mlist[7].name = "Glock-21\0";
        mlist[8].name = "Stechkin's Pistol\0";
        mlist[9].name = "H&K USP\0";
        mlist[10].name = "Walther PP\0";
        mlist[11].name = "Beretta 92\0";
        mlist[12].name = "FN Five-seveN\0";
        mlist[13].name = "CZ-75 Auto\0";
        mlist[14].name = "Desert Eagle\0";

        mlist[0].cost = 50;
        mlist[1].cost = 75;
        mlist[2].cost = 130;
        mlist[3].cost = 80;
        mlist[4].cost = 150;
        mlist[5].cost = 300;

        mlist[6].cost = 500;
        mlist[7].cost = 750;
        mlist[8].cost = 475;
        mlist[9].cost = 825;
        mlist[10].cost = 750;
        mlist[11].cost = 1000;
        mlist[12].cost = 1500;
        mlist[13].cost = 1725;
        mlist[14].cost = 2000;

    }

bool canChange(unsigned int mny, struct merch* mlist, struct leftChange* coins)
{
    int i = 0, change = 0, dif, j = 0, buf;
    for(i = 0; i < 15 && mlist[i].amount != 0; i++)
    {
        dif = mny - mlist[i].cost;
        if(dif == 0)
            return true;
        buf = coins[j].left;
        for(; buf != 0 && j < 4;)
        {
            change += coins[j].nom;
            buf--;
            if(dif < change)
            {
                change -= coins[j].nom;
                j++;
            }
            if(buf == 0)
                j++;
        }
        if(dif == change)
            return true;
    }
    return false;
}

bool canChangeNow(unsigned int mny, unsigned int code,struct merch* mlist, struct leftChange* coins)
{
    int change = 0, dif, j = 0, buf;
        dif = mny - mlist[code].cost;
        if(dif == 0)
            return true;
        buf = coins[j].left;
        for(; buf != 0 && j < 4;)
        {
            change += coins[j].nom;
            buf--;
            if(dif < change)
            {
                change -= coins[j].nom;
                j++;
            }
            if(buf == 0)
            {
                j++;
                buf = coins[j].left;
            }
            if(dif == change)
                return true;
        }
    return false;
}


bool serviceCheck( struct merch* mlist, struct leftChange* coins)
        {
                if(canChange(50, mlist, coins) || canChange(100, mlist, coins) || canChange(200, mlist, coins) || canChange(500, mlist, coins))
                    return false;
                return true;
        }

int giveChange(unsigned int mny, unsigned int cost, struct leftChange* coins)
        {
            unsigned int i = 0, change = 0, dif;
            dif = mny - cost;
            if(dif == 0)
                return 0;
            for(; coins[i].left != 0 && i < 4;)
            {
                change += coins[i].nom;
                coins[i].left--;
                if(dif < change)
                {
                    coins[i].left++;
                    change -= coins[i].nom;
                    i++;
                }
                if(coins[i].left == 0)
                    i++;
                if(dif == change)
                    return change;
            }
            return -1;
        }

int main() {
    setlocale(LC_CTYPE, "Russian");
    unsigned int E = 0, curPaper = 0, ST = 1, i, code;
    int dif;
    string magicWord;
    struct leftChange coins[4];
    struct merch list[15];

    coins[0].nom = 10;
    coins[1].nom = 5;
    coins[2].nom = 2;
    coins[3].nom = 1;
    setMerch(&list[0]);

    while (1)
    {
        if(serviceCheck(&list[0], &coins[0]))
        {
            ST = 0;
            cout << "Need service bad(PLS HELP)";
        }

        switch (ST)
        {
            case 0 :
                goto I_WANNA_SERVICE;
            case 1 :
                goto SHOW_YA_MONEY;
            case 2:
                goto TAKE_A_LOOK_AT_THAT;
        }

        I_WANNA_SERVICE:
            cin >> magicWord;
            if (magicWord == "srvop17")
            {
                E = 0;
                curPaper = 0;
                ST = 1;
                for (i = 0; i < 7; i++)
                {
                    if (i < 4)
                        coins[i].left = 400;
                    list[i].amount = 15;
                }
                cout << "Service completed" << endl;
            }
            else if(magicWord == "Off")
            {
                cout <<"WellByeNow";
                break;
            }
            else
                {
                    cout << "I don't know you" << endl;
                    goto  I_WANNA_SERVICE;
                }

        SHOW_YA_MONEY:
            printf("GIMME YO MONEY: ");
            cin >> curPaper;
            if ((curPaper == 50 || curPaper == 100 || curPaper == 200 || curPaper == 500) && canChange(curPaper + E, &list[0], &coins[0]))
            {
                while(1)
                {
                    E += curPaper;
                    curPaper = 0;
                    printf("Payin more?: ");
                    cin >> curPaper;
                    if((curPaper == 50 || curPaper == 100 || curPaper == 200 || curPaper == 500) && canChange(curPaper + E, &list[0], &coins[0]))
                        continue;
                    else if(curPaper != 50 && curPaper != 100 && curPaper != 200 && curPaper != 500)
                    {
                        cout << "Okay, I think u won't put money in anymore" << endl;
                        ST = 2;
                        curPaper = 0;
                        break;
                    }
                    else
                        {
                            cout << "No change for ya, buddy. Take it back" << endl;
                            curPaper = 0;
                            continue;
                        }
                }
                ST = 2;
            }
            else if(curPaper == 7355608)
            {
                cout << "K, time to service(boom)" << endl;
                ST = 0;
                goto I_WANNA_SERVICE;
            }
            else if(curPaper != 50 && curPaper != 100 && curPaper != 200 && curPaper != 500)
            {
                cout << "WTF is yo money, bro, take it back!" << endl;
                curPaper = 0;
                goto SHOW_YA_MONEY;
            }
            else
                {
                    cout << "No change for ya, buddy. Take it back" << endl;
                    curPaper = 0;
                    goto SHOW_YA_MONEY;
                }

        TAKE_A_LOOK_AT_THAT:
            for(i = 0; i < 15; i++)
                if(list[i].amount)
                {
                    printf("%18s | cost: %4u | left: %2u | code: %d\n", list[i].name, list[i].cost, list[i].amount, i);
                }
            cout << endl <<"Watchu want?";
            cin >> code;
            if(!list[code].amount)
            {
                cout << "No more of dat left, chose smt else" << endl;
                goto TAKE_A_LOOK_AT_THAT;
            }
            if(!canChangeNow(E, code, &list[0], &coins[0]))
            {
                cout << "No change for ya, buddy. Chose smt else" << endl;
                goto TAKE_A_LOOK_AT_THAT;
            }
            dif = (int) E - list[code].cost;
            if(dif >= 0)
            {
                cout << "Ok, deal, imma give you that" << endl << "(Take your thing)" << endl;
                list[code].amount--;
                system("pause");
                if(dif != 0)
                {
                    cout << "Here's your change: " << giveChange(E, list[code].cost, &coins[0]) << " RUB" << endl << "Have a nice day" << endl;
                    ST = 1;
                    E = 0;
                }
                else
                    {
                        cout << "Have a nice day" << endl;
                        ST = 1;
                        E = 0;
                    }
            }
            else
                {
                    cout << "Not enough mny, pay more" << endl;
                    ST = 1;
                    goto SHOW_YA_MONEY;
                }
    }
    return 0;
}