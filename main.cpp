#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "GameLogic.h"
#include "Drawing.h"

const int ROWS = 6;    // Number of rows in the Connect Four board
const int COLUMNS = 7; // Number of columns in the Connect Four board
bool isGameOver = false; // Flag to check if the game has ended

// Global game state
std::vector<std::vector<Player>> board(6, std::vector<Player>(7, NONE));

int main() {
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a larger windowed mode window and its OpenGL context
    int windowWidth = 800 * 4 / 3;  // Change the window width
    int windowHeight = 600 * 4 / 3; // Change the window height
    window = glfwCreateWindow(windowWidth, windowHeight, "2D Connect Four", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing GLEW" << std::endl;
        return -1;
    }

    // Set up an orthographic projection with larger margins
    float marginX = 0.2f; // Increase the X margin
    float marginY = 0.2f; // Increase the Y margin
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    // Main loop
    Player currentPlayer = RED;
    while (!glfwWindowShouldClose(window)) {
        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the 7x6 grid with larger margins
        drawGrid(COLUMNS, ROWS, marginX, marginY);

        // Calculate column width and positions for numbers
        float columnWidth = (1.0f - 2.0f * marginX) / 7;
        float yPosition = 1.0 - 0.7 * marginY; // Y position for numbers
        float numberSize = columnWidth / 3; // Adjust size as necessary

        // Draw numbers for column headers
        float firstColumnCenterX = marginX + columnWidth / 2.0f;

        drawNumbers(firstColumnCenterX, columnWidth, yPosition, numberSize);
        
        // Calculate y position of the first token row (bottom row)
        float rowHeight = (1.0f - 2.0f * marginY) / ROWS;
        float firstRowYPosition = marginY + (ROWS - 1) * rowHeight;  // This is the y position of the bottom row
 
        // Draw the tokens based on the board state
        drawTokens(board, marginX, columnWidth, firstRowYPosition, rowHeight);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        int columnInput;
        std::cout << "Player " << (currentPlayer == RED ? "1 (Red)" : "2 (Blue)") << ", enter a column (1-7): ";
        if (std::cin >> columnInput) {
            if (placeToken(columnInput, currentPlayer)) {
                // Check for a win after a successful move
                if (checkWin(currentPlayer)) {
                    std::cout << "Player " << (currentPlayer == RED ? "Red" : "Blue") << " Wins!" << std::endl;
                    isGameOver = true; // Set the game over flag
                    break; // Exit the game loop
                }
                if (!isGameOver && isBoardFull()) {
                    std::cout << "It's a draw!" << std::endl;
                    std::cout << "Close window to end the game." << std::endl;
                    isGameOver = true;  // The game is over, but it's a draw, not a win
                    break;
                }
                currentPlayer = (currentPlayer == RED ? BLUE : RED); // Switch players if no win
            }
            else {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
        else {
            // If the input was not a number, clear the error state and ignore the rest of the line.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 7." << std::endl;
        }

        // Add a small delay for the console input
        glfwWaitEventsTimeout(0.5);
    }

    if (isGameOver) {
        std::cout << (isBoardFull() && !checkWin(RED) && !checkWin(BLUE) ? "It's a draw!" : "Close window to end the game.") << std::endl;
        while (!glfwWindowShouldClose(window)) {
            // Continue to display the game state
            glClear(GL_COLOR_BUFFER_BIT);

            // Redraw grid, numbers, and tokens
            drawGrid(COLUMNS, ROWS, marginX, marginY);

            // Calculate column width and positions for numbers
            float columnWidth = (1.0f - 2.0f * marginX) / 7;
            float yPosition = 1.0 - 0.7 * marginY; // Y position for numbers
            float numberSize = columnWidth / 3; 

            float firstColumnCenterX = marginX + columnWidth / 2.0f;
            drawNumbers(firstColumnCenterX, columnWidth, yPosition, numberSize);

            // Calculate y position of the first token row (bottom row)
            float rowHeight = (1.0f - 2.0f * marginY) / ROWS;
            float firstRowYPosition = marginY + (ROWS - 1) * rowHeight;  // This is the y position of the bottom row

            // Draw the tokens based on the board state
            drawTokens(board, marginX, columnWidth, firstRowYPosition, rowHeight);

            glfwSwapBuffers(window);
            glfwPollEvents();  // This will keep the window responsive
        }
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
