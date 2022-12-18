#include "decipherer.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>

// #include <ncurses.h>

#define MAX_DIVIDER 25

using namespace std;

std::map<char, double> ENGLISH_ALPHABET{
    {'a', 8.167}, {'b', 1.492}, {'c', 2.782}, {'d', 4.253}, {'e', 12.702},
    {'f', 2.228}, {'g', 2.015}, {'h', 6.094}, {'i', 6.966}, {'j', 0.153},
    {'k', 0.772}, {'l', 4.025}, {'m', 2.406}, {'n', 6.749}, {'o', 7.507},
    {'p', 1.929}, {'q', 0.095}, {'r', 5.987}, {'s', 6.327}, {'t', 9.056},
    {'u', 2.758}, {'v', 0.978}, {'w', 2.36},  {'x', 0.15},  {'y', 1.974},
    {'z', 0.074}};

/*
std::map<char, double> PORTUGUESE_ALPHABET{
    {'a', 14.634}, {'e', 12.57}, {'o', 9.735}, {'s', 6.805}, {'r', 6.53},
    {'i', 6.186},  {'d', 4.992}, {'m', 4.738}, {'n', 4.446}, {'t', 4.336},
    {'c', 3.882},  {'u', 3.639}, {'l', 2.779}, {'p', 2.523}, {'v', 1.575},
    {'g', 1.303},  {'q', 1.204}, {'b', 1.043}, {'f', 1.023}, {'h', 0.781},
    {'ã', 0.733},  {'ô', 0.635}, {'â', 0.562}, {'ç', 0.530}, {'z', 0.47},
    {'ê', 0.45},   {'j', 0.397}, {'é', 0.337}, {'ó', 0.296}, {'x', 0.253},
    {'ú', 0.207},  {'í', 0.132}, {'á', 0.118}, {'à', 0.072}, {'õ', 0.04},
    {'w', 0.037},  {'ü', 0.026}, {'k', 0.015}, {'y', 0.006}};
*/

std::map<char, double> PORTUGUESE_ALPHABET_NO_SYMBOL{
    {'a', 16.119}, {'e', 13.357}, {'o', 10.706}, {'s', 6.805}, {'r', 6.53},
    {'i', 6.318},  {'d', 4.992},  {'m', 4.738},  {'n', 4.446}, {'t', 4.336},
    {'c', 4.412},  {'u', 3.872},  {'l', 2.779},  {'p', 2.523}, {'v', 1.575},
    {'g', 1.303},  {'q', 1.204},  {'b', 1.043},  {'f', 1.023}, {'h', 0.781},
    {'z', 0.47},   {'j', 0.397},  {'x', 0.253},  {'w', 0.037}, {'k', 0.015},
    {'y', 0.006}};

