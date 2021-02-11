/**********************************************************
 * CSCI 330         Assignment 5      Spring 2021
 * @author Alexander Kashyap
 * @file dataprocess.cc
 * Section: 1
 * Date Due: 2/12/2021
 * Z-id: z1926618  
 **********************************************************/
#include <cctype> // tolower() isalpha()

/**
 * Performs a casesar cipher on a string
 * @param str string to be encrypted
 * @param size size of string to be encrypted
 * @param shift amount to be shifted by
 */
void caesarCipher(char str[], int size, int shift)
{
    shift %= 26;
    for (int i = 0; i < size; i++)
    {
        if (isalpha(str[i]))
        {
            str[i] += shift;
            if (tolower(str[i]) > 'z')
            {
                str[i] -= 26;
            } 
            else if (tolower(str[i]) < 'a')
            {
                str[i] += 26;
            }
        }
    }
}

/**
 * Performs a rotation on a string (caesar shift on all chars)
 * @param str string to be encrypted
 * @param size size of string to be encrypted
 * @param shift amount to be shifted by
 */
void rotation(char str[], int size, int shift)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = (str[i] + shift) % 255;
    }
}

/**
 * Translates a string to binary
 * @param str string to translate
 * @param size size of string 
 * @param binary string that will store the translated information
 */
void toBinary(char str[], int size, char binary[])
{
    char binvals[] = "01";
    int num;

    for (int i = 0; i < size; i++)
    {
        num = str[i];
        for (int z = i * 8 + 7; z >= i * 8; z--)
        {
            binary[z] = binvals[num % 2];
            num /= 2;
        }
    }

}

/**
 * Translates a string to hex
 * @param str string to translate
 * @param size size of string 
 * @param hex string that will store the translated information
 */
void toHex(char str[], int size, char hex[])
{
    char hexvals[] = "0123456789ABCDEFGH";
    int num;

    for (int i = 0; i < size; i++)
    {
        num = str[i];
        for (int z = i * 2 + 1; z >= i * 2; z--)
        {
            hex[z] = hexvals[num % 16];
            num /= 16;
        }
    }
}