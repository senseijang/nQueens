#include <iostream>
#include <stack>

/* dummy class */
class dummy
{
private:
  int age;

public:
  dummy()
  {
    age = 0;
  };
  void sayHi()
  {
    std::cout << "Hi!\n";
  }
};

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

int getInput()
{
  bool invalidInput = true;
  int n = -1;

  while (invalidInput)
  {
    std::cout << "N: ";
    std::cin >> n;
    std::cout << std::endl;
    checkInput(n, &invalidInput);
  }
  return n;
}

int main()
{
  int n = getInput();
  std::stack<dummy> test;
  dummy d;

  test.push(d);
  test.top().sayHi();

  return 0;
}