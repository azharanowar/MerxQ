#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

// Base custom exception
class MerxQException : public exception {
protected:
  string message;

public:
  MerxQException(const string &msg) : message(msg) {}
  const char *what() const noexcept override { return message.c_str(); }
};

// Invalid input from user
class InvalidInputException : public MerxQException {
public:
  InvalidInputException(const string &msg = "Invalid input")
      : MerxQException(msg) {}
};

// Product not found
class ProductNotFoundException : public MerxQException {
public:
  ProductNotFoundException(const string &msg = "Product not found")
      : MerxQException(msg) {}
};

// Not enough stock
class InsufficientStockException : public MerxQException {
public:
  InsufficientStockException(const string &msg = "Insufficient stock")
      : MerxQException(msg) {}
};

// User not found
class UserNotFoundException : public MerxQException {
public:
  UserNotFoundException(const string &msg = "User not found")
      : MerxQException(msg) {}
};

// Wrong password or email
class AuthenticationException : public MerxQException {
public:
  AuthenticationException(const string &msg = "Authentication failed")
      : MerxQException(msg) {}
};

// File read/write error
class FileException : public MerxQException {
public:
  FileException(const string &msg = "File operation failed")
      : MerxQException(msg) {}
};

#endif
