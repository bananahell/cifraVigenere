#include "deciphererUI.h"
#include "decipherer.h"

#include <ncurses.h>
#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include <iostream>
#include <cstring>

using namespace std;

int inputMenu(string &guessKey) {

  static int currentLetter = 0;
	raw(); /* Line buffering disabled	*/
	keypad(stdscr, TRUE);		
	noecho();	

  while (true) {
    int ch = getch();
    noecho();
    switch (ch)
    {
      case KEY_UP:
        guessKey[currentLetter]++;
        if (guessKey[currentLetter] > 90) guessKey[currentLetter] = 'A';
        return currentLetter;
      case KEY_DOWN:
        guessKey[currentLetter]--;
        if (guessKey[currentLetter] < 65) guessKey[currentLetter] = 'Z';
        return currentLetter;
      case KEY_RIGHT:
        currentLetter = (currentLetter + 1) % guessKey.size();
        return currentLetter;
        // mvwprintw(stdscr, 0, 0, "%d", currentLetter);
        break;
      case KEY_LEFT:
        currentLetter = (currentLetter - 1) % guessKey.size();
        return currentLetter;
        break;
      case KEY_BACKSPACE:
        return -1;
      default:
        break;
    }
  }

}

void showTextArea(WINDOW *textArea, string text) {

  int row, col, j = 2, k = 2;
  setlocale(LC_ALL, "");
  getmaxyx(textArea,row,col);

  mvwaddch(textArea, 0, 3, ACS_VLINE);
  mvwprintw(textArea, 0, 4, " Intercepted Text "); 
  mvwaddch(textArea, 0, 22, ACS_VLINE);

  for (unsigned int i = 0; i < text.size(); i+=(col-4)) {
    if (j > row-3) break;
    string subString = text.substr(i, col-4);
    mvwprintw(textArea, j, 2, "%s", subString.c_str());
    j++; 
  }

}

void showMenu(WINDOW *menu, string guessKey, int markedLetter) {

  int row, col, baseRow, baseCol, baseColAux, lineSize, wordSize;
  getmaxyx(menu,row,col);

  mvwaddch(menu, 0, 3, ACS_VLINE);
  mvwprintw(menu, 0, 4, " Guess Key "); 
  mvwaddch(menu, 0, 15, ACS_VLINE);

  wordSize = guessKey.size();
  lineSize = wordSize > 15 ? 15 : wordSize;
  baseRow = row/4;
  baseCol = (col/2 - ((lineSize+1)*2));
  baseColAux = baseCol;

  baseColAux++;
  // mvwprintw(menu, 0, 0, "%d, %d, %d, %d", row, col, baseRow, baseColAux);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);

  for (unsigned int i = 0; i < guessKey.size(); i++) {
    mvwaddch(menu, baseRow, baseCol, ACS_VLINE);
    if (i == markedLetter) wattron(menu, COLOR_PAIR(4));
    mvwprintw(menu, baseRow, baseCol+1, " %c ", toupper(guessKey[i]));
    wattroff(menu, COLOR_PAIR(4));
    baseCol += 4;
    if ((i+1) % 15 == 0) {
      mvwaddch(menu, baseRow, baseCol, ACS_VLINE);
      baseRow +=2;
      wordSize -= lineSize;
      lineSize = wordSize > 15 ? 15 : wordSize;
      baseCol = (col/2 - ((lineSize+1)*2));
      mvwaddch(menu, baseRow, baseCol, ACS_VLINE);
    }
  }
  mvwaddch(menu, baseRow, baseCol, ACS_VLINE);

  mvwhline(menu, row-6, 2, ACS_HLINE , col-4);
  mvwprintw(menu, row-4, col/8, "[Up Arrow] Next Guess");
  mvwprintw(menu, row-4, col/4+25, "[Down Arrow] Prev Guess");
  mvwprintw(menu, row-3, col/8, "[Left Arrow] Next Letter");
  mvwprintw(menu, row-3, col/4+25, "[Right Arrow] Prev Letter");

}

int showGraph(WINDOW *graphs, map<char, double> alphabet, int drawPos, int markedLetter, double maxVal, double minVal) {

  int row, col, baseRow, baseCol;
  int baseBlockWide;

  getmaxyx(graphs,row,col);
  baseBlockWide = col < 83 ? 1 : 2;

  init_pair(3, COLOR_WHITE, COLOR_WHITE);
  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  baseRow = drawPos ? row - 3 : row/2 - 3;
  baseCol = baseBlockWide == 1 ? col/2 - 26 : col/2 - 40;
  
  int maxBarHeight = row/2 - 3;
  int minBarHeight = 1;

  mvwaddch(graphs, 0, 3, ACS_VLINE);
  mvwprintw(graphs, 0, 4, " Frequency Graphs "); 
  mvwaddch(graphs, 0, 22, ACS_VLINE);

  for (unsigned int j = 0; j < alphabet.size(); j++) 
  {
      int key = (j + (markedLetter-65))%26 + 97;
      mvwprintw(graphs, baseRow+1, baseCol, "%c", key);
      wattron(graphs, COLOR_PAIR(1));
      int barHeight = alphabet[key] == 0 ? 0 : round(minBarHeight + (maxBarHeight - minBarHeight ) * (alphabet[key] - minVal) / ( maxVal - minVal ));
      for (int i = 0; i < barHeight; i++) {
        mvwprintw(graphs, baseRow-i, baseCol, string(baseBlockWide,' ').c_str());
      }
      wattroff(graphs, COLOR_PAIR(1));
      wattron(graphs,COLOR_PAIR(3));
      for (int i = barHeight; i < maxBarHeight; i++) {
        mvwprintw(graphs, baseRow-i, baseCol, string(baseBlockWide,' ').c_str());
      }
      wattroff(graphs,COLOR_PAIR(3));
      baseCol += baseBlockWide + 1;
  }

  return baseCol;

}

