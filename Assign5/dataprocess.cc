#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

void caesarCipher(char str[], int size, int shift)
{
    for (int i = 0; i < size; i++)
    {
        if (str[i] <= 'z' && str[i] >= 'a')
        {
            str[i] += shift;
            while (str[i] > 'z')
            {
                str[i] -= 26;
            } 
            while (str[i] < 'a')
            {
                str[i] += 26;
            }
        }
        else if (str[i] <= 'Z' && str[i] >= 'A')
        {
            str[i] += shift;
            while (str[i] > 'Z')
            {
                str[i] -= 26;
            } 
            while (str[i] < 'A')
            {
                str[i] += 26;
            }
        }
    }
}
void rotation(char str[], int size, int shift)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = (str[i] + shift) % 255;
    }
}
void toBinary(char str[], int size, char binary[])
{
    for (int i = 0; i < size; i++)
    {
        int num = str[i];
        for (int z = i * 8 + 7; z >= i * 8; z--)
        {
            if (num % 2 == 0) {
                binary[z] = '0';
            }
            else
            {
                binary[z] = '1';
            }
            num /= 2;
        }
    }
}
void toHex(char str[], int size, char hex[])
{
    for (int i = 0; i < size; i++)
    {
        int num = str[i];
        for (int z = i * 2 + 1; z >= i * 2; z--)
        {
            int temp = num % 16;
            if (temp < 10)
            {
                hex[z] = temp + 48;
            }
            else
            {
                hex[z] = temp + 87;
            }
            num /= 16;
        }
    }
}