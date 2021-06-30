#include "2048.h"
using namespace std;
#define N 4
#define ull unsigned long long

Tiles::Tiles(int x)
{
    this->x = x;
    this->names.clear();
}
void Tiles::set_val(int x)
{
    this->x = x;
}
int Tiles::get_val()
{
    return this->x;
}
void Tiles::print()
{
    if (!this->x)
        cout << "\t"
             << " "
             << "\t|";
    else
        cout << "\t" << x << "\t|";
}

void Tiles::add_name(string name)
{
    this->names.push_back(name);
}

vector<string> Tiles::get_names()
{
    return this->names;
}

void Tiles::delete_names()
{
    this->names.clear();
}

Tiles::~Tiles()
{
    names.clear();
}