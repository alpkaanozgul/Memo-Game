// Alp Kaan Özgül 2638096


#include <stdio.h>
#include<stdlib.h>
#include <time.h>


int boardsize();    // done
int** initializeBoard(int size); //done
int displayBoard(int sizedisplay,int cor1x,int cor1y,int cor2x,int cor2y,int** boardcord,int check,int whichplayer,int* condition,int* pointplayer1,int* pointplayer2,int* finishcount);
int displayBoard2(int sizedisplay);
int reusecheck(int* count,int cor1x,int cor1y,int cor2x,int cor2y,int** ptr,int* condition);
int checkCharacters(int cor1x,int cor1y,int cor2x,int cor2y,int** boardcord,int size,int* pointplayer1,int* pointplayer2,int whichplayer,int* condition);
int getCoordinates(int* Pcount,int size,int* x1,int* x2,int* y1,int* y2);

int main() {
    int sizeofboard;
    int x1=0,x2=0,y1=0,y2=0;
    int x1a,x2a,y1a,y2a;
    int a;
    int ba=1;
    int count=0,same=10;
    int countsend;                                                    //here is the variables defined for main function i created them horixantally to see easier
    int Pcount=0;
    int* ptr=0;
    int choise=0;
    int check;
    int pointplayer1=0,pointplayer2=0;
    int whichplayer;
    int playcount=1;
    int condition=0;
    int finishcount=1;
    char decision='Y';



    while(decision == 'Y') {
        printf("Welcome to MemoME!\n");
        sizeofboard = boardsize();
        printf("A Board is created for you with the size of %dx%d\n", sizeofboard, sizeofboard);

        int **boardcord = initializeBoard(
                sizeofboard);           //here i initialized the board with 2d array and stored it to double pointer to future access
        displayBoard2(sizeofboard);


        while (finishcount * 2 != sizeofboard *
                                  sizeofboard) {    //i found the logic that if this condition is met every character is oppened it can bee seen clearly as program progresses

            if (playcount % 2 == 0) {
                whichplayer = 1;                  // in these if else if conditiones i checked which player's turn it is
            } else if (playcount % 2 != 0) {
                whichplayer = 2;
            }
            getCoordinates(&Pcount, sizeofboard, &x1, &x2, &y1, &y2);
            //function calls (detailed description in the function itself)
            same = reusecheck(&Pcount, x1, y1, x2, y2, &ptr, &condition);

            while (same == 1 || same == 2) {
                if (same == 1) {
                    printf("(%d,%d) already opened!\n", x1, y1);
                    printf("\nEnter the coordinates of doors to open:\n");          // in the reuse function if a coordinate used before it brings here and asks user to input again
                    fflush(stdin);
                    scanf("(%d,%d) (%d,%d)", &x1, &y1, &x2, &y2);

                    same = 10;

                }
                if (same == 2) {
                    printf("(%d,%d) already opened!\n", x2, y2);
                    printf("Enter the coordinates of doors to open:\n");
                    fflush(stdin);
                    scanf("(%d,%d) (%d,%d)", &x1, &y1, &x2, &y2);
                    same = 10;

                }
            }

            check = checkCharacters(x1, y1, x2, y2, boardcord, sizeofboard, &pointplayer1, &pointplayer2, whichplayer,
                                    &condition);
            displayBoard(sizeofboard, x1, y1, x2, y2, boardcord, check, whichplayer, &condition, &pointplayer1,
                         &pointplayer2, &finishcount);  //function calls

            playcount = playcount + 1;


        }

        if (pointplayer1 < pointplayer2) {
            printf("***Winner is Player 1!***\n");
        }                                                       //decideds who is the winner
        else if (pointplayer2 < pointplayer1) {
            printf("***Winner is Player 2!***\n");
        }

        printf("Would you like to play again (Y/N)? \n");
        scanf("%c",&decision);

    }

    return 0;
}

