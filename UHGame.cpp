/*
Copyright 2020 Stephen Wilde - CSNorwood (WLGfx).
  _   _ _   _  ____
| | | | | | |/ ___| __ _ _ __ ___   ___
| | | | |_| | |  _ / _` | '_ ` _ \ / _ \
| |_| |  _  | |_| | (_| | | | | | |  __/
 \___/|_| |_|\____|\__,_|_| |_| |_|\___|
                                        .

 UHGame is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 UHGame is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with UHGame. If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

struct game_level {
    char intro[128];
    char outro[128];
    long int range_max; // for PSYCHO level 10 range
};

struct game_level game_levels[11] = {
    // Level 1
    {
        "Welcome to the easiest level, yeah, LEVEL 1!!!\n",
        "Well done, but it was way too easy anyway\n",
        10
    },
    // Level 2
    {
        "Welcome to the NEXT easiest level, okay, LEVEL 2!!!\n",
        "Well done, but it was easy only a tiny bit harder than leven 1 anyway\n",
        100
    },
    // Level 3
    {
        "Okay, now we're testing you, LEVEL 3!!!\n",
        "Well done, now try level 4\n",
        1000
    },
    // Level 4
    {
        "Welcome to a moderately easy but hard, LEVEL 4!!!\n",
        "Well done, bit harder, so alright\n",
        10000
    },
    // Level 5
    {
        "Welcome to playing a stupid level, LEVEL 5!!!\n",
        "Well done, you actually lasted\n",
        100000
    },
    // Level 6
    {
        "Welcome to 'should be a piece of cake.', LEVEL 6!!!\n",
        "Well done, but you are not a number god just yet\n",
        1000000
    },
    // Level 7
    {
        "Welcome to Psycho easy, LEVEL 7!!!\n",
        "Well done, I guess that was too easy for you\n",
        10000000
    },
    // Level 8
    {
        "Welcome to Psycho medium, LEVEL 8!!!\n",
        "Well done, Getting there but still two levels left\n",
        100000000
    },
    // Level 9
    {
        "Welcome to Psycho hard, LEVEL 9!!!\n",
        "Well done, onto level 10 now you absolute beast\n",
        1000000000
    },
    // Level 10
    {
        "Welcome to just PSYCHO, LEVEL 10!!!\n",
        "Well done, that was impressive!!! you are now a number god!!!\n",
        10000000000000
    },

    //level 11
    {
    "Welcome to the WTF level!!! Added for giggles\n",
    "Well i cant believe you mastered that one! holy crap\n",
    200000000000000000
    }
};

void show_intro() {
    puts("Welcome to the 'Guess The Number game v0.0.78'");
    puts("Last updated 9th May 2020");
    puts("Brought to you by Stephen Wilde (with a bit of help from CSNorwood aka WLGfx)");
    puts("www.stephenwilde.net | www.csnorwood.com\n");
    puts("**************************************************");
}

int get_level_select() {
    int level;

    for (int pos = 0; pos < 11; pos++) {
        printf("Level %d is between 1 and %ld\n",
                pos + 1,
                game_levels[pos].range_max);
    }

    do {
        printf("\nEnter a level to play 1 to 11 (0 to quit) : ");
        scanf("%d", &level);
    } while (level < 0 || level > 11);

    return level;
}

int play_level(int level) {
    long int number = rand() % (game_levels[level].range_max) + 1;

    printf("\n%s", game_levels[level].intro);

    int completed = 0;
    int try_count = 0;
    long int try_value;

    char buffer[64];
    char *temp_ptr; // used in strtol function

    do {
        printf("Enter value between 1 and %ld (try %d) (Q - Quit): ",
                game_levels[level].range_max,
                try_count + 1);

        scanf("%s", &buffer);

        if (buffer[0] == 'q' || buffer[0] == 'Q') { // option to quit
            puts("So sorry you have given up already...");
            return -1;
        } else if (strcmp("CHEAT", buffer) == 0) { // cheat
            puts("CHEATER HA HA");
            printf("The number is %ld\n", number);
            printf("Adding %d tries\n", (level + 1) * 10);
            try_count += (level + 1) * 10;
        } else {
            try_count++;

            try_value = strtol(buffer, &temp_ptr, 10);

            if (try_value == number) {
                printf("%ld is CORRECT\n", try_value);
                printf("It took you %d tries\n", try_count);
                puts(game_levels[level].outro);
                completed = 1;
            } else if (try_value < number) {
                puts("Too LOW");
            } else if (try_value > number) {
                puts("Too HIGH");
            }
        }
    } while (!completed);

    return 0;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int result;

    do {
        show_intro();

        int level = get_level_select();

        if (level > 0) result = play_level(level - 1);
        else result = -1;

    } while (result == 0);

    return (EXIT_SUCCESS);
}
