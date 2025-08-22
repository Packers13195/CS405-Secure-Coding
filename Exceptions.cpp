// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Austin Donaubauer
// Date: 7/26/2025
//
#include <exception>
#include <iostream>

class CustomException : public std::exception {
public:
    const char * what () {
        return "Custom Exception";
    }
};

bool do_even_more_custom_application_logic()
{
  // TODO: Throw any standard exception

  std::cout << "Running Even More Custom Application Logic." << std::endl;

  throw std::exception("Exception");
  
  return true;

}
void do_custom_application_logic()
{
  // TODO: Wrap the call to do_even_more_custom_application_logic()
  //  with an exception handler that catches std::exception, displays
  //  a message and the exception.what(), then continues processing
  std::cout << "Running Custom Application Logic." << std::endl;

  try {
      if (do_even_more_custom_application_logic()) {
          std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
      }
  }
  catch (std::exception &e) {
      std::cout << "Standard Exception Caught: " << e.what() << std::endl;
  }
  

  // TODO: Throw a custom exception derived from std::exception
  //  and catch it explictly in main

  throw CustomException();

  std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
  // TODO: Throw an exception to deal with divide by zero errors using
  //  a standard C++ defined exception
    
    if (den == 0) {
        // Throw std::runtime_error for bad division
        throw std::runtime_error("Division by zero exception");
    }

  return (num / den);
}

void do_division() noexcept
{
  //  TODO: create an exception handler to capture ONLY the exception thrown
  //  by divide.

    
    float numerator = 10.0f;
    float denominator = 0;

    try {

        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
       
    }
    // Catch std::runtime_error for bad division
    catch (std::runtime_error &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    

}

int main()
{
  std::cout << "Exceptions Tests!" << std::endl;

  // TODO: Create exception handlers that catch (in this order):
  //  your custom exception
  //  std::exception
  //  uncaught exception 
  //  that wraps the whole main function, and displays a message to the console.
  try {
      
      do_division();
      
      do_custom_application_logic();
      
      
  }
  // Catch custom exception
  catch (CustomException& customException) {
      std::cout << "Custom Exception Caught: " << customException.what() << std::endl;
  }
  // Catch std::exceptions types
  catch (std::exception& e) {
      std::cout << "Standard Exception Caught" << e.what() << std::endl;
  }
  // Catch All other exceptions
  catch (...) {
      std::cout << "Any other Exceptions Caught" << std::endl;
  }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
