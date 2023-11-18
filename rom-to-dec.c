#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// In order to convert decimal to roman, we started from the thousands all the way to the unit, now we will do the opposite, starting from the right to the left

int romanToDecimal(char *romanNum);

// Checks whether we have invalid characters after a given index. For example, we cannot have 'D' after 'D' of 'C' after 'CM'
int checkInvalidSequence(char *romanNum, int index, char *characters);

// Adds a sequence of characters (M, C, X, I)
int addCharSequence(char *string, int *strIndex, char romanNum, int romanNumVal, int *counter);

int main(void)
{
  char romanNumber[20] = "MCCCXXXIX";
  printf("%d\n", romanToDecimal(romanNumber));

  return 0;
}

int romanToDecimal(char *romanNum)
{
  int index = 0;
  int counter = 0;

  // Adding thousands while the character is equal to 'M'
  int addM = addCharSequence(romanNum, &index, 'M', 1000, &counter);
  if (addM == 0)
  {
    printf("Extra M found in the string.\n");
    return -1;
  }

  // Checking for 'CM' sequence == 900
  if (romanNum[index] == 'C' && romanNum[index + 1] == 'M')
  {
    // We start checking 2 indexes later bcs we cannot have "CMD" after "CM"
    // #TODO condition for 990 (we need an extra C for XC) -> I removed the C for now
    int validate = checkInvalidSequence(romanNum, index + 2, "MD");
    if (validate == 0)
    {
      return -1;
    }
    counter += 900;
    index += 2; // We move 2 indexes since we have checked a sequence of 2 chars
  }

  if (romanNum[index] == 'D')
  {
    int validate = checkInvalidSequence(romanNum, index + 1, "MD");
    if (validate == 0)
    {
      return -1;
    }
    counter += 500;
    index++;
  }

  if (romanNum[index] == 'C' && romanNum[index + 1] == 'D')
  {
    int validate = checkInvalidSequence(romanNum, index + 2, "MDC");
    if (validate == 0)
    {
      return -1;
    }
    counter += 400;
    index += 2;
  }

  // Checking for 'C', which can happen 3 times
  int addC = addCharSequence(romanNum, &index, 'C', 100, &counter);
  if (addC == 0)
  {
    printf("Extra C found in the string.\n");
    return -1;
  }

  if (romanNum[index] == 'X' && romanNum[index + 1] == 'C')
  {
    // #TODO condition for 90 (we need an extra X for XC) -> I removed the X for now
    int validate = checkInvalidSequence(romanNum, index + 2, "MDCL");
    if (validate == 0)
    {
      return -1;
    }
    counter += 90;
    index += 2;
  }

  // Checking for 'L'
  if (romanNum[index] == 'L')
  {
    int validate = checkInvalidSequence(romanNum, index + 1, "MDCL");
    if (validate == 0)
    {
      return -1;
    }
    counter += 50;
    index++;
  }

  // Checking for 'XL' which can only happen once
  if (romanNum[index] == 'X' && romanNum[index + 1] == 'L')
  {
    int validate = checkInvalidSequence(romanNum, index + 2, "MDCLX");
    if (validate == 0)
    {
      return -1;
    }
    counter += 40;
    index += 2;
  }

  int addX = addCharSequence(romanNum, &index, 'X', 10, &counter);
  if (addX == 0)
  {
    return -1;
  }

  if (romanNum[index] == 'I' && romanNum[index + 1] == 'X')
  {
    int validate = checkInvalidSequence(romanNum, index + 2, "MDCLXVI");
    if (validate == 0)
    {
      return -1;
    }
    counter += 9;
    return counter;
  }

  if (romanNum[index] == 'V')
  {
    int validate = checkInvalidSequence(romanNum, index + 1, "MDCLXV");
    if (validate == 0)
    {
      return -1;
    }
    counter += 5;
    index++;
  }

  if (romanNum[index] == 'I' && romanNum[index + 1] == 'V')
  {
    int validate = checkInvalidSequence(romanNum, index + 2, "MDCLXVI");
    if (validate == 0)
    {
      return -1;
    }
    counter += 4;
    return counter;
  }

  int addI = addCharSequence(romanNum, &index, 'I', 1, &counter);
  if (addI == 0)
  {
    return -1;
  }

  if (counter == 0)
  {
    printf("Invalid number.\n");
    return -1;
  }

  return counter;
}

int checkInvalidSequence(char *romanNum, int index, char *characters)
{
  for (int i = index; romanNum[i] != '\0'; i++)
  {
    for (int j = 0; characters[j] != '\0'; j++)
    {
      if (romanNum[i] == characters[j]) // If we find an invalid character after that
      {
        printf("Invalid Roman Number: %c at position %d\n", romanNum[i], i + 1);
        return 0;
      }
    }
  }
  return 1;
}

// Adds a sequence of the characters "M, C, X, I"
int addCharSequence(char *string, int *strIndex, char romanNum, int romanNumVal, int *counter)
{
  int countChar = 0;
  while (string[*strIndex] == romanNum)
  {
    *counter += romanNumVal;
    countChar++;
    if (countChar > 3)
    {
      return 0;
    }
    *strIndex += 1;
  }
  return 1;
}