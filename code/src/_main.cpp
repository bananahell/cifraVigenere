#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

#include "decipherer.h"
#include "deciphererUI.h"
#include "encoder.h"

#define USER_QUIT 0
#define USER_GET_PASS_SIZE 1
#define USER_GET_BEST_PASS 2
#define USER_USE_OWN_PASS 3

using namespace std;

/*

-fd -> Processo de encontrar a chave e decifrar
-d -> Processo de decifrar a mensagem ja sabendo a chave
-c -> Processo de cifrar uma mensagem

-arq.txt -> arquivo com a mensagem

-en -> Mensagem em ingles
-pt -> Mensagem em portuges

*/

void findAndDecipher(string message, string language) {

  int keySize;
  string formatedMsg;
  map<int, int>::iterator it;
  vector<vector<double>> freqTable;

  cout << "ENCONTRAR SENHA E DECODIFICAR A MENSAGEM" << endl;
  // Formatar message
  for (int i = 0; i < message.size(); i++) {
    char letter = toupper(message[i]);
    if (letter >= 'A' && letter <= 'Z') {
      formatedMsg.push_back(letter);
    }
  }
  cout << "FORMATED STRING: \n";
  cout << formatedMsg << endl;

  map<int, int> sizeLikeliness = getMostLikelyPassSize(formatedMsg);
  cout << "Quantidade de divisores, ate 24, das distancias entre as substrings:" << endl;
  for (it = sizeLikeliness.begin(); it != sizeLikeliness.end(); ++it) {
    cout << "(" << it->first << ", " << it->second << ")" << endl;
  }

  cout << "Palpite de tamanho de chave: ";
  cin >> keySize;

  freqTable = getEncodedMsgFreq(keySize, formatedMsg);
  vigDecipherUI(message, keySize, freqTable, language);

}

void decipher(string message) {
  string key;

  cout << "DECODIFICACAO DE MENSAGEM" << endl;
  cout << "Insira a chave de decodificacao: ";
  cin >> key;

  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "Mensagem codificada: " << endl << message << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;

  vector<string> decipheredMessages = decipherWithKey(message, key);
  cout << "Mensagem decodificada: " << endl << decipheredMessages[0] << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
}

void cipher(string message) {
  string key;

  cout << "CODIFICACAO DE MENSAGEM" << endl;
  cout << "Insira a chave de codificacao: ";
  cin >> key;

  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
  cout << "Mensagem original: " << endl << message << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;

  vector<string> encodedMessages = encode(message, key);
  cout << "Mensagem codificada: " << endl << encodedMessages[1] << endl;
  cout << "----------------------------------------";
  cout << "----------------------------------------" << endl;
}

int main(int argc, char *argv[]) {

  string message;

  if (argc == 1 || argc > 4) {
    cout << "Numero de argumentos invalidos." << endl;
    return 0;
  }
  ifstream messageFile(argv[2]);
  if (messageFile.is_open()) {
    stringstream buffer;
    buffer << messageFile.rdbuf();
    message = buffer.str();
  } else {
    cout << "Arquivo nao abriu ou nao existe" << endl;
    return 0;
  }
  if (strcmp(argv[1], "-fd") == 0) {
    if (strcmp(argv[3], "-pt") != 0 && strcmp(argv[3], "-en") != 0) {
      cout << "Lingua invalida." << endl;
      return 0;      
    }
    findAndDecipher(message,argv[3]);
  } else if (strcmp(argv[1], "-d") == 0) {
    decipher(message);
  } else if (strcmp(argv[1], "-c") == 0) {
    cipher(message);
  } else {
    cout << "Funcao inexistente." << endl;
    return 0;
  }

  return 0;

}