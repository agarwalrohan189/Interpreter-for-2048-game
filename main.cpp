#include "2048.h"
#include "parse.tab.h"
using namespace std;

Board *current_board = new Board();
char interpret;

int main()
{
    cout << "2048> Hi, I am the 2048-game Engine." << endl;
    cout << "2048> The start state is:" << endl;
    current_board->random_insertion();
    current_board->print();
    current_board->print_stderr();
    cout << "What Interpretation Should this game follow?" << endl;
    cout << "Enter A or B based on the following description:-" << endl;
    cout << "\"SUBTRACT LEFT\" ON [4,2,2,4] can generate:" << endl;
    cout << "    A->[4,4,0,0]     B->[4,0,4,0] " << endl;
    scanf(" %c", &interpret);
    while (interpret != 'A' && interpret != 'B')
    {
        cout << "Invalid input! Enter a valid option." << endl;
        scanf(" %c", &interpret);
    }
    char extraEOL;
    scanf("%c", &extraEOL);
    srand(time(NULL));
    int x = 1;
    do
    {
        if (x == 0)
        {
            cout << "2048> The current state is:" << endl;
            current_board->print();
            current_board->print_stderr();
        }
        if (x == -2)
        {
            current_board->print_stderr();
        }
        cout << "2048> Please type a command." << endl;
        x = 1;
        while (x > 0)
        {
            cout << "----> ";
            x = yyparse();
            if (x == 1)
            {
                fprintf(stderr, "%d\n", -1);
            }
        }
    } while (!feof(stdin));

    cout << endl
         << "2048> THE END" << endl;

    return 0;
}
