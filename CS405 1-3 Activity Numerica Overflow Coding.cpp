// CS405 1-3 Activity Numerica Overflow Coding.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// AUTHOR: CS-405 Secure Coding
// INSTITUTION: Southern New Hampshire University (SNHU)
// COURSE: CS-405 Secure Coding
// EDITOR: Austin Donaubauer
// DATE: 6/30/2025

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <type_traits>  // std::is_integral, std::is_floating_point (Checking types)
#include <cmath>        // std::isinf (Check if floating point value is infinity)
#include <string>       // std::to_string (Was used for debuging datatype values (Unused after commenting out the debugging lines)

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <param name="result">The result of adding</param> UPDATE adding additional parameter to hold the result
/// <returns>Boolean value</returns> UPDATED return value to help indicate overflow or underflow
template <typename T>
bool add_numbers(T const& start, T const& increment, unsigned long int const& steps, T& result)
{
    T current_result = start; // UPDATE update local result variable

    // DEBUGGING lines to check Maximum and Minimum values of datatypes
    //std::cout << std::endl << "Max Value: " << std::numeric_limits<T>::max() << std::endl;
    //std::cout << "Min Value: " << std::numeric_limits<T>::min() << std::endl;

    // DEBUGGING lines to check type
    //std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;

    for (unsigned long int i = 0; i < steps; ++i)
    {

        // DEBUGGING line to check datatype value as it progressed throught the loop
        //std::cout << "Current Result: " << current_result << std::endl;

        if (std::is_integral<T>::value) { // Check if value is an Integer datatype

            // Check if value will overflow
            if (increment > 0 && current_result > std::numeric_limits<T>::max() - increment) {

                return false; // Overflow detected

            }
            
            // Check if value will underflow
            if (increment < 0 && current_result < std::numeric_limits<T>::min() + increment) {

                return false; // Underflow detected

            }

        }

        //current_result += increment; // add to result

        if (std::is_floating_point<T>::value) { // Check if value is a floating point datatype

            // DEBUGGING line to check datatype value as it progressed throught the loop
            //std::cout << "Current Result: " << static_cast<long long>(current_result) << std::endl;

            // Check if value will overflow
            if (increment > 0 && current_result > std::numeric_limits<T>::max() - increment) {

                return false; // Overflow detected

            }

            // Check if value will underflow
            if (increment < 0 && current_result < std::numeric_limits<T>::min() + increment) {

                return false; // Underflow detected

            }

            if (std::isinf(current_result)) { // Check for infinity

                return false; // Overflow if infinity

            }

        }

        current_result += increment; // add to result

    }

    result = current_result; // Assign result to local result value

    return true; // Calculation completed successfully with no overflow or underflow detected
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <param name="result">The result of the substration</param>
/// <returns>boolean value</returns>

template <typename T>
bool subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, T& result)
{

    // DEBUGGING lines to check Maximum and Minimum values of datatypes
    //std::cout << std::endl << "Max Value: " << static_cast<long long>(std::numeric_limits<T>::max()) << std::endl;
    //std::cout << "Min Value: " << static_cast<long long>(std::numeric_limits<T>::min()) << std::endl;
    //std::cout << "Max value - decrement = " << std::numeric_limits<T>::max() - decrement << std::endl;
    //std::cout << "Max value + decrement = " << std::numeric_limits<T>::max() + decrement << std::endl;

    T current_result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {

        //if (std::is_integral<T>::value) {

            // DEBUGGING line to check datatype value as it progressed throught the loop
            //std::cout << "Current Result: " << current_result << std::endl;

        if (decrement > 0) { // Subtracting a positive decrement, potentially causing an underflow

            if (current_result < (std::numeric_limits<T>::min() + decrement)) { // Check that if local result value would exceet minimum data limit

                return false; // Underflow will occur

            }

        }
        if (decrement < 0) { // Subtracting a negative decrement, potentially causing an overflow

            if (current_result > (std::numeric_limits<T>::max() + decrement)) { // Check that if local result value would exceed max data limit

                return false; // Overflow will occur

            }

        }
        
        // Check for signed datatypes
        if (std::is_signed<T>::value && decrement > 0) {

            if (current_result >= 0 && (current_result - decrement) < 0) { // Check that if local result value decremented would result in negative value which is an underflow

                return false; //logical underflow for if value goes below zero but doesn't reach actual datatype minimum value

            }

        }
        /*


    }

    if (std::is_floating_point<T>::value) { // Check for floating point datatypes

        //std::cout << "Current Result: " << current_result << std::endl;

        if (std::isinf(current_result)) { // Check for infinity underflow

            return false;

        }

        if (!std::isnormal(current_result) && current_result != 0.0) { // check for not 0.0 value and not normal

            return false;

        }

        if (decrement > 0 && current_result < std::numeric_limits<T>::min() + decrement) {

            return false;

        }

    }
    */
        current_result -= decrement; // Decrement local result value by decrement value
    }

        //}
    result = current_result; // assign local value to reference variable
    return true; // Return true for non-detected overflow/underflow calculation

    
}
    



//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // TODO: The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        1. Detect when an overflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no overflow happened or
    //        4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        1. Detect when an add_numbers failed
    //        2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    T result = 0;

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    if (add_numbers<T>(start, increment, steps, result)) {

        std::cout << +result << std::endl;

    }
    else {

        std::cout << "Overflow detected" << std::endl; // Output overflow detected statement

    }

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    if (add_numbers<T>(start, increment, steps + 1, result)) {

        std::cout << +result << std::endl;

    }
    else {

        std::cout << "Overflow detected" << std::endl; // Output overflow detected statement

    }
}

template <typename T>
void test_underflow()
{
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        1. Detect when an underflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no underflow happened or
    //        4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        1. Detect when an subtract_numbers failed
    //        2. Inform the user the underflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    T result;

    std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    if (subtract_numbers<T>(start, decrement, steps, result)) {
        std::cout << +result << std::endl;
    }
    else {
        std::cout << "Underflow detected" << std::endl;
    }

    std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << ((steps * 2) + 2) << ") = ";
    if (subtract_numbers<T>(start, decrement, (steps * 2) + 1, result)) {

        std::cout << +result << std::endl;

    }
    else {

        std::cout << "Underflow detected" << std::endl;

    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative types see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative types see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu