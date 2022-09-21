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

  // end user input
  // init stack by adding 2 entries onto the stack
  initStack();

  // contains the N-Queens problem logic, had to add 1 more iteration because of short circuiting.
  while (filled != N + 1)
  {
    // if no conflicts, then add new queen
    if (!isConflict(N))
    {
      placeNewQueen();
    }
    // if conflicts, but has space, increment x-value of queen by 1
    else if (isSpace(N))
    {
      adjustQueen();
    }
    // else backtrack
    else
    {
      backtrack(N);
    }
  }

  // omit filler
  // have to remove as it is an excess entry
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

  // compares the top queen to every other entry
  int newQueen = queens.top();
  usedQueens.push(newQueen);
  queens.pop();

  // goes through the rest of the stack
  while (keepGoing)
  {
    int compareQueen = queens.top();
    usedQueens.push(compareQueen);
    queens.pop();

    // check columns
    if (newQueen == compareQueen)
    {
      conflict = true;
      keepGoing = false;
    }

    // check diagonals
    int yDiag = queens.size() + 1;
    int xDiag = compareQueen;

    // check primary diagonal (bottom-left to top-right)
    for (int i = 0; i < N; i++)
    {
      if (xDiag == newQueen && yDiag == filled)
      {
        conflict = true;
        keepGoing = false;
      }
      xDiag++;
      yDiag++;

      // check overflow, if on border, stop checking diagonal
      if (xDiag > N || yDiag > N)
      {
        break;
      }
    }

    // check other diagonal (bottom-right to top-left)
    yDiag = queens.size() + 1;
    xDiag = compareQueen;

    for (int j = 0; j < N; j++)
    {
      if (xDiag == newQueen && yDiag == filled)
      {
        conflict = true;
        keepGoing = false;
      }
      xDiag--;
      yDiag++;

      // check overflow, if on border, stop checking diagonal
      if (xDiag <= 0 || yDiag > N)
      {
        break;
      }
    }

    // when stack is empty, no more checks needed
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
    // if no room
    if (topQueen == N)
    {
      return false;
    }
    // else has room
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

/* backtracks until the next free queen is found
   uses the algorithm given to us on the slide to readjust the stack */
void backtrack(int N)
{
  queens.pop();
  filled--;

  bool keepGoing = true;
  while (keepGoing)
  {
    // if space exists, then queen can be adjusted
    if (isSpace(N))
    {
      adjustQueen();
      //  if there is 1 queen left, 1 more is added to prevent segmentation faults
      if (queens.size() == 1)
      {
        filled++;
        queens.push(1);
      }
      keepGoing = false;
    }
    // else no valid room, so pop and check next entry on stack
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
