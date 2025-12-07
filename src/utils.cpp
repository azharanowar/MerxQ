#include "../include/utils.h"
#include <cstdlib> // for system()
#include <iostream>
#include <limits> // for numeric_limits
#include <map>
#include <unistd.h> // for sleep on Unix/Mac

using namespace std;

// ============================================
// ANSI COLOR CODES
// ============================================

string Utils::colorText(const string &text, const string &color,
                        const string &bgColor, const string &style) {
  // ANSI escape codes for text colors
  map<string, string> colors = {{"red", "\033[31m"},    {"green", "\033[32m"},
                                {"yellow", "\033[33m"}, {"blue", "\033[34m"},
                                {"yellow", "\033[35m"}, {"yellow", "\033[36m"},
                                {"white", "\033[37m"},  {"reset", "\033[0m"}};

  // ANSI escape codes for background colors
  map<string, string> bgColors = {
      {"black", "\033[40m"},  {"red", "\033[41m"},  {"green", "\033[42m"},
      {"yellow", "\033[43m"}, {"blue", "\033[44m"}, {"yellow", "\033[45m"},
      {"yellow", "\033[46m"}, {"white", "\033[47m"}};

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

  // Fixed padding for emoji titles (emojis take 2 char width)
  int visualWidth = 23;
  int leftPadding = (50 - visualWidth) / 2;
  int rightPadding = 50 - visualWidth - leftPadding;
  string centeredTitle =
      string(leftPadding, ' ') + title + string(rightPadding, ' ');

  cout << colorText(centeredTitle, "white", "blue", "bold") << endl;
  cout << colorText(border, "white", "blue") << endl;
  cout << endl;
}

void Utils::showSubHeader(const string &subtitle) {
  string border = string(50, '-');

  cout << colorText(border, "yellow", "", "dim") << endl;

  // Center the subtitle
  int padding = (50 - subtitle.length()) / 2;
  string centeredTitle = string(padding, ' ') + subtitle;

  cout << colorText(centeredTitle, "yellow", "", "bold") << endl;
  cout << colorText(border, "yellow", "", "dim") << endl;
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
  cin.get();
}

void Utils::showLoading(const string &message, int seconds) {
  cout << colorText(message, "yellow");

  for (int i = 0; i < seconds * 2; i++) {
    cout << colorText(".", "yellow") << flush;
    usleep(500000); // Sleep for 0.5 seconds (500,000 microseconds)
  }

  cout << endl;
}

// ============================================
// INPUT VALIDATION FUNCTIONS
// ============================================

int Utils::getIntInput(const string &prompt, int min, int max) {
  int value;
  while (true) {
    cout << prompt;
    if (cin >> value) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
      if (value >= min && value <= max) {
        return value;
      }
      cout << colorText("Please enter a number between " + to_string(min) +
                            " and " + to_string(max),
                        "yellow")
           << endl;
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << colorText("Invalid input. Please enter a number.", "red") << endl;
    }
  }
}

double Utils::getDoubleInput(const string &prompt, double min, double max) {
  double value;
  while (true) {
    cout << prompt;
    if (cin >> value) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
      if (value >= min && value <= max) {
        return value;
      }
      cout << colorText("Please enter a valid amount.", "yellow") << endl;
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << colorText("Invalid input. Please enter a number.", "red") << endl;
    }
  }
}

string Utils::getStringInput(const string &prompt) {
  string value;
  cout << prompt;
  getline(cin, value);
  return value;
}

int Utils::getMenuChoice(const string &prompt, int minOption, int maxOption) {
  int choice;
  while (true) {
    cout << colorText(prompt, "yellow");
    if (cin >> choice) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
      if (choice >= minOption && choice <= maxOption) {
        return choice;
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}
