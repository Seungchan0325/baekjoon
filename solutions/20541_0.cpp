#include <bits/stdc++.h>

using namespace std;

struct node {
    const string name;
    const node* parent;
    mutable set<string> photos;
    mutable set<node> albums;

    node(const string& _name, const node* _parent) : name(_name), parent(_parent) {}

    bool operator < (const node& other) const
    {
        return name < other.name;
    }

    int count_albums_recursive() const
    {
        int ret = albums.size();
        for(auto& next : albums) {
            ret += next.count_albums_recursive();
        }
        return ret;
    }

    int count_photos_recursive() const
    {
        int ret = photos.size();
        for(auto& next : albums) {
            ret += next.count_photos_recursive();
        }
        return ret;
    }
};

node root_album("album", &root_album);
const node* cur = &root_album;

void mkalb(string s)
{
    if(cur->albums.find(node(s, nullptr)) != cur->albums.end()) {
        cout << "duplicated album name\n";
        return;
    }

    cur->albums.insert(node(s, cur));
}

void rmalb(string s)
{
    int removed_albums = 0;
    int removed_photos = 0;

    if(s == "-1") {
        if(!cur->albums.empty()) {
            auto it = cur->albums.begin();
            removed_albums = it->count_albums_recursive() + 1;
            removed_photos = it->count_photos_recursive();
            cur->albums.erase(it);
        }
    } else if(s == "0") {
        removed_albums = cur->count_albums_recursive();
        removed_photos = cur->count_photos_recursive() - cur->photos.size();
        cur->albums = set<node>();
    } else if(s == "1") {
        if(!cur->albums.empty()) {
            auto it = --cur->albums.end();
            removed_albums = it->count_albums_recursive() + 1;
            removed_photos = it->count_photos_recursive();
            cur->albums.erase(it);
        }
    } else {
        auto it = cur->albums.find(node(s, nullptr));
        if(it != cur->albums.end()) {
            removed_albums = it->count_albums_recursive() + 1;
            removed_photos = it->count_photos_recursive();
            cur->albums.erase(it);
        }
    }

    cout << removed_albums << " " << removed_photos << "\n";
}

void insert(string s)
{
    if(cur->photos.find(s) != cur->photos.end()) {
        cout << "duplicated photo name\n";
        return;
    }

    cur->photos.insert(s);
}

void Delete(string s)
{
    int removed_photos = 0;

    if(s == "-1") {
        if(!cur->photos.empty()) {
            removed_photos = 1;
            cur->photos.erase(cur->photos.begin());
        }
    } else if(s == "0") {
        removed_photos = cur->photos.size();
        cur->photos = set<string>();
    } else if(s == "1") {
        if(!cur->photos.empty()) {
            removed_photos = 1;
            cur->photos.erase(--cur->photos.end());
        }
    } else {
        auto it = cur->photos.find(s);
        if(it != cur->photos.end()) {
            removed_photos = 1;
            cur->photos.erase(it);
        }
    }

    cout << removed_photos << "\n";
}

void ca(string s)
{
    if(s == "..") {
        cur = cur->parent;
    } else if(s == "/") {
        cur = &root_album;
    } else {
        auto it = cur->albums.find(node(s, nullptr));

        if(it != cur->albums.end()) {
            cur = &(*it);
        }
    }

    cout << cur->name << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    while(n--) {
        string op, s;
        cin >> op >> s;

        if(op == "mkalb") mkalb(s);
        else if(op == "rmalb") rmalb(s);
        else if(op == "insert") insert(s);
        else if(op == "delete") Delete(s);
        else if(op == "ca") ca(s);
        else assert(0);
    }
}