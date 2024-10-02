# Simple Calculator Project

This project is a basic calculator implemented using an ATmega32 microcontroller, an LCD, and a keypad. The calculator is capable of accepting mathematical expressions as input and displaying the results on the LCD, similar to a Casio calculator. It supports basic arithmetic operations including addition, subtraction, multiplication, and division.

## Features

- Input expressions using a keypad.
- Display results on a 16x2 LCD.
- Support for floating-point numbers and basic operators (+, -, *, /).
- Handles multiple operations in a single expression.
- Correctly handles negative numbers and consecutive minus signs (`--`).

## Project Structure

This project follows a modular approach, dividing functionality into multiple small functions to ensure maintainability and scalability.

### Files

- `main.c`: Contains the core logic of the calculator.
- `lcd_int.h`, `keypad_int.h`: Header files containing function prototypes and interface definitions for the LCD and keypad modules.
- `calculator_int.h`: Header file for the calculator's main functionalities.
- `config.h`: Configuration file containing definitions for hardware setup.

### Naming Conventions

This project adheres to a strict naming convention:

- **Global Variables:** Prefix with `Calculator_`, e.g., `Calculator_Au8Nums`.
- **Local Variables:** Prefix with `Local_`, e.g., `Local_u8Counter`.
- **Function Names:** Prefix with `Calculator_`, e.g., `Calculator_voidInit()`.
- **Header Files:** Use `_int.h` suffix to indicate function prototypes, e.g., `calculator_int.h`.

## Getting Started

### Prerequisites

- **Microcontroller:** ATmega32
- **Development Environment:** Eclipse
- **Simulation Tool:** Proteus

### Keypad Layout

The calculator uses a 4x4 keypad for input. Each key corresponds to a specific digit or operator.

| Button | Operation |
|--------|-----------|
| `0-9`  | Digits    |
| `+`    | Addition  |
| `-`    | Subtraction (also used for negative numbers) |
| `*`    | Multiplication |
| `/`    | Division  |
| `=`    | Equals (compute result) |

### LCD Display

The results are displayed on a 16x2 LCD. The first line shows the input expression, and the second line displays the result.

## Handling Negative Numbers

When encountering double negatives (`--`), the first `-` is treated as a subtraction operator, and the second `-` is interpreted as making the subsequent number negative.

## Future Improvements

- **Additional Operations:** Add support for more complex mathematical functions (e.g., trigonometry, exponentiation).
- **Error Handling:** Improve error handling for cases like division by zero.
- **Memory:** Add support for storing and recalling previous results.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request with your changes.
