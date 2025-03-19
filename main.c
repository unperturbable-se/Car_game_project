#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  
#include <windows.h> 

#define TrackWidth 75    
#define TrackHeight 15  //storage
#define ViewHeight 15 //display    
#define DELAY 0
#define MaxLeaderboard 50 // Maximum number of leaderboard entries
#define acceleration 2.1
#define HIDE_CURSOR printf("\e[?25l")  
#define CAR "~#!#~"
#define OBSTACLE "~X~"  

struct LeaderboardEntry
{
    int score;
    char nickname[50];
};

// Functions
void showMenu();
void playGame();
void showRules();
void showLeaderboard();
void initializeTrack(char track[TrackHeight][TrackWidth]);
void printTrack(char track[TrackHeight][TrackWidth], int carPosX, int carPosY, int viewStart);
int checkCollision(char track[TrackHeight][TrackWidth], int carPosX, int carPosY);
void setTextColor(int color);
void saveScore(int score);
void loadLeaderboard(struct LeaderboardEntry leaderboard[], int *numEntries);
void sortLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries);
void displayLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries);
void delay(int milliseconds);
void titleScreen();
void backStory();


int main()
{ 
    HIDE_CURSOR;
    backStory();
    titleScreen();
    int choice;
    while(1)
    {
        showMenu(); 
        printf("Enter choice: ");
        
        while (!_kbhit()) {};
        choice = _getch();

        if(choice <= '1' && choice >= '4')
		{
            ;
            continue;  
        }
        system("cls");
        switch(choice)
        {
        case '1':
            playGame();
            break;
        case '2':
            showRules();
            break;
        case '3':
            showLeaderboard();
            break;
        case '4':
            printf("Thanks for playing!\n");
            setTextColor(3);
        printf("\n       .-\"\"\"\"\"\"-.\n");
        printf("      /          \\\n");
        printf("     /            \\\n");
        printf("    |              |\n");
        printf("    |,  .-.  .-.  ,|\n");
        printf("    | )(_o/  \\o_)( |\n");
        printf("    |/     /\\     \\|\n");
        printf("    (_     ^^     _)\n");
        printf("     \\__|IIIIII|__/\n");
        printf("      | \\IIIIII/ |\n");
        printf("      \\          /\n");
        printf("       `--------`\n");
        setTextColor(7);
        return 0;
        default:
            printf("Invalid choice try again\n");
        }
        printf("\nPRESS ANY KEY TO CONTINUE...");
        _getch();
        system("cls");
    }
    return 0;
}

