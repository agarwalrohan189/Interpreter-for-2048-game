#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#ifndef _2048_H_
#define _2048_H_

#define N 4

class Tiles
{
private:
    int x;
    vector<string> names;

public:
    Tiles(int x);
    void set_val(int x);
    int get_val();
    void print();
    void add_name(string name);
    vector<string> get_names();
    void delete_names();
    ~Tiles();
};

class Board
{
private:
    Tiles *arr[N][N];

public:
    Board();
    void print();
    void print_stderr();
    void transpose();
    bool move_helper(int dir, int op);
    bool move(int op, int dir);
    bool compare(Board *b);
    bool random_insertion();
    bool check(int i, int j);
    bool set_val(int i, int j, int val, vector<string> names, int print = 0);
    int get_val(int i, int j);
    bool add_name(int i, int j, string name, int print);
    void set_names(int i, int j, vector<string> names);
    void delete_names(int i, int j);
    vector<string> get_names(int i, int j);
    bool print_val(int i, int j);
    ~Board();
};

extern Board *current_board;
extern char interpret;

#endif
