#ifndef USER_H
#define USER_H

#include "utils.h"
#include <iostream>
#include <string>

using namespace std;

// ============================================
// USER BASE CLASS (Abstract)
// ============================================
// Demonstrates: Inheritance, Polymorphism, Encapsulation

class User {
protected:
  int id;
  string name;
  string email;
  string password;
  string role; // "customer" or "admin"

public:
  // Constructor
  User(int id, const string &name, const string &email, const string &password,
       const string &role);

  // Virtual destructor for proper polymorphism
  virtual ~User() = default;

  // ============================================
  // PURE VIRTUAL FUNCTIONS (Must be implemented by derived classes)
  // ============================================
  virtual void displayMenu() = 0; // Makes User abstract

  // ============================================
  // VIRTUAL FUNCTIONS (Can be overridden)
  // ============================================
  virtual void displayInfo() const;
  virtual bool authenticate(const string &inputPassword) const;

  // ============================================
  // GETTERS (Encapsulation)
  // ============================================
  int getId() const { return id; }
  string getName() const { return name; }
  string getEmail() const { return email; }
  string getPassword() const { return password; }
  string getRole() const { return role; }

  // ============================================
  // SETTERS (Encapsulation with validation)
  // ============================================
  void setName(const string &newName);
  void setEmail(const string &newEmail);
  void setPassword(const string &newPassword);
};

#endif
