#ifndef DRAWING_H
#define DRAWING_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GameLogic.h" 
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

void drawGrid(int width, int height, float marginX, float marginY) {
    glBegin(GL_LINES);

    // Draw vertical lines
    for (int i = 0; i <= width; ++i) {
        float x = marginX + (float)i / width * (1.0f - 2.0f * marginX);
        glVertex2f(x, marginY);
        glVertex2f(x, 1.0f - marginY);
    }

    // Draw horizontal lines
    for (int i = 0; i <= height; ++i) {
        float y = marginY + (float)i / height * (1.0f - 2.0f * marginY);
        glVertex2f(marginX, y);
        glVertex2f(1.0f - marginX, y);
    }

    glEnd();
}

void drawNumber1(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINES);

    // Vertical line
    glVertex2f(x, y - halfSize);
    glVertex2f(x, y + halfSize);


    glEnd();
}

void drawNumber2(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINE_STRIP);

    // Top horizontal line
    glVertex2f(x - halfSize, y + halfSize);
    glVertex2f(x + halfSize, y + halfSize);

    // Down to the right
    glVertex2f(x + halfSize, y);
    glVertex2f(x - halfSize, y);

    // Bottom horizontal line
    glVertex2f(x - halfSize, y - halfSize);
    glVertex2f(x + halfSize, y - halfSize);

    glEnd();
}

void drawNumber3(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINE_STRIP);

    // Start from top left
    glVertex2f(x - halfSize, y + halfSize);
    glVertex2f(x + halfSize, y + halfSize);
    glVertex2f(x + halfSize, y);
    glVertex2f(x - halfSize, y);
    glVertex2f(x + halfSize, y);
    glVertex2f(x + halfSize, y - halfSize);
    glVertex2f(x - halfSize, y - halfSize);

    glEnd();
}


void drawNumber4(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINES);

    // Upper left vertical
    glVertex2f(x - halfSize, y + halfSize);
    glVertex2f(x - halfSize, y);

    // Diagonal to bottom right
    glVertex2f(x - halfSize, y);
    glVertex2f(x + halfSize, y);

    // Middle horizontal line
    glVertex2f(x + halfSize, y + halfSize);
    glVertex2f(x + halfSize, y - halfSize);

    glEnd();
}

void drawNumber5(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINE_STRIP);

    // Start from top right
    glVertex2f(x + halfSize, y + halfSize);
    glVertex2f(x - halfSize, y + halfSize);
    glVertex2f(x - halfSize, y);
    glVertex2f(x + halfSize, y);
    glVertex2f(x + halfSize, y - halfSize);
    glVertex2f(x - halfSize, y - halfSize);

    glEnd();
}

void drawNumber6(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINES);

    // Vertical line on the left
    glVertex2f(x - halfSize, y + halfSize);
    glVertex2f(x - halfSize, y - halfSize);

    // Bottom horizontal line
    glVertex2f(x - halfSize, y - halfSize);
    glVertex2f(x + halfSize, y - halfSize);

    // Vertical line on the right
    glVertex2f(x + halfSize, y - halfSize);
    glVertex2f(x + halfSize, y);

    // Top horizontal line
    glVertex2f(x - halfSize, y);
    glVertex2f(x + halfSize, y);

    // Top left to middle vertical
    glVertex2f(x - halfSize, y);
    glVertex2f(x - halfSize, y + halfSize / 2);

    // Middle horizontal to the right
    glVertex2f(x - halfSize, y);
    glVertex2f(x, y);

    glEnd();
}


void drawNumber7(float x, float y, float size) {
    float halfSize = size / 2;

    glBegin(GL_LINES);

    // Top horizontal line
    glVertex2f(x - halfSize, y + halfSize);
    glVertex2f(x + halfSize, y + halfSize);

    // Diagonal to bottom right
    glVertex2f(x + halfSize, y + halfSize);
    glVertex2f(x, y - halfSize);

    glEnd();
}

void drawNumbers(float firstColumnCenterX, float columnWidth, float yPosition, float numberSize) {
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white for the numbers
    drawNumber1(firstColumnCenterX, yPosition, numberSize);
    drawNumber2(firstColumnCenterX + columnWidth, yPosition, numberSize);
    drawNumber3(firstColumnCenterX + 2 * columnWidth, yPosition, numberSize);
    drawNumber4(firstColumnCenterX + 3 * columnWidth, yPosition, numberSize);
    drawNumber5(firstColumnCenterX + 4 * columnWidth, yPosition, numberSize);
    drawNumber6(firstColumnCenterX + 5 * columnWidth, yPosition, numberSize);
    drawNumber7(firstColumnCenterX + 6 * columnWidth, yPosition, numberSize);
}

void drawCircle(float cx, float cy, float r, int num_segments, Player playerColor) {
    float theta = 2 * M_PI / float(num_segments);
    float c = cosf(theta); // precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = r; // we start at angle = 0
    float y = 0;

    glBegin(GL_TRIANGLE_FAN);
    if (playerColor == RED)
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
    else if (playerColor == BLUE)
        glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    else
        glColor3f(1.0f, 1.0f, 1.0f); // Default to white if no player color is specified

    glVertex2f(cx, cy); // Center of circle

    for (int i = 0; i <= num_segments; i++) {
        glVertex2f(x + cx, y + cy);

        // apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

// Function to draw the tokens
void drawTokens(const std::vector<std::vector<Player>>& board, float marginX, float columnWidth, float firstRowYPosition, float rowHeight) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            if (board[row][col] != NONE) {
                float cx = marginX + columnWidth * col + columnWidth / 2.0f;
                float cy = firstRowYPosition - row * rowHeight + 0.05;
                drawCircle(cx, cy, columnWidth / 3.0f, 30, board[row][col]); // Adjust num_segments for smoothness
            }
        }
    }
}

#endif // RENDERING_H