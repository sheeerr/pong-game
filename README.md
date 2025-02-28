# Pong Game

This project is a simple implementation of the classic Pong game using the Raylib library. It features two paddles (one controlled by the player and the other by the CPU) and a ball that bounces between them. The objective is to score points by getting the ball past the opponent's paddle.

## Files

- `src/main.cpp`: Contains the main implementation of the Pong game, including the game loop, entity classes (`Ball`, `Paddle`, and `CpuPaddle`), and game logic for scoring and collision detection.
- `.gitignore`: Specifies files and directories that should be ignored by Git.

## Requirements

To build and run this project, you need to have the following installed:

- C++ compiler (e.g., g++, clang++)
- Raylib library

## Building the Project

1. Clone the repository:
   ```
   git clone [https://github.com/sheeerr/pong-game]
   cd pong-game
   ```

2. Build the project:
   ```
   g++ src/main.cpp -o pong-game -lraylib -lm -lpthread -ldl -lrt -lX11
   ```

## Running the Game

After building the project, you can run the game with the following command:
```
./pong-game
```

## Controls

- Use the UP and DOWN arrow keys to move the player's paddle.

## Contributing

Feel free to submit issues or pull requests if you would like to contribute to the project.
