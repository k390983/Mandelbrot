
//gcc main.c -lraylib -o Mandelbrot
//Mandelbrot mode, real center, imaginary center

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"


int main(int argc, char **argv){
    long int width = 1280;
    long int height = 720;
    long double realCenter;
    long double imagCenter;
    long double zoom = 1;
    long double max = 30;
    long int z;
    int mode;

    SetTargetFPS(60);

    // ---------- < zoom mode > ----------

    if(atoll(&argv[1][0]) == 0){
        realCenter = atof(argv[2]);
        imagCenter = atof(argv[3]);

        InitWindow(width, height, "Mandelbrot Zoom");

        while(!WindowShouldClose()){
            BeginDrawing();
            ClearBackground(WHITE);

            zoom = zoom * 0.9;
            max = max * 1.1;

            long double realMin = realCenter - 2 * zoom;
            long double realMax = realCenter + 2 * zoom;
            long double imagMin = imagCenter - 2 * zoom;
            long double imagMax = imagMin + (realMax - realMin) * height / width;
            long double realFactor = (realMax - realMin) / (width - 1);
            long double imagFactor = (imagMax - imagMin) / (height - 1);

            for(long int y = 0; y < height; ++y)
            {
                long double imagC = imagMax - y * imagFactor;

                for(long int x = 0; x < width; ++x)
                {
                    long double realC = realMin + x * realFactor;
                    long double realZ = realC;
                    long double imagZ = imagC;
                    int isInside = 1;

                    for(z = 0; z < max; ++z)
                    {
                        long double realZZ = realZ * realZ;
                        long double imagZZ = imagZ * imagZ;

                        if(realZZ + imagZZ > 4)
                        {
                            isInside = 0;
                            break;
                        }

                        imagZ = 2 * realZ * imagZ + imagC;
                        realZ = realZZ - imagZZ + realC;

                    }

                    if(isInside == 1){
                        DrawPixel(x, y, BLACK);

                    }else if(z < max / 2 - 1){
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {(long int)colorFactor, 0, 0, 255};
                        DrawPixel(x, y, color);
                    }else{
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {255, (long int)colorFactor, (long int)colorFactor, 255};
                        DrawPixel(x, y, color);

                    }

                }

            }

            EndDrawing();

            if(IsKeyPressed(KEY_P) == 1){
                char fileName[100];
                time_t num = time(NULL);
                sprintf(fileName ,"madelbrot%ld.png", num);
                TakeScreenshot(fileName);

            }


            BeginDrawing();

            char text[100];
            sprintf(text, "%f + %fi (zoom = %f, max iterations = %d)", (float)realCenter, (float)imagCenter, (float)zoom, (int)max);
            DrawText(text, 10, 10, 15, WHITE);
            DrawText("[p]: take screenshot", 10, height - (10 + 15), 15, WHITE);

            EndDrawing();

        }

    }

    // ---------- < render mode > ----------

    else if(atoll(&argv[1][0]) == 1){
        realCenter = atof(argv[2]);
        imagCenter = atof(argv[3]);
        zoom = 1 / atof(argv[4]);

        InitWindow(width, height, "Mandelbrot Zoom");

        while(!WindowShouldClose()){
            BeginDrawing();
            ClearBackground(WHITE);

            max = max * 1.1;

            long double realMin = realCenter - 2 * zoom;
            long double realMax = realCenter + 2 * zoom;
            long double imagMin = imagCenter - 2 * zoom;
            long double imagMax = imagMin + (realMax - realMin) * height / width;
            long double realFactor = (realMax - realMin) / (width - 1);
            long double imagFactor = (imagMax - imagMin) / (height - 1);

            for(long int y = 0; y < height; ++y)
            {
                long double imagC = imagMax - y * imagFactor;

                for(long int x = 0; x < width; ++x)
                {
                    long double realC = realMin + x * realFactor;
                    long double realZ = realC;
                    long double imagZ = imagC;
                    int isInside = 1;

                    for(z = 0; z < max; ++z)
                    {
                        long double realZZ = realZ * realZ;
                        long double imagZZ = imagZ * imagZ;

                        if(realZZ + imagZZ > 4)
                        {
                            isInside = 0;
                            break;
                        }

                        imagZ = 2 * realZ * imagZ + imagC;
                        realZ = realZZ - imagZZ + realC;

                    }

                    if(isInside == 1){
                        DrawPixel(x, y, BLACK);

                    }else{
                        long double colorFactor = (long double)z / ((long double)max - 1) * 255;
                        Color color = {(long int)colorFactor, (long int)colorFactor, (long int)colorFactor, 255};
                        DrawPixel(x, y, color);

                    }

                    /*else if(z < max / 2 - 1){
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {(long int)colorFactor, 0, 0, 255};
                        DrawPixel(x, y, color);
                    }else{
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {255, (long int)colorFactor, (long int)colorFactor, 255};
                        DrawPixel(x, y, color);

                    }*/

                }

            }

            EndDrawing();

            if(IsKeyPressed(KEY_P) == 1){
                char fileName[100];
                time_t num = time(NULL);
                sprintf(fileName ,"madelbrot%ld.png", num);
                TakeScreenshot(fileName);

            }

            BeginDrawing();

            char text[100];
            sprintf(text, "%f + %fi (zoom = %f, max iterations = %d)", (float)realCenter, (float)imagCenter, (float)zoom, (int)max);
            DrawText(text, 10, 10, 15, WHITE);
            DrawText("[p]: take screenshot", 10, height - (10 + 15), 15, WHITE);

            EndDrawing();

        }

    }

    // ---------- < final render mode > ----------

    else if(atoll(&argv[1][0]) == 2){
        width = 7680;
        height = 4320;

        realCenter = atof(argv[2]);
        imagCenter = atof(argv[3]);
        zoom = 1 / atof(argv[4]);
        max = atof(argv[5]);

        InitWindow(width, height, "Mandelbrot Zoom");

        while (!WindowShouldClose()){
            BeginDrawing();
            ClearBackground(WHITE);

            long double realMin = realCenter - 2 * zoom;
            long double realMax = realCenter + 2 * zoom;
            long double imagMin = imagCenter - 2 * zoom;
            long double imagMax = imagMin + (realMax - realMin) * height / width;
            long double realFactor = (realMax - realMin) / (width - 1);
            long double imagFactor = (imagMax - imagMin) / (height - 1);

            for(long int y = 0; y < height; ++y)
            {
                long double imagC = imagMax - y * imagFactor;

                for(long int x = 0; x < width; ++x)
                {
                    long double realC = realMin + x * realFactor;
                    long double realZ = realC;
                    long double imagZ = imagC;
                    int isInside = 1;

                    for(z = 0; z < max; ++z)
                    {
                        long double realZZ = realZ * realZ;
                        long double imagZZ = imagZ * imagZ;

                        if(realZZ + imagZZ > 4)
                        {
                            isInside = 0;
                            break;
                        }

                        imagZ = 2 * realZ * imagZ + imagC;
                        realZ = realZZ - imagZZ + realC;

                    }

                    if(isInside == 1){
                        DrawPixel(x, y, BLACK);

                    }

                    //Mono
                    /*else{
                        long double colorFactor = (long double)z / ((long double)max - 1) * 255;
                        Color color = {(long int)colorFactor, (long int)colorFactor, (long int)colorFactor, 255};
                        DrawPixel(x, y, color);

                    }*/

                    //Red
                    /*else if(z < max / 2 - 1){
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {(long int)colorFactor, 0, 0, 255};
                        DrawPixel(x, y, color);
                    }else{
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {255, (long int)colorFactor, (long int)colorFactor, 255};
                        DrawPixel(x, y, color);

                    }*/

                    //Dark Blue
                    else if(z < max / 2 - 1){
                        long double colorFactor = (long double)z / ((long double)max / 2 - 1) * 100;
                        Color color = {0, (long int)colorFactor, (long int)colorFactor, 255};
                        DrawPixel(x, y, color);
                    }else{
                        long double colorFactor1 = (long double)z / ((long double)max / 2 - 1) * 100 + 155;
                        long double colorFactor2 = (long double)z / ((long double)max / 2 - 1) * 255;
                        Color color = {0, (long int)colorFactor1, (long int)colorFactor1, 255};
                        DrawPixel(x, y, color);

                    }

                }

            }

            EndDrawing();

            char fileName[100];
            time_t num = time(NULL);
            sprintf(fileName ,"madelbrot%ld.png", num);
            TakeScreenshot(fileName);
            exit(0);

        }

    }

}
