#include "../include/utils.h"
#include <cstdlib> // for system()
#include <iostream>
#include <map>
#include <unistd.h> // for sleep on Unix/Mac

using namespace std;

// ============================================
// ANSI COLOR CODES
// ============================================

string Utils::colorText(const string &text, const string &color,
                        const string &bgColor, const string &style) {
  // ANSI escape codes for text colors
  map<string, string> colors = {{"red", "\033[31m"},     {"green", "\033[32m"},
                                {"yellow", "\033[33m"},  {"blue", "\033[34m"},
                                {"magenta", "\033[35m"}, {"cyan", "\033[36m"},
                                {"white", "\033[37m"},   {"reset", "\033[0m"}};

  // ANSI escape codes for background colors
  map<string, string> bgColors = {
      {"black", "\033[40m"},  {"red", "\033[41m"},  {"green", "\033[42m"},
      {"yellow", "\033[43m"}, {"blue", "\033[44m"}, {"magenta", "\033[45m"},
      {"cyan", "\033[46m"},   {"white", "\033[47m"}};

  // ANSI escape codes for styles
  map<string, string> styles = {{"bold", "\033[1m"},
                                {"dim", "\033[2m"},
                                {"underline", "\033[4m"},
                                {"italic", "\033[3m"}};

  string result = "";

  // Apply text color
  if (colors.find(color) != colors.end()) {
    result += colors[color];
  }

  // Apply background color
  if (bgColors.find(bgColor) != bgColors.end()) {
    result += bgColors[bgColor];
  }

  // Apply style
  if (styles.find(style) != styles.end()) {
    result += styles[style];
  }

  // Add the actual text
  result += text;

  // Reset all formatting
  result += "\033[0m";

  return result;
}

// ============================================
// DISPLAY FUNCTIONS
// ============================================

void Utils::showMainHeader(const string &title) {
  string border = string(50, '=');

  cout << colorText(border, "white", "blue") << endl;

  // Center the title
  int padding = (50 - title.length()) / 2;
  string centeredTitle = string(padding, ' ') + title;

  cout << colorText(centeredTitle, "white", "blue", "bold") << endl;
  cout << colorText(border, "white", "blue") << endl;
  cout << endl;
}

void Utils::showSubHeader(const string &subtitle) {
  string border = string(50, '-');

  cout << colorText(border, "cyan", "", "dim") << endl;

  // Center the subtitle
  int padding = (50 - subtitle.length()) / 2;
  string centeredTitle = string(padding, ' ') + subtitle;

  cout << colorText(centeredTitle, "cyan", "", "bold") << endl;
  cout << colorText(border, "cyan", "", "dim") << endl;
  cout << endl;
}

void Utils::clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void Utils::pauseScreen() {
  cout << colorText("\nPress Enter to continue...", "yellow");
  cin.ignore();
  cin.get();
}

void Utils::showLoading(const string &message, int seconds) {
  cout << colorText(message, "cyan");

  for (int i = 0; i < seconds * 2; i++) {
    cout << colorText(".", "cyan") << flush;
    usleep(500000); // Sleep for 0.5 seconds (500,000 microseconds)
  }

  cout << endl;
}

// ============================================
// INPUT VALIDATION FUNCTIONS (BASIC VERSIONS)
// ============================================
// TODO: Implement full validation in next phase

int Utils::getIntInput(const string &prompt, int min, int max) {
  // Placeholder - will implement full validation later
  int value;
  cout << prompt;
  cin >> value;
  return value;
}

double Utils::getDoubleInput(const string &prompt, double min, double max) {
  // Placeholder - will implement full validation later
  double value;
  cout << prompt;
  cin >> value;
  return value;
}

string Utils::getStringInput(const string &prompt) {
  // Placeholder - will implement full validation later
  string value;
  cout << prompt;
  cin >> value;
  return value;
}

int Utils::getMenuChoice(const string &prompt, int minOption, int maxOption) {
  // Placeholder - will implement full validation later
  int choice;
  cout << colorText(prompt, "yellow");
  cin >> choice;
  return choice;
}