void backStory()
{
 system("color 5");    
 printf("\n\n===BACKSTORY===\n\n");

    printf("In the year 2154, Earth has made significant advancements in space travel and colonization.\n");
    printf("Humankind has established thriving colonies on Mars, the Moon, and beyond. However, these advancements\n");
    printf("have attracted the attention of a malevolent alien race known as the **Zylox**, a technologically advanced\n");
    printf("species that has set its sights on Earth for conquest.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");
 printf("=== BACKSTORY===\n\n");   
    printf("Unbeknownst to humanity, the Zylox have secretly infiltrated Earth, preparing for their invasion.\n");
    printf("Their first wave of attack comes unexpectedly in the form of mysterious, high-tech ships that begin appearing\n");
    printf("across the globe. The Zylox want to destabilize Earth, subdue its population, and harvest its resources.\n");
    printf("Their ships are equipped with sophisticated weaponry and cloaking devices, making them nearly impossible to detect.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");
 printf("=== BACKSTORY===\n\n");   
    printf("The world is in chaos. Cities are evacuated, governments scramble to mount a defense, and panic spreads.\n");
    printf("Amidst the chaos, a lone survivor, **Alex Cruz**, finds himself behind the wheel of an experimental car—an\n");
    printf("advanced, AI-powered vehicle designed for high-speed travel and exploration.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");
 printf("=== BACKSTORY===\n\n");   
    printf("The car, code-named **\"Vanguard\"**, was initially developed for exploration on hostile planetary surfaces,\n");
    printf("but now it becomes humanity's best hope. With no time to waste and no way to stop the alien invasion,\n");
    printf("Alex has to race through dangerous, alien-infested roads, dodging obstacles, and evading attacks from Zylox\n");
    printf("drones and spacecraft.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");  
    setTextColor(7);  
}
void titleScreen()
{
 setTextColor(1);
    printf(" #####             ###              ###              #             ####      ######   \n");
    printf(" #                 #   #            #   #           # #           #   #      #        \n");
    printf(" #                 #                #              #   #          #   #      #        \n");
    printf(" ####               ###             #              #   #          ####       #####    \n");
    printf(" #                     #            #              #####          #          #        \n");
    printf(" #                 #   #            #   #          #   #          #          #        \n");
    printf(" #####              ###              ###           #   #          #          ######   \n");
  
    setTextColor(3);
    printf("       .-\"\"\"\"\"\"-.\n");
    printf("      /          \\\n");
    printf("     /            \\\n");
    printf("    |              |\n");
    printf("    |,  .-.  .-.  ,|\n");
    printf("    | )(_o/  \\o_)( |\n");
    printf("    |/     /\\     \\|\n");
    printf("    (_     ^^     _)\n");
    printf("     \\__|IIIIII|__/\n");
    printf("      | \\IIIIII/ |\n");
    printf("      \\          /\n");
    printf("       `--------`\n");
printf("ESCAPE THE ALIENS\n\n");   
setTextColor(7); 
printf("<<<PRESS ANY KEY TO CONTINUE>>>"); 
_getch();
system("cls");   
}
void showMenu()
{
	setTextColor(5);
    printf("--------------------\nMenu:\n--------------------\n");
    printf("1. Play\n--------------------\n");
    printf("2. Rules\n--------------------\n");
    printf("3. Leaderboard\n--------------------\n");
    printf("4. Quit\n--------------------\n\n\n\n");
    setTextColor(7);
}

void showRules()
{
	setTextColor(5);
    printf("\nGame Rules:\n");
    printf("1. Use 'a' or 'A' to swerve the car left.\n");
    printf("2. Use 'd' or 'D' to swerve the car right.\n");
    printf("4. Avoid Aliens (~X~). If the car crashes into an Alien, the game is over.\n");
    printf("5. Survive for as long as possible!\n\n");
    printf("6.If you horizontally attack an alien, the alien will be eliminated\n\n");
    
    setTextColor(7);
}

void showLeaderboard()
{
    struct LeaderboardEntry leaderboard[MaxLeaderboard];
    int numEntries = 0;

    loadLeaderboard(leaderboard, &numEntries);
    sortLeaderboard(leaderboard, numEntries);
    displayLeaderboard(leaderboard, numEntries);
}
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    int start = clock();
    int stop  = clock();
    while( (stop-start) < pause ){stop = clock();};
}
void playGame()
{
    char track[TrackHeight][TrackWidth];
    int carPosX = TrackWidth / 2; // Start in the middle
    int carPosY = TrackHeight - 1; // Bottom row
    int gameOver = 0;
    int score = 0;
    int viewStart = 0; // Starting row for visible track
    int input;
    int i, j;  

    srand(time(0));
    initializeTrack(track);
    
    
    int delayed_time=DELAY;
    printf("\033[%dm", 47); //white background
    while (!gameOver)
    {
          
        printTrack(track, carPosX, carPosY, viewStart);
        if (checkCollision(track, carPosX, carPosY))
        {
            system("cls");
            system("color 07"); // Reset to default color                      
            printf("Game Over! You collided with an ALIEN.\n");
            saveScore(score); // Save the score to the file
            break;
        }

        // Update visible rows and score
        score++;
        if (viewStart < TrackHeight - ViewHeight)
            viewStart++;

        // Check for input and update car position immediately
        if (_kbhit())
        {
            input = _getch();
                 if ((input == 'a' || input == 'A') && carPosX > 1) //&& track[carPosY][carPosX - 1] != 'X')
                {carPosX-=4;Beep(750,10);}
            else if ((input == 'd' || input == 'D') && carPosX < TrackWidth -2 ) //&& track[carPosY][carPosX + 1] != 'X')
                {carPosX+=4;Beep(750,10);};
        }

        // Update obstacles (move down)
        for (i = TrackHeight - 1; i > 0; i--)
        {
            for (j = 0; j < TrackWidth; j++)
            {
                track[i][j] = track[i - 1][j];
            }
        }

        // Add new obstacles in the top row
        for (j = 0; j < TrackWidth; j++)
        {
            track[0][j] = (rand() % 100 == 0) ? 'X' : ' ';
        }

        // Delay for game speed
       ///////////////////////////////////////////////////////// delay(delayed_time);
        delayed_time/=acceleration;
    }

    // display the scores
    struct LeaderboardEntry leaderboard[MaxLeaderboard];
    int numEntries = 0;
    loadLeaderboard(leaderboard, &numEntries);

    printf("\nYour score: %d\n", score);
}

