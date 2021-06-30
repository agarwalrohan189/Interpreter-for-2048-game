#include "2048.h"
#include <cstring>
using namespace std;

unordered_map<string, int> name_taken;

Board::Board()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = new Tiles(0);
        }
    }
}

void Board::print()
{
    for (int j = 0; j < 4 * N; j++)
    {
        cout << "----";
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == 0)
                cout << "|";
            arr[i][j]->print();
        }
        cout << endl;
        for (int j = 0; j < 4 * N; j++)
        {
            cout << "----";
        }
        cout << endl;
    }
}

void Board::print_stderr()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fprintf(stderr, "%d ", this->get_val(i, j));
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vector<string> names = this->get_names(i, j);
            if (names.size() == 0)
                continue;
            fprintf(stderr, "%d,%d", i + 1, j + 1);
            int n = names.size();
            for (int i = 0; i < n; i++)
            {
                char s[200];
                int j;
                for (j = 0; j < names[i].length(); j++)
                {
                    s[j] = names[i][j];
                }
                s[j] = '\0';
                if (i == n - 1)
                    fprintf(stderr, "%s ", s);
                else
                    fprintf(stderr, "%s,", s);
            }
        }
    }
    fprintf(stderr, "\n");
}

void Board::transpose()
{
    int temp[N][N];
    vector<string> names[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp[j][i] = this->get_val(i, j);
            names[j][i] = this->get_names(i, j);
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            this->delete_names(i, j);
            this->set_val(i, j, temp[i][j], names[i][j]);
        }
    }
}

bool Board::move_helper(int dir, int op)
{
    bool flag = 0;
    int temp[N][N];
    vector<string> names[N][N];
    memset(temp, 0, sizeof(temp));
    for (int i = 0; i < N; i++)
    {
        int k = (N + dir) % (N + 1);
        for (int j = (N + dir) % (N + 1); (dir == 1) ? j < N : j >= 0; j += dir)
        {
            if (this->get_val(i, j) != 0)
            {
                temp[i][k] = this->get_val(i, j);
                names[i][k] = this->get_names(i, j);
                this->set_val(i, j, 0, {});
                if (k != j)
                    flag = 1;
                k += dir;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = (N + dir) % (N + 1); (dir == 1) ? j < N - 1 : j > 0; j += dir)
        {
            if (temp[i][j] == temp[i][j + dir])
            {
                for (string name : names[i][j + dir])
                {
                    names[i][j].push_back(name);
                }

                names[i][j + dir].clear();

                if (temp[i][j] != 0)
                {
                    flag = 1;
                    switch (op)
                    {
                    case 1: //ADD
                        temp[i][j] *= 2;
                        temp[i][j + dir] = 0;
                        break;

                    case 2: //SUBTRACT
                        if (interpret == 'A')
                        {
                            cout << "A" << endl;
                            temp[i][j] = 0;
                            temp[i][j + dir] = 0;
                            break;
                        }
                        else
                        {
                            temp[i][j] = 0;
                            temp[i][j + dir] = -1;
                            break;
                        }

                    case 3: //MULTIPLY
                        temp[i][j] *= temp[i][j + dir];
                        temp[i][j + dir] = 0;
                        break;

                    case 4: //DIVIDE
                        temp[i][j] = 1;
                        temp[i][j + dir] = 0;
                        break;
                    }
                }
                else
                {
                    temp[i][j] *= 2;
                    temp[i][j + dir] = 0;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        int k = (N + dir) % (N + 1);
        for (int j = (N + dir) % (N + 1); (dir == 1) ? j < N : j >= 0; j += dir)
        {
            if (temp[i][j] == -1)
            {
                this->set_val(i, k, 0, {});
                k += dir;
            }
            else if (temp[i][j] != 0)
            {
                this->set_val(i, k, temp[i][j], names[i][j]);
                k += dir;
            }
        }
    }
    return flag;
}

bool Board::move(int op, int dir)
{
    bool flag = 0;
    string moves[] = {"left", "right", "up", "down"};
    switch (dir)
    {
    case 1: //left
        flag = this->move_helper(1, op);
        break;

    case 2: //right
        flag = this->move_helper(-1, op);
        break;

    case 3: //up
        this->transpose();
        flag = this->move_helper(1, op);
        this->transpose();
        break;

    case 4: //down
        this->transpose();
        flag = this->move_helper(-1, op);
        this->transpose();
        break;

    default:
        cout << "2048> Invalid Move" << endl;
        return 0;
    }
    if (flag)
    {
        cout << "2048> Thanks, " << moves[dir - 1] << " move done, random tile added." << endl;
    }
    else
    {
        cout << "2048> No change in the state. Hence, No random tile added." << endl;
    }
    return flag;
}

bool Board::compare(Board *b)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (arr[i][j]->get_val() != b->get_val(i, j))
                return false;
        }
    }
    return true;
}

bool Board::random_insertion()
{

    vector<pair<int, int>> vacant_indices;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!arr[i][j]->get_val())
                vacant_indices.push_back(make_pair(i, j));
        }
    }

    if (vacant_indices.size() == 0)
        return false;
    int choice = rand() % vacant_indices.size();
    int i = vacant_indices[choice].first;
    int j = vacant_indices[choice].second;
    int val = (rand() % 2 + 1) * 2;
    arr[i][j]->set_val(val);

    return true;
}

