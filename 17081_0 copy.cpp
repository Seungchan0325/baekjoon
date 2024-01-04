#include <bits/stdc++.h>

using namespace std;

string game_over_message;

class Item {
public:
    char type;
    Item(char _type) : type(_type) {}
    virtual ~Item() {}
};

class Weapon : public Item {
public:
    int ATK;
    Weapon() : Item('W'), ATK(0) {}
    virtual ~Weapon() {}
};

class Armor : public Item {
public:
    int DEF;
    Armor() : Item('A'), DEF(0) {}
    virtual ~Armor() {}
};

class Accessory : public Item {
public:
    string effect;
    Accessory() : Item('O'), effect("") {}
    virtual ~Accessory() {}
};

class ItemBox {
public:
    int r, c;
    Item* item;
    ItemBox() : r(0), c(0) {}
};

class Entity {
public:
    int r, c;
    int HP, FULL_HP;
    int ATK;
    int DEF;
    bool is_dead;
    Entity() : r(0), c(0), HP(0), FULL_HP(0), ATK(0), DEF(0), is_dead(false) {}
};

class Monster : public Entity {
public:
    bool is_boss;
    string name;
    int EXP;
    Monster() : Entity(), is_boss(false), name(""), EXP(0) {}
};

class Player : public Entity {
public:
    int start_r;
    int start_c;
    int LV;
    int EXP;
    int MAX_EXP;
    Weapon* weapon;
    Armor* armor;
    vector<Accessory*> accessories;

    Player() : Entity() {
        HP = FULL_HP = 20;
        ATK = DEF = 2;
        LV = 1;
        EXP = 0;
        MAX_EXP = 5 * LV;

        weapon = nullptr;
        armor = nullptr;
    }

    bool searchAccessory(string effect) {
        for(auto accessory : accessories)
            if(accessory->effect == effect)
                return true;
        return false;
    }

    void removeAccessory(string effect) {
        auto it = accessories.begin();
        for(; it != accessories.end(); it++)
            if((*it)->effect == effect) break;
        assert(it != accessories.end());
        accessories.erase(it);
    }

    int getATK() {
        int ret = ATK;
        if(weapon != nullptr)
            ret += weapon->ATK;
        return ret;
    }

    int getDEF() {
        int ret = DEF;
        if(armor != nullptr)
            ret += armor->DEF;
        return ret;
    }

    // return true, if the game over
    bool entrap() {
        int damage = 5;
        if(searchAccessory("DX")) damage = 1;
        HP -= damage;

        bool ret = HP <= 0;

        if(ret) {
            if(searchAccessory("RE")) {
                removeAccessory("RE");
                ret = false;

                HP = FULL_HP;
                r = start_r;
                c = start_c;
            }
            else {
                game_over_message = "YOU HAVE BEEN KILLED BY SPIKE TRAP..";
            }
        }

        return ret;
    }

    void tryAttachItem(Item* item) {
        switch(item->type) {
            case 'W':
                weapon = dynamic_cast<Weapon*>(item);
                break;
            case 'A':
                armor = dynamic_cast<Armor*>(item);
                break;
            case 'O':
                if(accessories.size() < 4 && !searchAccessory(dynamic_cast<Accessory*>(item)->effect))
                    accessories.push_back(dynamic_cast<Accessory*>(item));
                break;
            default:
                assert(0);
        }
    }

    // return true, if the game over
    bool fight(Monster& monster) {
        if(monster.is_boss && searchAccessory("HU")) HP = FULL_HP;

        bool first_fight = true;
        while(0 < HP && 0 < monster.HP) {
            int player_atk = getATK();
            int player_def = getDEF();
            if(first_fight) {
                if(searchAccessory("CO")) {
                    if(searchAccessory("DX")) player_atk *= 3;
                    else player_atk *= 2;
                }
            }

            assert(player_atk != 0);
            assert(player_def != 0);
            
            monster.HP -= max(1, player_atk - monster.DEF);
            if(monster.HP <= 0) break;

            if(!(first_fight && monster.is_boss && searchAccessory("HU")))
                HP -= max(1, monster.ATK - player_def);
            
            first_fight = false;
        }

        bool is_player_killed = HP <= 0;
        bool is_monster_killed = monster.HP <= 0;

        if(is_monster_killed) {
            if(searchAccessory("HR"))
                HP = min(HP + 3, FULL_HP);
            
            if(searchAccessory("EX"))
                EXP += monster.EXP * 1.2f;
            else
                EXP += monster.EXP;

            if(EXP >= MAX_EXP) {
                LV++;
                FULL_HP += 5;
                HP = FULL_HP;
                ATK += 2;
                DEF += 2;
                EXP = 0;
                MAX_EXP = 5*LV;
            }
        } else if(is_player_killed) {
            if(searchAccessory("RE")) {
                removeAccessory("RE");
                is_player_killed = false;
                is_monster_killed = false;

                HP = FULL_HP;
                monster.HP = monster.FULL_HP;
                r = start_r;
                c = start_c;
            }
        }

        if(is_player_killed) game_over_message = "YOU HAVE BEEN KILLED BY " + monster.name + "..";

        if(monster.is_boss && is_monster_killed) game_over_message = "YOU WIN!";

        return is_player_killed || (monster.is_boss && is_monster_killed);
    }
};