void initializeTrack(char track[TrackHeight][TrackWidth])
{
    int i, j;  
    for (i = 0; i < TrackHeight; i++)
    {
        for (j = 0; j < TrackWidth; j++)
        {
            track[i][j] = ' ';
        }
    }
}

void printTrack(char track[TrackHeight][TrackWidth], int carPosX, int carPosY, int viewStart)
{
    int i, j;  
    system("cls");//clearScreen();   
    for (i = viewStart; i < viewStart + ViewHeight; i++)
    {
        for (j = 0; j < TrackWidth; j++)
        {
            if (i == carPosY && j == carPosX) 
            {
                setTextColor(1); // Blue for car
                printf(CAR);
            }
            else if (track[i][j] == 'X') 
            {
                setTextColor(4); // Red for obstacles
                printf(OBSTACLE);
            }
            else
            {
                setTextColor(0); // Default color
                printf(" ");
            }
        }
        printf("\n");
    }
    
}

int checkCollision(char track[TrackHeight][TrackWidth], int carPosX, int carPosY)
{
    if (carPosY >= 0 && carPosY < TrackHeight && carPosX >= 0 && carPosX < TrackWidth)
    {
        return track[carPosY][carPosX] == 'X'||
        track[carPosY][carPosX+1] == 'X'||
        track[carPosY][carPosX+2] == 'X'||
        track[carPosY][carPosX+3] == 'X'||
        track[carPosY][carPosX+4] == 'X'; // Check for obstacle collision
    }
    return 0;
}

void setTextColor(int color)
{
     printf("\033[%dm", 30 + color);
    
}

void saveScore(int score)
{
    FILE *fptr;
    char name[50];

    fptr = fopen("scores.txt", "a+");

    printf("Enter your nickname: ");
    scanf("%s", name);

    fprintf(fptr, "%d %s\n", score, name);
    fclose(fptr);
}

void loadLeaderboard(struct LeaderboardEntry leaderboard[], int *numEntries)
{
    FILE *fptr;
    int score;
    char nickname[50];

    fptr = fopen("scores.txt", "r");
    if (fptr == NULL)
    {
        printf("LEADERBOARD IS EMPTY");
        return;
    }

    *numEntries = 0;
    while (fscanf(fptr, "%d %s", &score, nickname) != EOF)
    {
        leaderboard[*numEntries].score = score;
        strcpy(leaderboard[*numEntries].nickname, nickname);
        (*numEntries)++;
    }

    fclose(fptr);
}

void sortLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries)
{
    int i, j;
    struct LeaderboardEntry temp;

    for (i = 0; i < numEntries - 1; i++)
    {
        for (j = i + 1; j < numEntries; j++)
        {
            if (leaderboard[i].score < leaderboard[j].score)
            {
                temp = leaderboard[i];
                leaderboard[i] = leaderboard[j];
                leaderboard[j] = temp;
            };
        };
    };
}

void displayLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries)
{
	int i;
	setTextColor(5);
    printf("\nLeaderboard:\n");
    printf("Rank | Score | Nickname\n");
    printf("-------------------------\n");

    for ( i = 0; i < numEntries && i < MaxLeaderboard; i++)
    {
        printf("%-4d | %-5d | %s\n", i + 1, leaderboard[i].score, leaderboard[i].nickname);
    }
    setTextColor(7);
}
