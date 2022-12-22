#include <iostream>
#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

// Function to hash a password using SHA-256
std::string hash_password(const std::string& password) {
  // TODO: Implement password hashing using SHA-256
  return password;  // Dummy return for now
}

// Function to check if a password is strong enough
bool is_strong_password(const std::string& password) {
  // TODO: Implement password strength check
  return true;  // Dummy return for now
}

// Function to send an email
void send_email(const std::string& to, const std::string& subject, const std::string& message) {
  // TODO: Implement email sending
  std::cout << "Sending email to " << to << " with subject '" << subject << "' and message '" << message << "'" << std::endl;
}

int main() {
  // Create a map to store the user accounts
  std::map<std::string, std::pair<std::string, std::string>> accounts;

  while (true) {
    std::cout << "Enter 'signup' to create a new account, 'login' to log in, 'forgot' to reset your password, or 'change' to change your password: ";
    std::string action;
    std::cin >> action;

    if (action == "signup") {
      std::cout << "Enter your email address: ";
      std::string email;
      std::cin >> email;

      std::cout << "Enter a username: ";
      std::string username;
      std::cin >> username;

      if (accounts.count(username) > 0) {
        std::cout << "Error: that username is already taken. Try again." << std::endl;
        continue;
      }

      std::cout << "Enter a password: ";
      std::string password;
      std::cin >> password;

      if (!is_strong_password(password)) {
        std::cout << "Error: that password is not strong enough. Try again." << std::endl;
        continue;
      }

      // Generate a random recovery code
      std::string recovery_code;
      std::random_device rd;
      std::mt19937 generator(rd());
      std::uniform_int_distribution<int> dist(10000, 99999);
      for (int i = 0; i < 5; ++i) {
        recovery_code += std::to_string(dist(generator));
      }

      // Hash the password
      password = hash_password(password);

      // Add the new account to the map
      accounts[username] = {password, recovery_code};

      // Send the recovery code to the user's email address
           // Send the recovery code to the user's email address
      send_email(email, "Your account recovery code", "Your recovery code is: " + recovery_code);

      std::cout << "Account created successfully! Check your email for your recovery code." << std::endl;
    } else if (action == "login") {
      std::cout << "Enter your username: ";
      std::string username;
      std::cin >> username;

      if (accounts.count(username) == 0) {
        std::cout << "Error: that username does not exist. Try again." << std::endl;
        continue;
      }

      std::cout << "Enter your password: ";
      std::string password;
      std::cin >> password;

      if (accounts[username].first != hash_password(password)) {
        std::cout << "Error: incorrect password. Try again." << std::endl;
        continue;
      }

      std::cout << "Login successful!" << std::endl;
      break;
    } else if (action == "forgot") {
      std::cout << "Enter your username: ";
      std::string username;
      std::cin >> username;

      if (accounts.count(username) == 0) {
        std::cout << "Error: that username does not exist. Try again." << std::endl;
        continue;
      }

      std::cout << "Enter your recovery code: ";
      std::string recovery_code;
      std::cin >> recovery_code;

      if (accounts[username].second != recovery_code) {
        std::cout << "Error: invalid recovery code. Try again." << std::endl;
        continue;
      }

      std::cout << "Enter a new password: ";
      std::string password;
      std::cin >> password;

      if (!is_strong_password(password)) {
        std::cout << "Error: that password is not strong enough. Try again." << std::endl;
        continue;
      }

      accounts[username].first = hash_password(password);
      std::cout << "Password reset successful!" << std::endl;
    } else if (action == "change") {
            std::cout << "Enter your username: ";
      std::string username;
      std::cin >> username;

      if (accounts.count(username) == 0) {
        std::cout << "Error: that username does not exist. Try again." << std::endl;
        continue;
      }

      std::cout << "Enter your current password: ";
      std::string password;
      std::cin >> password;

      if (accounts[username].first != hash_password(password)) {
        std::cout << "Error: incorrect password. Try again." << std::endl;
        continue;
      }

      std::cout << "Enter a new password: ";
      std::string new_password;
      std::cin >> new_password;

      if (!is_strong_password(new_password)) {
        std::cout << "Error: that password is not strong enough. Try again." << std::endl;
        continue;
      }

      accounts[username].first = hash_password(new_password);
      std::cout << "Password changed successfully!" << std::endl;
    } else {
      std::cout << "Error: invalid action. Try again." << std::endl;
    }
  }

  return 0;
}
