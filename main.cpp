#include <iostream>
#include <stack>

void checkInput(int n, bool *invalidInput)
{
  if (n == 2 || n == 3)
  {
    std::cout << "N-Queens is not possible with " << n << ". Please enter a different number\n";
  }
  else
  {
    *invalidInput = false;
    std::cout << "N-value: " << n << std::endl;
  }
}

int main()
{
  // Start with getting N
  bool invalidInput = true;
  int n = -1;

  while (invalidInput)
  {
    std::cout << "N: ";
    std::cin >> n;
    std::cout << std::endl;
    checkInput(n, &invalidInput);
  }

  return 0;
}