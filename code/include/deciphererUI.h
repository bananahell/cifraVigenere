#ifndef DECIPHERER_UI
#define DECIPHERER_UI

#include <ncurses.h>
#include <map>
#include <string>
#include <vector>

int inputMenu(std::vector<char> &guessWord);
void showTextArea(WINDOW *textArea, std::string text);
void showMenu(WINDOW *menu, std::vector<char> guessWord, unsigned int markedLetter);
int showGraph(WINDOW *graphs, std::map<char, double> alphabet, int drawPos, int markedLetter, double maxVal, double minVal);
std::string vigDecipherUI(std::string originalMsg, int keySize,  std::vector<std::vector<double>> freqTable,  std::string language);

#endif  // DECIPHERER_UI