//Elementary Cellular Automaton

#include <stdio.h>
#include <stdbool.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current status for me
    int total; //running accumulated count of this cell's active status for all generations
} cell;

// Convert a rule number (0-255) into an 8-bit array
// The bits are stored in reverse order
bool setBitArray(bool bitArray[8], int rule) {
    // check if the rule is valid
    if (rule < 0 || rule > 255) {
        return false;
    }

    // store each binary digit in reverse order
    for (int i = 0; i < 8; i++) {
        bitArray[i] = rule % 2;
        rule = rule / 2;
    }

    return true;
}

// Convert the three cell states into an index from 0 to 7
int stateToIndex(bool state[3]) {
    return state[0] * 4 + state[1] * 2 + state[2];
}

// Store each cell's left, current, and right states
void setStates(cell world[WORLD_SIZE]) {
    for (int i = 0; i < WORLD_SIZE; i++) {

        int leftIndex;
        int rightIndex;

        // wrap around to last cell if at the beginning
        if(i == 0){
            leftIndex = WORLD_SIZE - 1;
        } else {
            leftIndex = i - 1;
        }

        // wrap around to the first cell if at the end
        if(i == WORLD_SIZE - 1){
            rightIndex = 0;
        } else {
            rightIndex = i + 1;
        }

        // save the active status of all three cells
        world[i].state[0] = world[leftIndex].active;
        world[i].state[1] = world[i].active;
        world[i].state[2] = world[rightIndex].active;

    }
}

//Update each cell for the next generation and return the number of active cells
int evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) {
    int index;
    int activeCount = 0;
    bool newActive;

    for(int i = 0; i < WORLD_SIZE; i ++ ){
        // find the next state using the cell's 3 neighboring states
        index = stateToIndex(world[i].state);
        newActive = ruleBitArray[index];
        world[i].active = newActive;

        // count active cells and update totals
        if(newActive == true){
            activeCount += 1;
            world[i].total += 1;
        }
        
    }

    return activeCount;
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Elementary Cellular Automaton!\n");
    int rule;
    bool bitArray[8];

    // read a valid rule and convert it to an 8-bit array
    while (true) {
        printf("Enter the rule # (0-255): ");
        scanf("%d", &rule);
        if (setBitArray(bitArray, rule)) {
            break;
        }
    }
    printf("The bit array for rule #%d is ", rule);

    // print the bits in binary order
    for (int i = 7; i >= 0; i--) {
        printf("%d", bitArray[i]);
    }
    printf("\n");

    // display the result of each possible cell state.
    printf("The evolution of all possible states are as follows:\n");
    printf("|ooo|   |oo'|   |o'o|   |o''|   |'oo|   |'o'|   |''o|   |'''|\n ");
   
    // print the rule result for each state
    for(int i = 7; i >= 0; i--){
        if(i != 0){
            if (bitArray[i] == 1){
                printf("|o|     ");
            }
            else if (bitArray[i] == 0){
                printf("|'|     ");
            }
        }
        else{
            if (bitArray[i] == 1){
                printf("|o|    \n");
            }
            else if (bitArray[i] == 0){
                printf("|'|    \n");
            }
        }
    }
    printf("\n");

    // read the number of generations and initialize the world
    setStates(world);
    int generations;
    bool valid = false;
    while(valid == false){
        printf("Enter the number of generations (1-99): \n");
        scanf("%d", &generations);
        if(generations > 99 || generations < 1){
            continue;
        }
        if(generations <= 99 && generations >= 1){
            valid = true;
        }
    }
    printf("\n");
    
    //initialize all cells as inactive
    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].active = false;
        world[i].total = 0;
    }

    //turn on middle cell
    int mid = WORLD_SIZE / 2;
    world[mid].active = true;
    world[mid].total = 1;

    setStates(world);

    // print the initial state of the world
    int numGens;
    printf("Initializing world & evolving...\n");
    for(int i = 0; i < WORLD_SIZE; i++){
        if(world[i].active){
            printf("o");
        }
        else{
            printf("'");
        }
    }
    numGens = 1;
    printf("  %d\n", numGens);


    // evolve and display the world for each generation
    for (int i = 0; i < generations - 1; i++){
        int activeCount = evolveWorld(world, bitArray);
        setStates(world);
        for(int j = 0; j < WORLD_SIZE; j++){
            if(world[j].active == true){
                printf("o");
            }
            else{
                printf("'");
            }
        }
        printf("  %d\n", activeCount);
    }

    // print a line under the final generation
    for (int i = 0; i < WORLD_SIZE; i++) {
        printf("_");
    }
    printf("\n");



    // print the total active count for each cell
    // print the tens digit
    for (int i = 0; i < WORLD_SIZE; i++) {
        int total = world[i].total;

        if(total >= 10){
            printf("%d", total/10);
        }
        else{
            printf(" ");
        }
    }
    printf("\n");

    // print the ones digit
    for (int i = 0; i < WORLD_SIZE; i++) {
        int total = world[i].total;

        if(total == 0){
            printf(" ");
        }
        else{
            printf("%d", total % 10);
        }
    }
    printf("\n");


    return 0;
}
