#include <ncurses.h>

int main(int argc, char *argv[])
{
    // Initialize ncurses
    initscr();             // Start ncurses mode
    cbreak();              // Disable line buffering
    noecho();              // Don't echo() while we do getch
    nodelay(stdscr, TRUE); // Make getch() non-blocking
    curs_set(0);           // Hide the cursor
    keypad(stdscr, TRUE);  // Enable F1, arrow keys, etc.
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // Start game loop
    int ch;
    int direction = 0; // 0: right, 1: down, 2: left, 3: up
    int feed_x = -1;
    int feed_y = -1;
    int snake[1000][2] = {{10, 10}, {10, 9}, {10, 8}}; // Initial snake position
    int snake_length = 3;
    while ((ch = getch()) != 'q') // Press 'q' to quit
    {
        usleep(50000); // Sleep for 100 milliseconds
        clear();       // Clear the screen
        switch (ch)
        {
        case KEY_RIGHT:
            direction = 0; // right
            break;
        case KEY_DOWN:
            direction = 1; // down
            break;
        case KEY_LEFT:
            direction = 2; // left
            break;
        case KEY_UP:
            direction = 3; // up
            break;
        }

        // locate feed
        if (feed_x == -1 || feed_y == -1)
        {
            feed_x = (rand() % COLS) + 1;
            feed_y = (rand() % LINES) + 1;
        }
        attron(COLOR_PAIR(2));
        mvaddch(feed_y, feed_x, ACS_BLOCK);
        attroff(COLOR_PAIR(2));
        // move snake
        for (int i = snake_length - 1; i > 0; --i)
        {
            snake[i][0] = snake[i - 1][0]; // Move body segments
            snake[i][1] = snake[i - 1][1];
        }
        switch (direction)
        {
        case 0: // right
            snake[0][0] += 1;
            break;
        case 1: // down
            snake[0][1] += 1;
            break;
        case 2: // left
            snake[0][0] -= 1;
            break;
        case 3: // up
            snake[0][1] -= 1;
            break;
        }
        // locate snake
        attron(COLOR_PAIR(1));
        for (int i = 0; i < snake_length; ++i)
        {
            mvaddch(snake[i][1], snake[i][0], ACS_CKBOARD);
        }
        attroff(COLOR_PAIR(1));
        // check collusion
        if (snake[0][0] < 1 || snake[0][0] >= COLS ||
            snake[0][1] < 1 || snake[0][1] >= LINES)
        {
            break; // Snake hit the wall
        }
        for (int i = 1; i < snake_length; ++i)
        {
            if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
            {
                break; // Snake hit itself
            }
        }
        // check feed
        if (snake[0][0] == feed_x && snake[0][1] == feed_y)
        {
            snake_length++; // Increase snake length
            feed_x = -1;    // Reset feed position
            feed_y = -1;    // Reset feed position
        }
        // clear and generate feed
    }

    // Clean up and exit ncurses mode
    clear();
    endwin();
    return 0;
}
