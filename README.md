# one_dimensional_life

1D cellular automata for making pretty pictures on your command line.

In the future I hope to add ways to make noise sound files drum loops and other things from theses.

## Build

```make``` to build

```make clean``` to delete to compiled program

## Instructions

to run with default settings:
```./oneDlife```

to see the help instructions:
```./oneDlife help``` or ```./oneDlife --help``` or ```./oneDlife -h```

to run with command line arguments:
```./oneDlife [RULE] [START_CONDITION] [BOARD_SIZE] [FRAME_TIME] [GENERATIONS] [ON_CHAR] [OFF_CHAR]```

### Arguments

1. Rule:
  - rule set for the automata
  - integer between 0-255
  - default: 30

2. Start Condition:
  - starting board conditions
  - 0 = board with one dot in the center, 1 = random board
  - defualt: 0

3. Board Size:
  - character width of the board
  - integer number greater than 0
  - default: 80

4. Frame Rate:
  - uSecond delay between printing lines
  - integer larger than 1
  - default: 100000

5. Generations:
  - number or generations to print
  - integer larger than 1
  - default: 1000

6. On Character:
  - character to print for "on" or 1 cells
  - any single ASCII character
  - default: '#'

7. Off Character:
  - character to print for "off" or 0 cells
  - any single ASCII character
  - default: ' '
