#include <bits/stdc++.h>

using namespace std;

struct Ident;

struct Lexeme {
    const int type;
    const char* literal;
    const Ident* ident;

    Lexeme(const char* _literal) : type(0), literal(_literal), ident(nullptr) {}
    Lexeme(const Ident* _ident) : type(1), literal(nullptr), ident(_ident) {}
};

struct Expression {
    const vector<Lexeme> lexemes;
    Expression(const initializer_list<Lexeme>& _lexemes) : lexemes(_lexemes) {}
};

struct Ident {
    mutable int cnt_appear;
    const vector<Expression> expressions;
    Ident(const initializer_list<Expression>& _expressions) : expressions(_expressions), cnt_appear(0) {}
};

int k;
int idx;
int cnt_taunt;
vector<vector<const char*>> taunts;

Ident adverb({{"conspicuously"}, {"categorically"}, {"positively"}, {"cruelly"}, {"incontrovertibly"}});
Ident adjective({{"silly"}, {"wicked"}, {"sordid"}, {"naughty"}, {"repulsive"}, {"malodorous"}, {"ill-tempered"}});
Ident article({{"a"}});
Ident past_verb({{"was"}, {"personified"}});
Ident present_verb({{"is"}, {"masquerades as"}});
Ident noun({{"hamster"}, {"coconut"}, {"duck"}, {"herring"}, {"newt"}, {"peril"}, {"chicken"}, {"vole"}, {"parrot"}, {"mouse"}, {"twit"}});
Ident past_person({{"mother"}, {"father"}, {"grandmother"}, {"grandfather"}, {"godfather"}});
Ident present_person({{"steed"}, {"king"}, {"first-born"}});
Ident past_rel({{"your", " ", &past_person, " ", &past_verb}});
Ident present_rel({{"your", " ", &present_person, " ", &present_verb}});
Ident modifier({{&adjective}, {&adverb, " ", &adjective}});
Ident modified_noun({{&noun}, {&modifier, " ", &noun}});
Ident noun_phrase({{&article, " ", &modified_noun}});
Ident sentence({{&past_rel, " ", &noun_phrase}, {&present_rel, " ", &noun_phrase}, {&past_rel, " ", &article, " ", &noun}});
Ident taunt({{&sentence}, {&taunt, &sentence}, {&noun, "!"}, {&sentence}});

void build(const Ident* ident)
{
    if(ident == &taunt) {
        cnt_taunt++;
        taunts.push_back(vector<const char *>());
    }
    auto& expression = ident->expressions[ident->cnt_appear % ident->expressions.size()];
    ident->cnt_appear++;
    for(auto& lexeme : expression.lexemes) {
        if(lexeme.type == 0) {
            taunts[idx].push_back(lexeme.literal);
        } else {
            build(lexeme.ident);
        }
    }
    if(ident == &taunt) {
        idx++;
    }
}

bool is_alphabet(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    const char* special_key = "theholygrail";
    int special_key_len = strlen(special_key);

    char str[80];
    while(cin.getline(str, sizeof(str))) {
        int len = strlen(str);
        int tokens_size = 0;
        char* tokens[80] = {nullptr, };
        for(int i = 0; i < len; i++) {
            if(!isspace(str[i])) {
                tokens[tokens_size] = new char[80];
                char* p = tokens[tokens_size];
                while(i < len && !isspace(str[i])) {
                    *(p++) = str[i++];
                }
                *p = '\0';
                tokens_size++;
            }
        }

        cout << "Knight: ";
        for(int i = 0; i < tokens_size; i++) {
            cout << tokens[i];
            cout << ' ';
        }
        cout << '\n';

        int key_last = 0;
        for(char* p = str; *p != '\0'; p++) {
            if(tolower(*p) == special_key[key_last]) {
                key_last++;
                if(key_last == special_key_len) break;
            }
        }

        k = 0;
        cnt_taunt = 0;

        if(key_last == special_key_len) {
            cout << "Taunter: (A childish hand gesture). \n";
            cnt_taunt++;
        }

        int cnt_word = 0;
        for(int i = 0; i < tokens_size; i++) {
            bool is_word = false;
            for(char* p = tokens[i]; *p != '\0'; p++) {
                is_word |= is_alphabet(*p);
            }
            cnt_word += is_word;
        }

        while(cnt_taunt < (cnt_word + 2) / 3) {
            cout << "Taunter: ";
            idx = 0;
            taunts.clear();
            build(&taunt);
            for(int i = 0; i < taunts.size(); i++) {
                for(int j = 0; j < taunts[i].size(); j++) {
                    if(j == 0) {
                        cout << (char)toupper(taunts[i][j][0]);
                        cout << &taunts[i][j][1];
                    } else {
                        // if(taunts[i][j][0] != '!') cout << " ";
                        cout << taunts[i][j];
                    }
                }
                if(i < taunts.size() - 1) cout << ' ';
            }
            cout << ". \n";
        }
        cout << '\n';

        for(int i = 0; i < tokens_size; i++) {
            delete tokens[i];
        }
    }
}