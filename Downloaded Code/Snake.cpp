#include <iostream>
#include <conio.h>
#include<cstdlib>
#include<ctime>
#include<cstdio>
//#include<string>

void run();
void Draw();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void generateFood();
char getMapValue(int value);

// Map dimensions
const int mapwidth = 25;
const int mapheight = 50;

const int size = mapwidth * mapheight;

// The tile values for the map
int map[size];

// Snake head details
int headxpos;
int headypos;
int direction;

// Amount of food the snake has (How long the body is)
int food = 3;

// Determine if game is running
bool running;

int main()
{
    run();
    return 0;
}

// Main game function
void run() {

//int i = 0;
//bool answer;
//while(i == 0) {

    //Start of clock to track program runtime
    std::clock_t start;
    double duration;
    start = std::clock(); // get current time

    // Initialize the map
    initMap();
    running = true;
    while (running) {
        // If a key is pressed
        if (kbhit()) {
            // Change to direction determined by key pressed
            changeDirection(getch());
        }
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC; //clock duration starting

        // Update the map
        update();

        //setup the map
        Draw();
        // Clear the screen
        // Print the map

        // wait 0.5 seconds
        _sleep(duration*2);
    }

    // Print out game over text
    std::cout << "\t!!Game over!!" << std::endl << "\tYour score is: " << food-3 << std::endl; //minus 3 for initial body length
    std::cout << "\tRuntime: "<< duration << " seconds" << std::endl; //prints program duration

//    std::cout << "\tWould you like to keep playing? (Y/N)";
//    std::cin >> answer;
//    if(answer = 'Y') {
//        i += 0;
//        run();
//    }
//    else {
//        break;
//    }

//    // Stop console from closing instantly
//    std::cin.ignore();
//    }

}

// Changes snake direction from input
void changeDirection(char key) {
    /*
      W              UP
    A + D      LEFT  +  RIGHT
      S             DOWN

      1              72
    4 + 2         75 + 77
      3              80
    */
    switch (key) {
    case 72:
        if (direction != 2) direction = 0;
        break;
    case 77:
        if (direction != 3) direction = 1;
        break;
    case 80:
        if (direction != 4) direction = 2;
        break;
    case 75:
        if (direction != 5) direction = 3;
        break;
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    }
}

// Moves snake head to new location
void move(int dx, int dy) {
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (map[newx + newy * mapwidth] == -2) {
        // Increase food value (body length)
        food++;

        // Generate new food on map
        generateFood();
    }

    // Check location is free
    else if (map[newx + newy * mapwidth] != 0) {
        running = false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = food + 1;

}

// Map setup function
void Draw() {
// Clear the screen
    system("cls");

// Prints the map to console
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            // Prints the value at current x,y location
            std::cout << getMapValue(map[x + y * mapwidth]);
        }
        // Ends the line for next x value
        std::cout << std::endl;
    }
}

// Generates new food on map
void generateFood() {
    int x = 0;
    int y = 0;

    int maxx = 18;
    int maxy = 48;

    //set the upper bound to generate the random number
    srand(time(0));
    for(int i = 0; i<10; i++) {
        maxx = rand() <= maxx;
        maxy = rand() <= maxy;
}
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth - maxx) + 1;
        y = rand() % (mapheight - maxy) + 1;

        // If location is not free try again
    } while (map[x + y * mapwidth] != 0);

    // Place new food
    map[x + y * mapwidth] = -2;
}

// Updates the map
void update() {
    // Move in direction indicated
    switch (direction) {
    case 0: move(-1, 0);
        break;
    case 1: move(0, 1);
        break;
    case 2: move(1, 0);
        break;
    case 3: move(0, -1);
        break;
    }

    // Reduce snake values on map by 1
    for (int i = 0; i < size; i++) {
        if (map[i] > 0) map[i]--;
    }
}

// Initializes map
void initMap()
{
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    // Places top and bottom walls
    for (int x = 0; x < mapwidth; ++x) {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < mapheight; y++) {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generates first food
    generateFood();
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
    // Returns a part of snake body
    if (value > 0) return 'o';

    switch (value) {
        // Return wall
    case -1: return 'X';
        // Return food
    case -2: return 'O';
    }
}
