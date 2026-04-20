#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define maxStars 80

// Bird variables
float birdY = 0;
float velocity = 0;

// Pipe variables
float pipeX = 1.0;
float pipeGapY;

// Game state
bool gameOver = false;
int score = 0;

float transition = 0.0f;   // 0 = day, 1 = night
bool isNight = false;
bool isTransitioning = false;

struct Star
{
    float x, y;
};
Star stars[maxStars];

// Draw text
void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawBackground()
{
    // Clouds
    glColor3f(1.0 * (1 - transition),
              1.0 * (1 - transition),
              1.0 * (1 - transition));

    // Cloud 1
    for (int i = 0; i < 3; i++)
    {
        float cx = 0.6 + i * 0.07;
        float cy = 0.6;
        float r = 0.05;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int j = 0; j <= 50; j++)
        {
            float angle = 2 * M_PI * j / 50;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
        glEnd();
    }

    // Cloud 2
    for (int i = 0; i < 3; i++)
    {
        float cx = 0.7 + i * 0.06;
        float cy = 0.5;
        float r = 0.04;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int j = 0; j <= 50; j++)
        {
            float angle = 2 * M_PI * j / 50;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
        glEnd();
    }

    // Sun
    float sx = 0.7, sy = 0.75;
    for (int k = 3; k >= 1; k--)
    {
        float glowR = 0.08 + k * 0.02;
        glColor4f(1.0, 0.9, 0.0, 0.2 * (1 - transition));
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(sx, sy);
        for (int i = 0; i <= 100; i++)
        {
            float angle = 2 * M_PI * i / 100;
            glVertex2f(sx + glowR * cos(angle), sy + glowR * sin(angle));
        }
        glEnd();
    }

    glColor3f(1.0 * (1 - transition),
              0.8 * (1 - transition),
              0.2 * (1 - transition));
    float r = 0.08;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(sx, sy);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * M_PI * i / 100;
        glVertex2f(sx + r * cos(angle), sy + r * sin(angle));
    }
    glEnd();

    // Moon (with alpha blending)
    glColor4f(transition, transition, 0.6 * transition, transition);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(sx, sy);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * M_PI * i / 100;
        glVertex2f(sx + r * cos(angle), sy + r * sin(angle));
    }
    glEnd();

    // Crescent overlay (optional)
    glColor4f(0.05, 0.05, 0.2, transition);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(sx + 0.03, sy);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * M_PI * i / 100;
        glVertex2f(sx + 0.03 + r * cos(angle), sy + r * sin(angle));
    }
    glEnd();

   // 🌱 Grass (green strip)
    glColor3f(0.2, 0.8, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(-1, -0.8);
    glVertex2f(1, -0.8);
    glVertex2f(1, -0.9);
    glVertex2f(-1, -0.9);
    glEnd();

    // 🌾 Grass spikes (small triangles)
    glColor3f(0.1, 0.6, 0.1);
    for (float x = -1; x < 1; x += 0.05)
    {
        glBegin(GL_TRIANGLES);
        glVertex2f(x, -0.8);
        glVertex2f(x + 0.02, -0.75);
        glVertex2f(x + 0.04, -0.8);
        glEnd();
    }
// 🌼 Flowers
    for (float x = -0.9; x < 1; x += 0.2)
    {
                                    // Yellow center
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_TRIANGLE_FAN);
        float r = 0.01;
        float cx = x;
        float cy = -0.85;

        glVertex2f(cx, cy);
        for (int i = 0; i <= 20; i++)
        {
            float angle = 2 * 3.1416 * i / 20;
            glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
        }
        glEnd();
    }
    // Soil
    glColor3f(0.5, 0.25, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(-1, -0.9);
    glVertex2f(1, -0.9);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();

}
// ================= STARS ====================

void drawStars()
{
    glPointSize(2 + rand()%3);
    glBegin(GL_POINTS);
    for (int i = 0; i < maxStars; i++)
    {
        float brightness = (rand()%100)/100.0f;
        glColor3f(brightness, brightness, brightness);
        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();
}

// 🐦 Draw bird (circle instead of square)
void drawBird()
{
    // 🟡 Body (yellow circle)
    glColor3f(1.0, 0.85, 0.0);
    float r = 0.05;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, birdY);
    for (int i = 0; i <= 360; i+=10)
    {
        float angle = 2 * 3.1416 * i / 180.0f;
        glVertex2f(r * cos(angle), birdY + r * sin(angle));
    }
    glEnd();

    // ⚪ Eye (white)
    glColor3f(1.0, 1.0, 1.0);
    float er = 0.015;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.02, birdY + 0.02);
    for (int i = 0; i <= 50; i++)
    {
        float angle = 2 * 3.1416 * i / 50;
        glVertex2f(0.02 + er * cos(angle), birdY + 0.02 + er * sin(angle));
    }
    glEnd();

    // ⚫ Eye pupil
    glColor3f(0.0, 0.0, 0.0);
    float pr = 0.007;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.025, birdY + 0.02);
    for (int i = 0; i <= 50; i++)
    {
        float angle = 2 * 3.1416 * i / 50;
        glVertex2f(0.025 + pr * cos(angle), birdY + 0.02 + pr * sin(angle));
    }
    glEnd();

    // 🔺 Beak (orange)
    glColor3f(1.0, 0.4, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.05, birdY);
    glVertex2f(0.09, birdY + 0.015);
    glVertex2f(0.09, birdY - 0.015);
    glEnd();

    // 🪽 Wing
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.01, birdY);
    glVertex2f(-0.04, birdY + 0.02);
    glVertex2f(-0.04, birdY - 0.02);
    glEnd();
}

