/**********************************************************
 * CSCI 330         Assignment 5      Spring 2021
 * @author Alexander Kashyap
 * @file dataprocess.h
 * Section: 1
 * Date Due: 2/12/2021
 * Z-id: z1926618  
 **********************************************************/
#ifndef DATAPROCESS_H
#define DATAPROCESS_H

// Function that manipulate the buffer directly
void caesarCipher(char str[], int size, int shift);
void rotation(char str[], int size, int shift);

// Functions that convert the ascii chars to something else
void toBinary(char str[], int size, char binary[]);
void toHex(char str[], int size, char hex[]);

#endif // !DATAPROCESS_H