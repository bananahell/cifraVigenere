#include "encoder.h"

using namespace std;

string encode(const string& message, const string& key) {
  string encodedMessage = message;
  int messageIndex = 0;
  for (unsigned i = 0; i < message.length(); i++) {
    char letter = message.at(i);
    if (letter >= 'a' && letter <= 'z') {
      letter -= LOWER_TO_UPPER;
    }
    if (letter >= 'A' && letter <= 'Z') {
      letter = vigEncode(letter, key, messageIndex);
      encodedMessage.at(i) = letter;
      messageIndex++;
    }
  }
  return encodedMessage;
}

char vigEncode(char oldLetter, const string& key, int messageIndex) {
  char keyLetter = key.at(messageIndex % key.length());
  if (keyLetter >= 'a' && keyLetter <= 'z') {
    keyLetter -= LOWER_TO_UPPER;
  }
  int keyLetterNum = keyLetter - 'A';
  int newLetterNum = (oldLetter - 'A') + (keyLetterNum);
  if (newLetterNum >= ALPHABET_SIZE) {
    newLetterNum -= ALPHABET_SIZE;
  }
  return newLetterNum + 'A';
}
