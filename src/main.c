#include <pebble.h>
int total = 100;

// Global add() function
int add(int x) {
  x = x + 3;
  return x;
}

int outer() {
  // total variable is local to the outer() function, the nested functions, AND the nested nested functions (and so on)
  static int total = 1;
  
  // A nested function with a nested function
  //  Note: this function returns: 4
  int number() {
    int three() {          // You can nest functions inside nested functions!
      return 3;
      //return total;      // This works, too.  Nested nested functions still have access to variables scoped above it.
    }
    int number() {         // Nested functions can even have the same name, but this can get confusing...
      return 1;
    }
    return number() + three();  // Not recurion: Calls the nested function inside it with the same name.
  }
  
  
  total = total + 1;       // You can put statements inbetween function declarations
  
  
  // Nested add() function
  //   It doesn't have an argument, showing how it differs from the global add() function
  //   CloudPebble's linter flags this line since it thinks functions aren't allowed here (which is normally right)
  int add() {
    // int number;          // WARNING: If you make this variable, you won't be able to call the number() function
    int three;              // <-- this variable is local only to this nested add() function
    static int four;        // <-- this one, too, even if it is static
    // four = three() + 1;  // ERROR: You cannot access functions nested inside other functions scoped above this
    four = number();        // you can call other nested functions (but not the nested nested functions, except ones nested inside this function)
    three = four - 1;       
    total = total + three;  // this is the variable total which is local to outer()
    return total;
  }
  
  // return four;          // ERROR: Can't access variables inside nested functions
  int q = add(1000);       // Oddly, you can still call global functions which have the same name as nested functions
  int r = add() + add(3);  // You can even mix nested functions and global functions.  I think I'm staring to get confused.
  
  return r;
}


int main(void) {
  printf("%d", outer());     // 19
  printf("%d", outer());     // 39
  printf("%d", outer());     // 59
  // printf("%d", number()); //       ERROR: Can't call nested function externally
  printf("%d", add(total));  // 103   Calls global add() function (notice it has an argument) with global total variable
  // printf("%d", add());    //       ERROR: Missing arguments for global function (nested function is out of scope)
  printf("%d", total);       // 100
}