int boardsize()
{
    int boardsize;
    printf("Please specify the board size (2-30):\n ");
    scanf("%d",&boardsize);
    while((boardsize>30 || boardsize<2) || (boardsize%2!=0) )
    {
        if(boardsize>30 || boardsize<2) {
            printf("Board size can only be between 2-30!\n");
            printf("Please specify the board size (2-30):\n");
            scanf("%d", &boardsize);
        }                                                                               //evaluates board size and creates acordingly
        else if(boardsize%2!=0)
        {
            printf("Board size can only be a multiple of two!\n");
            printf("Please specify the board size (2-30):\n");
            scanf("%d", &boardsize);

        }
    }
    return boardsize;

}

int** initializeBoard(int size) {
    int** arr2d;
    arr2d = (int**)malloc(size * sizeof(int*));
    if (arr2d == NULL) {
        printf("Error");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        arr2d[i] = (int*)malloc(size * sizeof(int));
    }

    srand(time(0));

                                                                // here i fill the array with random values
    for (int i = 0; i < size; i++) {
                                                        // here i initialized a temporary array to hold all possible values
        char temp[size];
        for (int j = 0; j < size; j++) {
            temp[j] = 33 + j;                                       // i fill the temporary array with ASCII values
        }

                                                                // Randomly shuffle the temporary array
        for (int j = size - 1; j > 0; j--) {
            int index = rand() % (j + 1);
            char tempValue = temp[index];
            temp[index] = temp[j];
            temp[j] = tempValue;
        }

                                                            // Copy the shuffled values to the current row of the 2D array
        for (int j = 0; j < size; j++) {
            arr2d[i][j] = temp[j];
        }
    }



    return arr2d;
}


int displayBoard(int sizedisplay,int cor1x,int cor1y,int cor2x,int cor2y,int** boardcord,int check,int whichplayer,int* condition,int* pointplayer1,int* pointplayer2,int* finishcount)
{

        int displayarray[sizedisplay][sizedisplay];

        for (int i = 0; i < sizedisplay; i++) {
            for (int j = 0; j < sizedisplay; j++) {
                displayarray[i][j] = 64;
            }                                                                                           //here it shows the symbol that corresponds to input that goes to 2d array
        }
        displayarray[cor1x-1][cor1y-1] = boardcord[cor1x -1][cor1y - 1];
        displayarray[cor2x-1][cor2y-1] = boardcord[cor2x - 1][cor2y - 1];

        for (int k = 0; k < sizedisplay; k++) {
            for (int u = 0; u < sizedisplay; u++) {
                printf("%c       ", displayarray[k][u]);
            }
            printf("\n");
        }

    if(*condition==1)
    {
        printf("\nLucky you! Your score: 2, total score: %d\n",*pointplayer1);
        *finishcount=*finishcount+1;
    }
    else if(*condition==2)                                                                      //in these if else if statements i print the messages and gather the information on when to finish the game
    {
        printf("\nUnlucky! Your score: -1, total score: %d\n",*pointplayer1);
    }
    else if(*condition==3)
    {
        printf("\nLucky you! Your score: 2, total score: %d\n",*pointplayer2);
        *finishcount=*finishcount+1;
    }
    else if(*condition==4)
    {
        printf("\nUnlucky! Your score: -1, total score: %d\n",*pointplayer2);
    }

    printf("--Player %d Turn:--\n\n",whichplayer);




}

int displayBoard2 (int sizedisplay)
{
    int displayarray[sizedisplay][sizedisplay];
    printf("--Player 1 Turn:--\n\n");
    for (int i = 0; i < sizedisplay; i++) {
        for (int j = 0; j < sizedisplay; j++) {
            displayarray[i][j] = 64;                            //in the beginning it is used to display clossed table
        }
    }
    for (int k = 0; k < sizedisplay; k++) {
        for (int u = 0; u < sizedisplay; u++) {
            printf("%c       ", displayarray[k][u]);
        }
        printf("\n");
    }
}

