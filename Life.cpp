#include<iostream>
#include<unistd.h>
using namespace std;
//size of grid
const int n = 30;

//prints grid
void print(char grid[n][n])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}

//initial input of live/dead cells
void initialise(char grid[n][n])
{
    //initialise the grid with full dead cells
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            grid[i][j] = '.';
        }
    }
    print(grid);
    //put in some live cells
    char ans;
    int row, col;
    do
    {
        cout<<endl<<"Where would you like to place your live cells?"<<endl;
        cin>>row>>col;
        row--;
        col--;
        //if that's a valid grid point
        if((row >= 0 && row < n) && (col >= 0 && col < n))
        {
            //user enters first row/column as 1, convert to 0 because C++
            grid[row][col] = 'o';
            cout<<endl;
        }
        //if that's an invalid grid point
        else
            cout<<endl<<"That's not a valid point!"<<endl;
        print(grid);
        cout<<endl<<"More? ";
        cin>>ans;
    }while(ans == 'y');
}

//evolve cells of grid
void update(char grid[n][n], char newgrid[n][n])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            //does the live cell live?
            if(grid[i][j] == 'o')
            {
                int liveneictr = 0;
                //check number of live neighbours
                for(int c = -1; c <= 1; c++)
                {
                    for(int d = -1; d <= 1; d++)
                    {
                        if(c != 0 || d != 0)
                        {
                            if(grid[i+c][j+d] == 'o')
                                liveneictr++;
                        }
                    }
                }
                //does the live cell die?
                if(liveneictr < 2)
                    newgrid[i][j] = '.';
                else if(liveneictr > 3)
                    newgrid[i][j] = '.';
                //otherwise, the live cell lives!
                else newgrid[i][j] = 'o';
                cout<<endl;
            }
            //does the dead cell live?
            else if(grid[i][j] == '.')
            {
                int deadneictr = 0;
                //check number of live neighbours
                for(int c = -1; c <= 1; c++)
                {
                    for(int d = -1; d <= 1; d++)
                    {
                        if(c != 0 || d != 0)
                        {
                            if(grid[i+c][j+d] == 'o')
                                deadneictr++;
                        }
                    }
                }
                //the dead cell comes to life!
                if(deadneictr == 3)
                    newgrid[i][j] = 'o';
            }
        }
    }
}

//outputs 1 if the grid is empty, so we don't need to keep going
int isgridempty(char grid[n][n])
{
    int emptyctr = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(grid[i][j] != '.')
                emptyctr++;
        }
    }
    if(emptyctr == 0)
        return 1;
    else
        return 0;
}

int main()
{
    cout<<endl;
    
    //original grid
    char grid[n][n];
    //new grid after evolution
    char newgrid[n][n];
    
    //print blank grid
    initialise(grid);
    print(grid);
    
    //set the updated grid to blank
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            newgrid[i][j] = '.';
        }
    }
    
    //do the evolution as many times as the user wants
    cout<<endl<<"All right! Let the Game of Life begin..."<<endl;
    //char choice;
    do
    {
        //cout<<endl<<"Evolve..."<<endl;
        update(grid, newgrid);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                grid[i][j] = newgrid[i][j];
            }
        }
        
        //outputs some white space
        cout<<string(20, '\n');
        print(grid);
        
        //freezes screen for 1 sec
        usleep(1000000);
        
        //cout<<endl<<"Again?"<<endl;
        //cin>>choice;
        //}while(choice == 'y');
        
    }while(isgridempty(grid) == 0);
    
    return 0;
}
