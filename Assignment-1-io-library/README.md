# Assignment №1: Input/Output library in assembly
---


In this task, you need to implement a library of procedures that will perform simple actions with strings, numbers, and their text representations.

* `exit` - accepts an exit code and terminates current process

* `string_length` - accepts a pointer to a string and returns its length

* `print_string` - accepts a pointer to a null-terminated string and prints it to stdout

* `print_char` - accepts a character code directly as its first argument and prints it to stdout

* `print_newline` - prints a character with code 0xA

* `print_uint` - outputs an unsigned 8-byte integer in decimal format

* `print_int` - output a signed 8-byte integer in decimal format

* `read_char` - read one character from stdin and return it. If the end of input stream occurs, return 0

* `read_word` - accepts a buffer address and size as arguments. Reads next word from stdin (skipping whitespaces7 into buffer); stops and returns 0 if word is too big for the buffer specified; otherwise returns a buffer address

* `parse_uint` - accepts a null-terminated string and tries to parse an unsigned number from its start; returns the number parsed in rax, its characters count in rdx

* `parse_int` - accepts a null-terminated string and tries to parse a signed number from its start; returns the number parsed in rax; its characters count in rdx (including sign if any); no spaces between sign and digits are allowed

* `string_equals` - accepts two pointers to strings and compares them; returns 1 if they are equal, otherwise 0

* `string_copy` - accepts a pointer to a string, a pointer to a buffer, and buffer’s length; copies string to the destination; the destination address is returned if the string fits the buffer; otherwise zero is returned