// Draw pipes
void drawPipe()
{
    // Pipe body
    glColor3f(0.0, 0.8, 0.0);

    // Top pipe
    glBegin(GL_QUADS);
    glVertex2f(pipeX, 1);
    glVertex2f(pipeX + 0.1, 1);
    glVertex2f(pipeX + 0.1, pipeGapY + 0.25);
    glVertex2f(pipeX, pipeGapY + 0.25);
    glEnd();

    // Top cap
    glColor3f(0.0, 0.6, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(pipeX - 0.02, pipeGapY + 0.25);
    glVertex2f(pipeX + 0.12, pipeGapY + 0.25);
    glVertex2f(pipeX + 0.12, pipeGapY + 0.30);
    glVertex2f(pipeX - 0.02, pipeGapY + 0.30);
    glEnd();

    // Bottom pipe
    glColor3f(0.0, 0.8, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(pipeX, -0.8);
    glVertex2f(pipeX + 0.1, -0.8);
    glVertex2f(pipeX + 0.1, pipeGapY - 0.25);
    glVertex2f(pipeX, pipeGapY - 0.25);
    glEnd();

    // Bottom cap
    glColor3f(0.0, 0.6, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(pipeX - 0.02, pipeGapY - 0.30);
    glVertex2f(pipeX + 0.12, pipeGapY - 0.30);
    glVertex2f(pipeX + 0.12, pipeGapY - 0.25);
    glVertex2f(pipeX - 0.02, pipeGapY - 0.25);
    glEnd();
}



// Display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    float dayR = 0.4, dayG = 0.7, dayB = 1.0;
    float nightR = 0.05, nightG = 0.05, nightB = 0.2;

// Linear interpolation (LERP)
    float r = dayR * (1 - transition) + nightR * transition;
    float g = dayG * (1 - transition) + nightG * transition;
    float b = dayB * (1 - transition) + nightB * transition;

    glClearColor(r, g, b, 1.0);
    drawBackground();

    if (transition > 0.1f)
    {
        glColor3f(transition, transition, transition); // fade in
        drawStars();
    }


    if (!gameOver)
    {
        drawBird();
        drawPipe();

        char scoreText[20];
        sprintf(scoreText, "Score: %d", score);
        drawText(-0.9, 0.9, scoreText);
    }
    else
    {
        drawText(-0.3, 0.2," GAME OVER ");

        char finalScore[30];
        sprintf(finalScore, " Final Score: %d", score);
        drawText(-0.3, 0.0, finalScore);

        drawText(-0.3, -0.2, "Press R to Restart");
    }

    glutSwapBuffers();
}

// 🔁 Update (SLOWER GAMEPLAY)

void update(int value)
{
    if (!gameOver)
    {

        // slower gravity
        velocity -= 0.0012;
        birdY += velocity;

        // slower pipe movement
        pipeX -= 0.005;
        for (int i = 0; i < maxStars; i++)
        {
            stars[i].y -= 0.0003;

            if (stars[i].y < 0)
            {
                stars[i].y = 1;
                stars[i].x = (rand() % 200 - 100) / 100.0f;
            }
        }
        // Reset pipe
        if (pipeX < -1)
        {
            pipeX = 1;
            pipeGapY = ((rand() % 100) / 100.0f) * 1.2 - 0.6;
            score++;
        }

        // Collision
        if (birdY > 1 || birdY < -1)
        {
            gameOver = true;
        }

        if (pipeX < 0.05 && pipeX + 0.1 > -0.05)
        {
            if (birdY > pipeGapY + 0.25 || birdY < pipeGapY - 0.25)
            {
                gameOver = true;
            }
        }
        float speed = 0.01f;

        if (isTransitioning)
        {
            if (isNight)
            {
                transition += speed;
                if (transition >= 1.0f)
                {
                    transition = 1.0f;
                    isTransitioning = false;
                }
            }
            else
            {
                transition -= speed;
                if (transition <= 0.0f)
                {
                    transition = 0.0f;
                    isTransitioning = false;
                }
            }
        }
    }

    glutPostRedisplay();

    // slower refresh (bigger = slower)
    glutTimerFunc(25, update, 0);
}

// Keyboard
void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        velocity = 0.03; // slower jump
    }

    if (key == 'r' && gameOver)
    {
        birdY = 0;
        velocity = 0;
        pipeX = 1;
        score = 0;
        gameOver = false;
    }

    if (key == 'n' || key == 'N')
    {
        isNight = !isNight;
        isTransitioning = true;
    }
}

// Init
void init()
{
    glClearColor(0.05, 0.05, 0.2, 1.0);// 🌙 night sky
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < maxStars; i++)
    {
        stars[i].x = (rand() % 200 - 100) / 100.0f; // -1 to 1
        stars[i].y = (rand() % 100) / 100.0f;       // 0 to 1
    }

    pipeGapY = 0;
}

// Main
int main(int argc, char** argv)
{
    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Flappy Bird Unity - Smooth Version");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
