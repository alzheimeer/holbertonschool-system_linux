# 0x01. C - Static variables, getline

## 0. Racing cars mandatory
Write a function that keeps track of the number of laps made by several cars in a race.

### Prototype : void race_state(int *id, size_t size)

### id is an array of int representing the “identifier” of each car.
### size is the size of this array
### Each car identifier is unique
### If an identifier is unknown:
Create a new car with the number of laps = 0

Print Car X joined the race followed by a new line (where X is the identifier)

### Each time the function is called:
The number of laps of each cars listed in id must be incremented by 1

Print the state of the race:
Header: Race state: followed by a new line
For each car sorted by the identifier: Car X [Y laps] (where X is the identifier and Y the number of laps already done)

```
#include "laps.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main()
{

    int ids1[3] = {1, 42, 101};
    int ids2[1] = {11};

    race_state(ids1, 3);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(ids1, 3);
    printf("--\n");
    race_state(ids2, 1);
    printf("--\n");
    race_state(NULL, 0);
    return (0);
}

```