#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <time.h>

int main()
{
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    srand(time(0));

    int groundY = 350;

    int playerX = 100;
    int playerY = groundY - 20;

    int obsX1 = 600;
    int obsX2 = 800;

    int obsCount = 1;

    int velocity = 0;
    int isJumping = 0;
    int gameRunning = 1;

    int score = 0;

    while(gameRunning)
    {
        cleardevice();

        /* DRAW GROUND */
        setcolor(WHITE);
        line(0, groundY, 640, groundY);

        /* INPUT */
        if(kbhit())
        {
            char ch = getch();

            if(ch == ' ')
            {
                if(!isJumping)
                {
                    velocity = -15;
                    isJumping = 1;
                }
            }

            if(ch == 'e' || ch == 'E')
            {
                closegraph();
                return 0;
            }
        }

        /* GRAVITY */
        velocity += 1;
        playerY += velocity;

        if(playerY >= groundY - 20)
        {
            playerY = groundY - 20;
            isJumping = 0;
        }

        /* SPEED INCREASE */
        int speed = (5 + score / 200) + 5;

        /* MOVE OBSTACLES */
        obsX1 -= speed;
        obsX2 -= speed;

        /* RESET OBSTACLES */
        if(obsX1 < 0)
        {
            obsCount = (rand() % 2) + 1;

            obsX1 = 600;
            obsX2 = 600 + (rand() % 100 + 40);
        }

        /* DRAW PLAYER */
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);

        circle(playerX, playerY, 20);
        floodfill(playerX, playerY, WHITE);

        /* DRAW TRIANGLE 1 */
        setcolor(WHITE);

        line(obsX1, groundY, obsX1 + 20, groundY);
        line(obsX1, groundY, obsX1 + 10, groundY - 20);
        line(obsX1 + 20, groundY, obsX1 + 10, groundY - 20);

        /* DRAW TRIANGLE 2 */
        if(obsCount == 2)
        {
            setcolor(WHITE);

            line(obsX2, groundY, obsX2 + 20, groundY);
            line(obsX2, groundY, obsX2 + 10, groundY - 20);
            line(obsX2 + 20, groundY, obsX2 + 10, groundY - 20);
        }

        /* COLLISION */
        if(abs(playerX - obsX1) < 25 &&
           abs(playerY - (groundY - 10)) < 25)
        {
            gameRunning = 0;
        }

        if(obsCount == 2)
        {
            if(abs(playerX - obsX2) < 25 &&
               abs(playerY - (groundY - 10)) < 25)
            {
                gameRunning = 0;
            }
        }

        /* SCORE */
        score++;

        char s[50];

        sprintf(s, "Score: %d", score);

        setcolor(WHITE);
        outtextxy(10, 10, s);

        delay(20);
    }

    /* GAME OVER */
    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    setcolor(WHITE);
    outtextxy(180, 150, "GAME OVER");

    char finalScore[50];

    sprintf(finalScore, "FINAL SCORE: %d", score);

    setcolor(WHITE);
    outtextxy(150, 220, finalScore);

    outtextxy(120, 300, "Press any key to exit");

    getch();

    closegraph();

    return 0;
}