class Board {
public:
    int n, m;
    Player player;
    vector<string> map;
    vector<Monster> monsters;
    vector<ItemBox> boxes;

    Monster& getMonster(int r, int c) {
        for(auto& monster : monsters)
            if(monster.r == r && monster.c == c)
                return monster;
        assert(0);
    }

    ItemBox getItemBox(int r, int c) {
        for(auto box : boxes)
            if(box.r == r && box.c == c)
                return box;
        assert(0);
    }

    ~Board() {
        for(auto box : boxes) {
            delete box.item;
        }
    }
    void enterMap() {
        cin >> n >> m;
        map.resize(n);
        for(int r = 0; r < n; r++)
            for(int c = 0; c < m; c++) {
                char ch; cin >> ch;
                if(ch == '@') {
                    player.start_r = player.r = r;
                    player.start_c = player.c = c;
                    ch = '.';
                }
                map[r].push_back(ch);
            }
    }

    void enterMonster() {
        int count_monster = 0;
        for(const auto& r : map) {
            count_monster += count(r.begin(), r.end(), '&');
            count_monster += count(r.begin(), r.end(), 'M');
        }

        monsters.reserve(count_monster);
        while(count_monster--) {
            assert(count_monster >= 0);
            Monster tmp;
            cin >> tmp.r >> tmp.c >> tmp.name >> tmp.ATK >> tmp.DEF >> tmp.FULL_HP >> tmp.EXP;
            tmp.HP = tmp.FULL_HP;
            tmp.r--; tmp.c--;
            if(map[tmp.r][tmp.c] == 'M') tmp.is_boss = true;
            else tmp.is_boss = false;
            monsters.push_back(tmp);
        }
    }

    void enterItemBox() {
        int count_item_box = 0;
        for(const auto& r : map) {
            count_item_box += count(r.begin(), r.end(), 'B');
        }

        boxes.reserve(count_item_box);
        while(count_item_box--) {
            assert(count_item_box >= 0);
            ItemBox tmp;
            char type;
            cin >> tmp.r >> tmp.c >> type;
            tmp.r--; tmp.c--;

            Item* item;
            if(type == 'O') {
                item = new Accessory;
                cin >> dynamic_cast<Accessory*>(item)->effect;
            } else if(type == 'W') {
                item = new Weapon;
                cin >> dynamic_cast<Weapon*>(item)->ATK;
            } else {
                item = new Armor;
                cin >> dynamic_cast<Armor*>(item)->DEF;
            }
            tmp.item = item;

            boxes.push_back(tmp);
        }
    }

    // return true, if the game stopped
    bool tryMovePlayer(char command) {
        int nr = player.r;
        int nc = player.c;
        if(command == 'L') nc--;
        else if(command == 'R') nc++;
        else if(command == 'U') nr--;
        else if(command == 'D') nr++;
        else assert(0);

        // can't move
        if(nr < 0 || n <= nr || nc < 0 || m <= nc || map[nr][nc] == '#') {
            nr = player.r;
            nc = player.c;
        }

        player.r = nr;
        player.c = nc;
        
        switch(map[nr][nc]) {
            case '.':
            {
            }
            break;
            case 'B':
            {
                auto item_box = getItemBox(nr, nc);
                player.tryAttachItem(item_box.item);
                map[nr][nc] = '.';
            }
            break;
            case '^':
            {
                if(player.entrap())
                    return true;
            }
            break;
            case '&': case 'M':
            {
                auto& monster = getMonster(nr, nc);
                if(player.fight(monster))
                    return true;
                
                if(monster.HP <= 0)
                    map[nr][nc] = '.';
            }
            break;
            default:
            {
                assert(0);
            }
            break;
        }
        return false;
    }
};

Board board;
string commands;

int main() {
    board.enterMap();
    cin >> commands;
    board.enterMonster();
    board.enterItemBox();

    int turn = 0;
    game_over_message = "Press any key to continue.";
    for(auto command : commands) {
        turn++;
        if(board.tryMovePlayer(command))
            break;
    }

    for(int r = 0; r < board.n; r++) {
        for(int c = 0; c < board.m; c++) {
            if(0 < board.player.HP && board.player.r == r && board.player.c == c) cout << '@';
            else cout << board.map[r][c];
        }
        cout << "\n";
    }

    cout << "Passed Turns : " << turn << "\n";

    cout << "LV : " << board.player.LV << "\n";
    cout << "HP : " << max(board.player.HP, 0) << "/" << board.player.FULL_HP << "\n";
    cout << "ATT : " << board.player.ATK << "+" << (board.player.weapon ? board.player.weapon->ATK : 0) << "\n";
    cout << "DEF : " << board.player.DEF << "+" << (board.player.armor ? board.player.armor->DEF : 0) << "\n";
    cout << "EXP : " << board.player.EXP << "/" << board.player.MAX_EXP << "\n";
    cout << game_over_message << "\n";
}