string vigDecipherUI(string originalMsg, int keySize, vector<vector<double>> freqTable, string language) {

  int row, col, markedLetter = 0; 
  unsigned int i;

  map<char, double> ENGLISH_ALPHABET{
    {'a', 8.167}, {'b', 1.492}, {'c', 2.782}, {'d', 4.253}, {'e', 12.702},
    {'f', 2.228}, {'g', 2.015}, {'h', 6.094}, {'i', 6.966}, {'j', 0.153},
    {'k', 0.772}, {'l', 4.025}, {'m', 2.406}, {'n', 6.749}, {'o', 7.507},
    {'p', 1.929}, {'q', 0.095}, {'r', 5.987}, {'s', 6.327}, {'t', 9.056},
    {'u', 2.758}, {'v', 0.978}, {'w', 2.36},  {'x', 0.15},  {'y', 1.974},
    {'z', 0.074}};

  std::map<char, double> PORTUGUESE_ALPHABET{
    {'a', 16.119}, {'e', 13.357}, {'o', 10.706}, {'s', 6.805}, {'r', 6.53},
    {'i', 6.318},  {'d', 4.992},  {'m', 4.738},  {'n', 4.446}, {'t', 4.336},
    {'c', 4.412},  {'u', 3.872},  {'l', 2.779},  {'p', 2.523}, {'v', 1.575},
    {'g', 1.303},  {'q', 1.204},  {'b', 1.043},  {'f', 1.023}, {'h', 0.781},
    {'z', 0.47},   {'j', 0.397},  {'x', 0.253},  {'w', 0.037}, {'k', 0.015},
    {'y', 0.006}};

  map<char, double> KEY_FREQUENCY{
    {'a', 8.167}, {'b', 1.492}, {'c', 2.782}, {'d', 4.253}, {'e', 12.702},
    {'f', 2.228}, {'g', 2.015}, {'h', 6.094}, {'i', 6.966}, {'j', 0.153},
    {'k', 0.772}, {'l', 4.025}, {'m', 2.406}, {'n', 6.749}, {'o', 7.507},
    {'p', 1.929}, {'q', 0.095}, {'r', 5.987}, {'s', 6.327}, {'t', 9.056},
    {'u', 2.758}, {'v', 0.978}, {'w', 2.36},  {'x', 0.15},  {'y', 1.974},
    {'z', 0.074}};

  string guessKey(keySize, 'A');
  vector<string> decipheredMessages;

  setlocale(LC_ALL, "");

  initscr();
  getmaxyx(stdscr,row,col);

  if(has_colors() == FALSE){
    endwin();
    printf("Seu terminal não suporta cores.\n");
    exit(0);
  }
  start_color(); // Inicia as cores
  init_pair(2, COLOR_BLACK, COLOR_WHITE);

  WINDOW *graphs = newwin(row-20, col/2 + 1, 1, 12);
  WINDOW *menu = newwin(row-20, col/2 - 21, 1, col/2 + 10);
  WINDOW *textArea = newwin(18, col - 24, row-19, 12);

  wbkgd(graphs, COLOR_PAIR(2));
  wbkgd(menu, COLOR_PAIR(2));
  wbkgd(textArea, COLOR_PAIR(2));
  refresh();

  box(graphs, 0, 0);
  box(menu, 0, 0);
  box(textArea, 0, 0);

  while (true) {
    decipheredMessages = decipherWithKey(originalMsg, guessKey);
    for (int i = 0; i < freqTable[markedLetter].size(); i++) {
      KEY_FREQUENCY[i+97] = freqTable[markedLetter][i];
    }
    wrefresh(graphs);

    if (language == "pt") 
      showGraph(graphs,PORTUGUESE_ALPHABET,0,'A',16.119,0.006);
    else 
      showGraph(graphs,ENGLISH_ALPHABET,0,'A',12.702,0.074);
    showGraph(graphs,KEY_FREQUENCY,1,guessKey[markedLetter], 
             *max_element(freqTable[markedLetter].begin(), freqTable[markedLetter].end()), 
             *min_element(freqTable[markedLetter].begin(), freqTable[markedLetter].end()));

    showMenu(menu,guessKey,markedLetter);
    showTextArea(textArea, decipheredMessages[1]);

    wrefresh(menu);
    wrefresh(graphs);
    wrefresh(textArea);
    markedLetter = inputMenu(guessKey);
    if (markedLetter == -1) break;
    // i = markedLetter;
  }
  endwin();

  return guessKey;

}
