#include <iostream>
#include <stack>

/* Function Prototpyes */
void checkInput(int N, bool *invalidInput);
bool isConflict(std::stack<int> queens, int N);
void solution();
void placeNewQueen(std::stack<int> queens, int filled);
bool isSpace(std::stack<int> queens, int N);
void adjustQueen(std::stack<int> queens);
void backtrack(std::stack<int> queens, int filled, int N);
void printBoard(std::stack<int> queens, int N);

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

  int filled = 1;
  std::stack<int> queens;

  queens.push(1);

  while (filled != N)
  {
    filled++;
    std::cout << "1st eval: " << !isConflict(queens, N) << "\n";
    if (!isConflict(queens, N))
    {
      placeNewQueen(queens, filled);
    }
    else if (isSpace(queens, N))
    {
      adjustQueen(queens);
    }
    else
    {
      backtrack(queens, filled, N);
    }
  }

  printBoard(queens, N);

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

bool isConflict(std::stack<int> queens, int N)
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
    usedQueens.pop();

    // check columns
    if (newQueen == compareQueen)
    {
      std::cout << "columns\n";
      conflict = true;
      keepGoing = false;
    }

    // check diagonals
    int yDiag = N - 1;
    int xDiag = compareQueen;

    // primary diagonal
    for (int i = 0; i < N; i++)
    {
      if (xDiag == newQueen && yDiag == N)
      {
        std::cout << "primary diagonal\n";
        conflict = true;
        keepGoing = false;
      }
      xDiag++;
      yDiag++;
    }

    // other diagonal
    yDiag = N - 1;
    xDiag = compareQueen;

    for (int j = 0; j < N; j++)
    {
      if (xDiag == newQueen && yDiag == N)
      {
        std::cout << "other diagonal\n";
        conflict = true;
        keepGoing = false;
      }
      xDiag--;
      yDiag++;
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
  std::cout << conflict << std::endl;
  return conflict;
}

void placeNewQueen(std::stack<int> queens, int filled)
{
  queens.push(1);
  filled++;
}

bool isSpace(std::stack<int> queens, int N)
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

void adjustQueen(std::stack<int> queens)
{
  if (queens.size() != 0)
  {
    int topQueen = queens.top();
    queens.pop();
    topQueen++;
    queens.push(topQueen);
  }
}

void backtrack(std::stack<int> queens, int filled, int N)
{
  queens.pop();
  filled--;

  bool keepGoing = true;
  while (keepGoing)
  {
    if (isSpace(queens, N))
    {
      adjustQueen(queens);
      keepGoing = false;
    }
    else
    {
      queens.pop();
      filled--;
    }
  }
}

void printBoard(std::stack<int> queens, int N)
{
  std::cout << "printing attempted " << queens.size();
  if (queens.size() != 0)
  {
    for (int i = 0; i < N; i++)
    {
      if (queens.top() == i)
      {
        std::cout << "Q";
      }
      else
      {
        std::cout << "0";
      }
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  queens.pop();
}