bool Board::check(int i, int j)
{
    return i >= 0 && j >= 0 && i < N && j < N;
}

bool Board::set_val(int i, int j, int val, vector<string> names = {}, int print)
{
    if (check(i, j))
    {
        if (val == 0)
        {
            this->delete_names(i, j);
        }
        else
        {
            this->set_names(i, j, names);
        }
        arr[i][j]->set_val(val);
        if (print)
        {
            cout << "2048> Thanks, assignment done." << endl;
        }
        return 1;
    }
    else
    {
        cout << "2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4." << endl;
        return 0;
    }
}

int Board::get_val(int i, int j)
{
    return arr[i][j]->get_val();
}

bool Board::add_name(int i, int j, string name, int print = 0)
{
    if (check(i, j))
    {
        if (print)
        {
            if (name_taken.find(name) != name_taken.end())
            {
                cout << "2048> Name already used. Try some other name." << endl;
            }
            else
            {
                if (!this->get_val(i, j))
                {
                    cout << "2048> No Valued Tile at this position. Try some other tile. " << endl;
                }
                else
                {
                    name_taken[name] = 1;
                    arr[i][j]->add_name(name);
                    cout << "2048> Thanks, naming done." << endl;
                    return 1;
                }
            }
        }
        else
        {
            arr[i][j]->add_name(name);
            return 1;
        }
    }
    else
    {
        if (print)
            cout << "2048> Invalid tile. Try in range 1,2,3,4." << endl;
    }
    return 0;
}

void Board::set_names(int i, int j, vector<string> names)
{
    for (string x : names)
    {
        this->add_name(i, j, x);
    }
}

void Board::delete_names(int i, int j)
{
    vector<string> names = this->get_names(i, j);
    for (string name : names)
    {
        name_taken.erase(name);
    }
    arr[i][j]->delete_names();
}

vector<string> Board::get_names(int i, int j)
{
    return arr[i][j]->get_names();
}

bool Board::print_val(int i, int j)
{
    if (check(i, j))
    {
        if (!this->get_val(i, j))
            cout << "2048> The value at position (" << i + 1 << "," << j + 1 << ") is " << this->get_val(i, j) << " (EMPTY TILE)" << endl;
        else
            cout << "2048> The value at position (" << i + 1 << "," << j + 1 << ") is " << this->get_val(i, j) << endl;
        fprintf(stderr, "%d\n", this->get_val(i, j));
        return 1;
    }
    else
    {
        cout << "2048> Invalid tile position. Try in range 1,2,3,4." << endl;
        fprintf(stderr, "-1\n");
    }
    return 0;
}

Board::~Board()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j]->~Tiles();
        }
    }
}