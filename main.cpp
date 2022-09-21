/*****************
 * Filename: main.cpp
 * Author: Andy Jang
 * Creation Date: 9/17/22
 * Last Modified On: 9/18/22
 * Purpose: To solve the N-Queens problem.
 * WARNING: This program is horrible optimized. Please be wary with any value above N = 20, it'll take awhile. I got to N = 25 at most.
 * ***************/

#include <iostream>
#include <stack>

/* Function Prototpyes */
void checkInput(int N, bool *invalidInput);
bool isConflict(int N);
void initStack();
void placeNewQueen();
bool isSpace(int N);
void adjustQueen();
void backtrack(int N);
void printBoard(int N);

/*
Majority of functions read and edit these 2 variables, hence global.
*/
std::stack<int> queens;
int filled = 0;

int main()
{
  // Start with getting N
  bool invalidInput = true;
  int N = -1;

  while (invalidInput)
  {
    std::cout << "N: ";
    std::cin >> N;
    std::cout << std::endl;
    checkInput(N, &invalidInput);
  }

  if (N == 0)
  {
    std::cout << "empty board...\n";
    return 0;
  }

  initStack();

  while (filled != N + 1)
  {
    // std::cout << "infinite loop \n";
    // std::cout << "!isConflict result: " << !isConflict(N) << "\n";
    if (!isConflict(N))
    {
      placeNewQueen();
    }
    else if (isSpace(N))
    {
      adjustQueen();
    }
    else
    {
      backtrack(N);
    }
  }

  // omit filler
  queens.pop();
  printBoard(N);

  return 0;
}

/* checks the input and throws out values of N that are not possible to solve*/
void checkInput(int N, bool *invalidInput)
{
  if (N == 2 || N == 3 || N < 0)
  {
    std::cout << "N-Queens is not possible with " << N << ". Please enter a different number\n";
  }
  else
  {
    *invalidInput = false;
    std::cout << "N-value: " << N << std::endl;
  }
}

/* checks if any queens conflict with each other */
bool isConflict(int N)
{
  bool conflict = false;
  bool keepGoing = true;
  std::stack<int> usedQueens;

  int newQueen = queens.top();
  usedQueens.push(newQueen);
  queens.pop();

  while (keepGoing)
  {
    int compareQueen = queens.top();
    usedQueens.push(compareQueen);
    queens.pop();

    // std::cout << "queens size: " << queens.size() << std::endl;

    // check columns
    if (newQueen == compareQueen)
    {
      // std::cout << "column conflict\n";
      conflict = true;
      keepGoing = false;
    }

    // check diagonals
    int yDiag = queens.size() + 1;
    int xDiag = compareQueen;

    // primary diagonal
    for (int i = 0; i < N; i++)
    {
      if (xDiag == newQueen && yDiag == filled)
      {
        // std::cout << "primary diagonal conflict\n";
        conflict = true;
        keepGoing = false;
      }
      xDiag++;
      yDiag++;

      // check overflow
      if (xDiag > N || yDiag > N)
      {
        break;
      }
    }

    // other diagonal
    yDiag = queens.size() + 1;
    xDiag = compareQueen;

    for (int j = 0; j < N; j++)
    {
      if (xDiag == newQueen && yDiag == filled)
      {
        // std::cout << "other diagonal conflict\n";
        conflict = true;
        keepGoing = false;
      }
      xDiag--;
      yDiag++;

      // check overflow
      if (xDiag <= 0 || yDiag > N)
      {
        break;
      }
    }

    if (queens.size() == 0)
    {
      keepGoing = false;
    }
  }
  // remake og stack
  while (usedQueens.size() > 0)
  {
    queens.push(usedQueens.top());
    usedQueens.pop();
  }
  // std::cout << conflict << std::endl;
  return conflict;
}

/* places new queen on stack, increment filled */
void placeNewQueen()
{
  queens.push(1);
  filled++;
}

/* checks if there is space for the queen to move right */
bool isSpace(int N)
{
  if (queens.size() != 0)
  {
    int topQueen = queens.top();
    if (topQueen == N)
    {
      return false;
    }
    return true;
  }
  return true;
}

/* moves the top queen to the right 1 */
void adjustQueen()
{
  if (queens.size() != 0)
  {
    int topQueen = queens.top();
    queens.pop();
    topQueen++;
    queens.push(topQueen);
  }
}

/* backtracks until the next free queen is found */
void backtrack(int N)
{
  queens.pop();
  filled--;

  bool keepGoing = true;
  while (keepGoing)
  {
    if (isSpace(N))
    {
      adjustQueen();
      if (queens.size() == 1)
      {
        filled++;
        queens.push(1);
      }
      keepGoing = false;
    }
    else
    {
      queens.pop();
      filled--;
    }
  }
}

/* prints the board */
void printBoard(int N)
{
  // std::cout << "printing attempted " << queens.size();
  if (queens.size() != 0)
  {
    std::cout << "Solution found!\n";
    std::cout << std::endl;
    for (int i = 0; i < N; i++)
    {
      if (i == 0)
      {
        std::cout << " ";
        for (int a = 0; a < N; a++)
        {
          std::cout << "_ ";
        }
        std::cout << std::endl;
      }
      for (int j = 0; j < N; j++)
      {
        if (j == 0)
        {
          std::cout << "|";
        }
        if (queens.top() - 1 == j)
        {
          std::cout << "Q";
        }
        else
        {
          std::cout << "_";
        }
        std::cout << "|";
      }
      queens.pop();
      std::cout << std::endl;
    }
  }
}

/* initializes the stack to prevent segmentation errors */
void initStack()
{
  filled += 2;
  queens.push(1);
  queens.push(1);
}
