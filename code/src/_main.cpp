#include <iostream>
#include <string>

#include "encoder.h"

using namespace std;

int main() {
  string message = "copa do mundo";
  string key = "senha";
  cout << "message: " << message << endl;
  cout << "key: " << key << endl;
  cout << "encoded message: " << encode(message, key) << endl;
  return 0;
}
