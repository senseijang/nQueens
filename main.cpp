#include <iostream>
#include <stack>

/* Function Prototpyes */
void checkInput(int N, bool *invalidInput);
bool isConflict();
void solution();
void placeNewQueen();
bool roomExists();
void adjustQueen();
void backtrack();
void printBoard();

int main()
{
  // Start with getting N
  bool invalidInput = true;
  int N;

  while (invalidInput)
  {
    std::cout << "N: ";
    std::cin >> N;
    std::cout << std::endl;
    checkInput(N, &invalidInput);
  }

  // initial an array based on N
  // int board[N][N] = {};
  int filled = 1;
  std::stack<int> queens;

  while (filled != N)
  {
    if (!isConflict())
    {
      placeNewQueen();
    }
    else if (roomExists())
    {
      adjustQueen();
    }
    else
    {
      backtrack();
    }
  }

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
