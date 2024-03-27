# Infix_to_Prefix_Expression_Converter

## Overview
This project is an implementation of an infix to prefix expression converter in C. It allows users to perform various operations on infix expressions, such as printing the expression, checking if it is balanced, reversing the infix expression, converting the infix expression to prefix notation, and quitting the program.

## Features
- **Print Expression:** Display the infix expression stored in a file.
- **Check Balance:** Determine if the infix expression is balanced with respect to parentheses.
- **Reverse Infix Expression:** Reverse the infix expression using a stack.
- **Convert to Prefix:** Convert the infix expression to prefix notation using a stack.
- **Quit:** Exit the program.

## How to Use
1. Run the program.
2. Choose an operation from the menu by entering the corresponding number.
3. Follow the prompts to perform the desired operation.
4. Continue or quit based on the prompts.
5. Optionally, modify the infix expression file to test different expressions.

## File Structure
- **main.c:** Contains the main program logic.
- **Functions:** Includes functions for printing infix expression, checking balance, reversing infix expression, converting to prefix, and menu display.
- **Files:** `infix.txt` stores the infix expression.

## Dependencies
- This project is written in C and requires a C compiler to build and run.
- Standard C libraries such as `stdio.h`, `stdlib.h`, `string.h`, and `ctype.h` are used.

## Usage Notes
- Ensure the `infix.txt` file exists and contains a valid infix expression.
- Follow the prompts to navigate through the menu options.
- Check the balance of the infix expression before attempting to reverse or convert it.

## Future Improvements
- Implement error handling for invalid inputs.
- Improve the efficiency of infix to prefix conversion.
- Add support for more complex expressions and operators.
- Enhance user interface for better interaction.
