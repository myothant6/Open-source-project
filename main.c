#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int board_x = 5;
int board_y = 6;
char symbols[4] = {'#', '@', '$', '%'};
//                  a    b    c    d

char board[5][6] = {
    {'|', '|', '|', '|', '|', '|'},
    {'|', '|', '|', '|', '|', '|'},
    {'|', '|', '|', '|', '|', '|'},
    {'|', '|', '|', '|', '|', '|'},
    {'|', '|', '|', '|', '|', '|'}
};

void print_board()
{
    system("clear");
    for (int y = board_y - 1; y >= 0; y--)
    {
        for (int x = 0; x < board_x; x++)
        {
            printf(" %c ", board[x][y]);
        }
        printf("\n");
    }
    printf("---------------\n 1  2  3  4  5 \n");
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

int move()
{
    int pick_position, drop_position;
    
    printf("Pick (1-5): ");
    scanf("%d", &pick_position);
    
    if (pick_position == 100) {
        return 100;
    }
    
    if (pick_position < 0 || pick_position > 5)
    {
        return 0;
    }
    else
    {
        printf("Drop (1-5): ");
        scanf("%d", &drop_position);
        
        if (drop_position < 0 || drop_position > 5)
        {
            return 0;
        }
        else
        {
            pick_position--;
            drop_position--;
            
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
    }
    
    return 0;
}

bool win()
{
    int a, b, c, d, score;
    
    score = 0;
    for (int x = 0; x < board_x; x++)
    {
        /*char symbolA = symbols[0];
        char symbolB = symbols[1];
        char symbolC = symbols[2];
        char symbolD = symbols[3];*/
        
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
    init_position();
    
    int r;
    
    while (true)
    {
        print_board();
        r = move();
        
        if (r == 100)
        {
            break;
        }
        
        if (win())
        {
            print_board();
            printf("You win! :)\n");
            break;
        }
    }
    
    return 0;
}