int checkCharacters(int cor1x,int cor1y,int cor2x,int cor2y,int** boardcord,int size,int* pointplayer1,int* pointplayer2,int whichplayer,int* condition)
{


    if(whichplayer==1)
    {                                                                                                           //in here i check the inputted coordinates are same or not if same some variables change and it is sent to main to be proccesed further
        if ((boardcord[cor1x-1][cor1y-1]) == (boardcord[cor2x-1][cor2y-1]))
        {
            *pointplayer1= *pointplayer1+2;
            *condition=1;
        }
        else if ((boardcord[cor1x-1][cor1y-1]) != (boardcord[cor2x-1][cor2y-1]))
        {
            *pointplayer1 = *pointplayer1-1;
            *condition=2;
        }
    }
    else if(whichplayer==2)
    {
        if ((boardcord[cor1x-1][cor1y-1]) == (boardcord[cor2x-1][cor2y-1]))
        {
            *pointplayer2= *pointplayer2+2;
            *condition =3;
        }
        else if ((boardcord[cor1x-1][cor1y-1]) != (boardcord[cor2x-1][cor2y-1]))
        {
            *pointplayer2 = *pointplayer2-1;
            *condition =4;
        }
    }





}

int getCoordinates(int* Pcount,int size,int* x1,int* x2,int* y1,int* y2)
{
        int cor1x = 0, cor1y = 0, cor2x = 0, cor2y = 0, same;           //here in this function i get the input coordinates and evaluate if it is valid or not
        printf("Enter the coordinates of doors to open:\n");
        fflush(stdin);
        scanf("(%d,%d) (%d,%d)", &cor1x, &cor1y, &cor2x, &cor2y);

        while (cor1x > size || cor1y > size || cor2x > size || cor2y > size || (cor1x == cor2x && cor1y == cor2y)) {
            if ((cor1x > size && cor1y > size) || (cor2x > size && cor2y > size)) {
                printf("Sorry, wrong coordinates!\n");
                printf("Enter the coordinates of doors to open:\n");
                fflush(stdin);
                scanf("(%d,%d) (%d,%d)", &cor1x, &cor1y, &cor2x, &cor2y);
            } else if (cor1x == cor2x && cor1y == cor2y) {
                printf("Sorry, two door coordinates are same!\n");
                printf("Enter the coordinates of doors to open:\n");
                fflush(stdin);
                scanf("(%d,%d) (%d,%d)", &cor1x, &cor1y, &cor2x, &cor2y);
            }


        }
        *Pcount = *Pcount + 4;
        *x1 = cor1x;
        *y1 = cor1y;
        *x2 = cor2x;
        *y2 = cor2y;

    return *Pcount;
}



int reusecheck(int* county, int cor1x, int cor1y, int cor2x, int cor2y, int** ptr,int* condition) {
    int count = *county;
    int used1 = 1, used2 = 2, pass = 10;

    if (count == 4) {
        *ptr = (int*)malloc(4 * sizeof(int));
                                                                    //in this function as new oppened coordinates assigned i reserve new sapces for every individual value
        (*ptr)[0] = cor1x;
        (*ptr)[1] = cor1y;
        (*ptr)[2] = cor2x;
        (*ptr)[3] = cor2y;
    }
    else if (count > 4 && (*condition==1 || *condition==3)) {
        int* newPtr = (int*)realloc(*ptr, count * sizeof(int));
        if (newPtr) {
            *ptr = newPtr;
            int j = count - 4;
            (*ptr)[j] = cor1x;
            (*ptr)[j + 1] = cor1y;
            (*ptr)[j + 2] = cor2x;
            (*ptr)[j + 3] = cor2y;
        }
        else {
            // Error handling for realloc failure
            free(*ptr);
            exit(0);

        }
    }

    if (count > 4) {
        for (int a = 0; a < count - 4; a += 4) {
            if (((*ptr)[a] == cor1x) && ((*ptr)[a + 1] == cor1y)) {
                printf("1x.[%d] 1y.[%d]\n", (*ptr)[a], (*ptr)[a + 1]);
                free(*ptr);
                return used1;
            }
            else if (((*ptr)[a + 2] == cor2x) && ((*ptr)[a + 3] == cor2y)) {
                printf("2x.[%d] 2y.[%d]\n", (*ptr)[a + 2], (*ptr)[a + 3]);
                free(*ptr);
                return used2;
            }
        }
    }



    return pass;
}






