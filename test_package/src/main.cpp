#include <iostream>
#include <substrate/substrate.h>

int main(int argc, char** argv)
{
   if (substrate::development::make_account_alice() != nullptr)
      return 0;
   return -1;
}
