#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

int board_x = 5;
int board_y = 6;
int menu_select = 0;
int menu[5] = {1, 2, 3, 4, 5};
char board[5][6];// a    b    c    d
char symbols[4] = {'@', '#', '$', '%'};
bool number_picked = false;

void board_create()
{
    for (int x = 0; x < board_x; x++)
    {
        for (int y = 0; y < board_y; y++)
        {
            board[x][y] = '|';
        }
    }
}

void print_board()
{
    clear();
    
    for (int y = board_y - 1; y >= 0; y--)
    {
        for (int x = 0; x < board_x; x++)
        {
            if (board[x][y] == symbols[0])
            {
                attron(COLOR_PAIR(1));
                printw(" %c ", board[x][y]);
                attroff(COLOR_PAIR(1));
            }
            else if (board[x][y] == symbols[1])
            {
                attron(COLOR_PAIR(2));
                printw(" %c ", board[x][y]);
                attroff(COLOR_PAIR(2));
            }
            else if (board[x][y] == symbols[2])
            {
                attron(COLOR_PAIR(3));
                printw(" %c ", board[x][y]);
                attroff(COLOR_PAIR(3));
            }
            else if (board[x][y] == symbols[3])
            {
                attron(COLOR_PAIR(4));
                printw(" %c ", board[x][y]);
                attroff(COLOR_PAIR(4));
            }
            else
            {
                printw(" %c ", board[x][y]);
            }
        }
        printw("\n");
    }
    printw("***************\n");
    
    // print menu
    for (int i = 0; i < 5; i++)
    {
        if (i == menu_select)
        {
            attron(A_REVERSE);
            printw(" %d ", menu[i]);
            attroff(A_REVERSE);
        }
        else
        {
            printw(" %d ", menu[i]);
        }
    }
    
    printw("\n");
    (number_picked) ? printw("Enter to Drop\n") : printw("Enter to Pick");
    
    refresh();
}

void init_position()
{
    int y, random_number, a, b, c, d;
    a = b = c = d = 6;
    for (int x = 1; x < board_x; x++)
    {
        y = 0;
        
        while (y < board_y)
        {
            random_number = rand() % 4;
            
            switch (random_number)
            {
                case 0: // #
                    if (a > 0)
                    {
                        board[x][y] = symbols[0];
                        a--;
                        y++;
                    }
                    break;
                case 1: // @
                    if (b > 0)
                    {
                        board[x][y] = symbols[1];
                        b--;
                        y++;
                    }
                    break;
                case 2: // $
                    if (c > 0)
                    {
                        board[x][y] = symbols[2];
                        c--;
                        y++;
                    }
                    break;
                case 3: // %
                    if (d > 0)
                    {
                        board[x][y] = symbols[3];
                        d--;
                        y++;
                    }
                    break;
            }
        }
    }
}

void player_move(int a, int b)
{
    int pick_position = a;
    int drop_position = b;
    
    // check => drop => true => pick
    for (int i = 0; i < board_y; i++)
    {
        if (board[drop_position][i] == '|')
        {
            // pick
            bool found = false;
            char picking;
            for (int y = board_y - 1; y >= 0; y--)
            {
                if (board[pick_position][y] != '|')
                {
                    picking = board[pick_position][y];
                    board[pick_position][y] = '|';
                    found = true;
                    break;
                }
            }
            
            if (found)
            {
                // drop
                for (int y = 0; y < board_y; y++)
                {
                    if (board[drop_position][y] == '|')
                    {
                        board[drop_position][y] = picking;
                        break;
                    }
                }
            }
            
            break;
        }
    }
}

bool win()
{
    int a, b, c, d, score;
    
    score = 0;
    for (int x = 0; x < board_x; x++)
    {
        a = b = c = d = 0;
        for (int y = 0; y < board_y; y++)
        {
            if (board[x][y] == symbols[0])
            {
                a++;
            }
            else if (board[x][y] == symbols[1])
            {
                b++;
            }
            else if (board[x][y] == symbols[2])
            {
                c++;
            }
            else if (board[x][y] == symbols[3])
            {
                d++;
            }
            
        }
        
        if (a == 6 || b == 6 || c == 6 || d == 6)
        {
            score++;
        }
        
    }
    
    if (score == 4)
    {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    srand(time(NULL));
    board_create();
    init_position();
    
    initscr();
    start_color();
    use_default_colors();
    curs_set(0);
    noecho();
    
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    
    int pick_number, drop_number;
    while (true)
    {
        print_board();
        
        int ch = getch();
        if (ch == 'q')
        {
            break;
        }
        else if (ch == 'd')
        {
            menu_select = (menu_select + 1) % 5;
        }
        else if (ch == 'a')
        {
            menu_select = (menu_select - 1 + 5) % 5;
        }
        else if (ch == 10)
        {
            if (number_picked)
            {
                drop_number = menu_select;
                number_picked = false;
                player_move(pick_number, drop_number);
            }
            else
            {
                pick_number = menu_select;
                number_picked = true;
            }
        }
        
        if (win())
        {
            print_board();
            printw("\nYou win! :)");
            refresh();
            getch();
            break;
        }
    }
    
    endwin();
    return 0;
}
