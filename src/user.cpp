#include "../include/user.h"
#include <iostream>

using namespace std;

// ============================================
// CONSTRUCTOR
// ============================================

User::User(int id, const string &name, const string &email,
           const string &password, const string &role)
    : id(id), name(name), email(email), password(password), role(role) {}

// ============================================
// VIRTUAL FUNCTIONS
// ============================================

void User::displayInfo() const {
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "yellow") << endl;
  cout << Utils::colorText("  User Information", "yellow", "", "bold") << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "yellow") << endl;
  cout << "  ID:    " << Utils::colorText(to_string(id), "white", "", "bold")
       << endl;
  cout << "  Name:  " << Utils::colorText(name, "white", "", "bold") << endl;
  cout << "  Email: " << Utils::colorText(email, "yellow") << endl;
  cout << "  Role:  " << Utils::colorText(role, "yellow") << endl;
  cout << Utils::colorText("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━", "yellow") << endl;
}

bool User::authenticate(const string &inputPassword) const {
  return password == inputPassword;
}

// ============================================
// SETTERS WITH VALIDATION
// ============================================

void User::setName(const string &newName) {
  if (!newName.empty()) {
    name = newName;
  }
}

void User::setEmail(const string &newEmail) {
  // Basic email validation - contains @
  if (newEmail.find('@') != string::npos) {
    email = newEmail;
  }
}

void User::setPassword(const string &newPassword) {
  // Password must be at least 6 characters
  if (newPassword.length() >= 6) {
    password = newPassword;
  }
}
