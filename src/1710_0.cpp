#include <bits/stdc++.h>

using namespace std;

string html;

struct Node {
    string tag;
    string content;
    vector<Node*> children;

    ~Node() {
        for(auto child : children) {
            delete child;
        }
    }
};

Node* parse(string_view partial_html)
{
    bool is_first = true;
    Node* ret;
    stack<Node*> s;

    auto it = partial_html.begin();
    while(it != partial_html.end()) {
        if(*it == '<') {
            if(*(it + 1) == '/') {
                Node* node = s.top();
                if(node->tag == "td" && node->children.empty()) {
                    Node* content = new Node;
                    content->content = "";
                    node->children.push_back(content);
                } else if(node->tag == "table" && node->children.empty()) {
                    node->tag = "";
                    node->content = "";
                }
                s.pop();
                while(*it != '>') it++;
                it++; // pass close bracket
            } else {
                Node* node = new Node;
                it++; // pass open bracket
                while(*it != '>') {
                    node->tag.push_back(*it);
                    it++;
                }
                it++; // pass close bracket
                if(is_first) {
                    ret = node;
                    is_first = false;
                } else {
                    s.top()->children.push_back(node);
                }
                s.push(node);
            }
        } else {
            Node* node = new Node;
            s.top()->children.push_back(node);
            while(*it != '<') {
                node->content.push_back(*it);
                it++;
            }
        }
    }
    return ret;
}

void print_node(Node* node, int depth)
{
    for(int i = 0; i < depth; i++) cout << "--";
    if(node->tag.empty()) cout << node->content << "\n";
    else cout << node->tag << "\n";
    for(auto child : node->children) {
        print_node(child, depth + 1);
    }
}

pair<int, int> cnt_rc(Node* table)
{
    int r = table->children.size();
    assert(table->children.size() != 0);
    int c = table->children[0]->children.size();

    for(auto tr : table->children) {
        for(auto td : tr->children) {
            assert(td->children.size() != 0);
            if(td->children[0]->tag == "table") {
                auto [child_r, child_c] = cnt_rc(td->children[0]);
                r += child_r - 1;
                c += child_c - 1;
            }
        }
    }

    return {r, c};
}

void compute_rcspan(Node* table, vector<vector<tuple<Node*, int, int>>>& sheet, int init)
{
    vector<int> rowspans(table->children.size(), 1);
    assert(table->children.size() != 0);
    vector<int> colspans(table->children[0]->children.size(), 1);

    int cnt_row = table->children.size();
    int cnt_col = table->children[0]->children.size();

    for(int i = 0; i < cnt_row; i++) {
        auto tr = table->children[i];
        for(int j = 0; j < cnt_col; j++) {
            auto td = tr->children[j];
            assert(td->children.size() != 0);
            if(td->children[0]->tag == "table") {
                auto [child_cnt_row, child_cnt_col] = cnt_rc(td->children[0]);
                rowspans[i] = child_cnt_row;
                colspans[j] = child_cnt_col;
            }
        }
    }

    int cur_row = 0;
    for(int i = 0; i < cnt_row; i++) {
        auto tr = table->children[i];
        for(int j = 0; j < cnt_col; j++) {
            auto td = tr->children[j];
            assert(td->children.size() != 0);
            if(td->children[0]->tag == "table") {
                compute_rcspan(td->children[0], sheet, init + cur_row);
            } else {
                sheet[init + cur_row].emplace_back(td, rowspans[i], colspans[j]);
            }
        }
        cur_row += rowspans[i];
    }
}

string generate(Node* table)
{
    assert(table->children.size() != 0);
    string result;

    auto [cnt_row, cnt_col] = cnt_rc(table);
    vector<vector<tuple<Node*, int, int>>> sheet(cnt_row);

    compute_rcspan(table, sheet, 0);

    result += "<table>";
    for(auto tr : sheet) {
        result += "<tr>";
        for(auto [td, rowspan, colspan] : tr) {
            result += "<td";
            if(rowspan > 1) {
                result += " rowspan=\"";
                result += to_string(rowspan);
                result += "\"";
            }
            if(colspan > 1) {
                result += " colspan=\"";
                result += to_string(colspan);
                result += "\"";
            }
            result += ">";
            assert(td->children.size() != 0);
            result += td->children[0]->content;
            result += "</td>";
        }
        result += "</tr>";
    }
    result += "</table>\n";

    return result;
}

int main()
{
    string s;
    do {
        cin >> s;
        html += s;
    } while(s != "</body>");

    Node* body = parse(html);
    // print_node(body, 0);

    string result;
    result += "<body>\n";
    for(auto table : body->children) {
        result += generate(table);
    }
    result += "</body>";
    cout << result;

    delete body;
}