map<int, int> getMostLikelyPassSize(string encodedMessage) {
  map<string, int> subStringFreqTemp;
  map<string, int>::iterator it;
  map<string, vector<int>>::iterator itPos;
  map<string, int> subStringFreq;
  map<string, vector<int>> subStringPos;
  map<int, int> sizeLikeliness;
  string subString;
  int subStringDistance, smallerSubStringDist = 0;

  for (int subSize = 3; subSize < 6; subSize++) {
    for (unsigned i = 0; i < encodedMessage.length() - subSize; i++) {
      subString = encodedMessage.substr(i, subSize);
      if (subStringFreqTemp.find(subString) != subStringFreqTemp.end()) {
        subStringFreqTemp[subString]++;
      } else {
        subStringFreqTemp.insert({subString, 0});
        subStringPos.insert({subString, {}});
      }
      subStringPos[subString].push_back(i);
    }
  }

  for (it = subStringFreqTemp.begin(); it != subStringFreqTemp.end(); ++it) {
    if (it->second != 0) {
      subStringFreq.insert({it->first, it->second});
    } else {
      subStringPos.erase(it->first);
    }
  }

  for (int i = 2; i < MAX_DIVIDER; i++) {
    sizeLikeliness.insert({i, 0});
  }

  for (itPos = subStringPos.begin(); itPos != subStringPos.end(); ++itPos) {
    smallerSubStringDist = 0;
    for (unsigned i = 1; i < itPos->second.size(); i++) {
      subStringDistance = itPos->second.at(i) - itPos->second.at(i - 1);
      if (subStringDistance < smallerSubStringDist || smallerSubStringDist == 0) {
        smallerSubStringDist = subStringDistance;
      }
    }
    for (int j = 2; j < MAX_DIVIDER; j++) {
      if (smallerSubStringDist % j == 0) {
        if (itPos->first == "NAUL") {
          cout << "NAUL: " << smallerSubStringDist << endl;
          cout << "J: " << j << endl;
        }
        sizeLikeliness[j]++;
      }
    }
  }

  // cout << "subStringFreq.size() = " << subStringFreq.size()
  //      << "; subStringPos.size() = " << subStringPos.size() << endl
  //      << endl;
  cout << "Tabela das substrings retiradas da mensagem, de 3 a 6 caracteres, e suas frequencias:" << endl;
  for (it = subStringFreq.begin(); it != subStringFreq.end(); ++it) {
    cout << "(subString - freq - pos): (" << it->first << " -\t" << it->second
         << " -\t";
    for (unsigned i = 0; i < subStringPos[it->first].size(); i++) {
      cout << subStringPos[it->first].at(i);
      if (i != subStringPos[it->first].size() - 1) {
        cout << ",\t";
      }
    }
    cout << ")" << endl;
  }
  cout << endl;

  return sizeLikeliness;
}

vector<vector<double>> getEncodedMsgFreq(int keySize, string encodedMessage) {

  vector<vector<double>> freqTable(keySize, vector<double>(26, 0)); //keySize colunas e tamanho do alfabeto de linhas

  for (unsigned int i = 0; i < encodedMessage.size(); i++) {
    freqTable[i%keySize][encodedMessage[i]-65]++;
  }

  for (auto& freqVector : freqTable) {
    int sumFreq = accumulate(freqVector.begin(), freqVector.end(), 0.0);
    for (unsigned int i = 0; i < freqVector.size(); i++) {
      freqVector[i] = (freqVector[i] / sumFreq)*100;
    } 
  }

  // cout << endl;
  // for (auto& freqVector : freqTable) {
  //   cout << accumulate(freqVector.begin(), freqVector.end(), 0.0) << endl;
  //   for (auto& item : freqVector) {
  //     cout << item << " ";
  //   }
  //   cout << endl;
  // }

  return freqTable;

}

vector<string> decipherWithKey(const string& encodedSymbol, const string& key) {
  vector<string> decipheredMessages;
  decipheredMessages.push_back("");
  decipheredMessages.push_back("");
  int rawIndex = 0;
  for (unsigned i = 0; i < encodedSymbol.size(); i++) {
    char letter = toupper(encodedSymbol.at(i));
    if (letter >= 'A' || letter >= 'Z') {
      letter = vigDecipher(letter, key, rawIndex);
      decipheredMessages.at(0).append(string(1, letter));
      rawIndex++;
    }
    decipheredMessages.at(1).append(string(1, letter));
  }
  return decipheredMessages;
}

char vigDecipher(char oldLetter, const string& key, int messageIndex) {
  char keyLetter = key.at(messageIndex % key.length());
  if (keyLetter >= 'a' && keyLetter <= 'z') {
    keyLetter -= LOWER_TO_UPPER;
  }
  int keyLetterNum = keyLetter - 'A';
  int newLetterNum = (oldLetter - 'A') - (keyLetterNum);
  if (newLetterNum < 0) {
    newLetterNum += ALPHABET_SIZE;
  }
  return newLetterNum + 'A';
}
