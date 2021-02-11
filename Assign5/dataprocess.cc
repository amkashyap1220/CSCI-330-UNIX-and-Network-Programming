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
 * @brief Performs a casesar cipher on a string
 * 
 * @param str string to be encrypted
 * @param size size of string to be encrypted
 * @param shift amount to be shifted by
 */
void caesarCipher(char str[], int size, int shift)
{
    // If the shift is over the length of the alphabet, shrink it down
    shift %= 26;

    // For each char in the string
    for (int i = 0; i < size; i++)
    {
        // If the char is in the alphabet shift if by shift amount on the alphabet
        if (isalpha(str[i]))
        {
            str[i] += shift;

            // ensuring that it stays a alphbetic char
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
 * @brief Performs a rotation on a string (caesar shift on all chars)
 * 
 * @param str string to be encrypted
 * @param size size of string to be encrypted
 * @param shift amount to be shifted by
 */
void rotation(char str[], int size, int shift)
{
    // Loop through each char and shift it along all char 0-255
    for (int i = 0; i < size; i++)
    {
        str[i] = (str[i] + shift) % 255;
    }
}

/**
 * @brief Translates a string to binary
 * 
 * @param str 
 * @param size 
 * @param binary 
 */
void toBinary(char str[], int size, char binary[])
{
    int num;

    // Array of possible binary values
    char binvals[] = "01";

    // For each char in the string
    for (int i = 0; i < size; i++)
    {
        num = str[i];

        // Fill the binary array with the translation of the char
        for (int z = i * 8 + 7; z >= i * 8; z--)
        {
            binary[z] = binvals[num % 2];
            num /= 2;
        }
    }
}

/**
 * @brief Translates a string to hex
 * 
 * @param str string to translate
 * @param size size of string 
 * @param hex string that will store the translated information
 */
void toHex(char str[], int size, char hex[])
{
    int num;

    // Array of possible hex values
    char hexvals[] = "0123456789ABCDEFGH";

    // For each char in the string
    for (int i = 0; i < size; i++)
    {
        num = str[i];

        // Fill the hex array with the translation of the char
        for (int z = i * 2 + 1; z >= i * 2; z--)
        {
            hex[z] = hexvals[num % 16];
            num /= 16;
        }
    }
}