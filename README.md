# ctc-C.tools
Command Line Tools for Composers

Title: “ctc-C.tools” version 1.5
Year: 2015-present
Development Language: C++
Platform: Mac OSX/Windows
Interface: CLI
Description: This program lets you construct pitch sets, rows or matrixes from input, then display them or outputs them to a file in the same directory. There are thirteen sub-programs available:

1. Generate a row of random pitches: This program lets you generate a list of up to 10000 random pitches with the option to output to a text file. It implements the ctime library in C++.
2. Construct a row with input of any integers: This program takes user input of any integers to form a row of up to 50 pitches. When the input is more than 12 or less than 0, the program modulates it back to the "normal" range by continuously adding or subtracting 12. The user can then create a row based on those "normalized" pitches.
3. Construct a twelve-tone row to be mapped to a custom table: This program creates a custom table other than the standard chromatic table, and lets the user map a custom row to this table.
4. Construct a matrix: This is a classic program for constructing a matrix. The user has the option to create matrixes that are less than or more than 12 pitches.
5. Construct a matrix in rotation: This matrix rotates by one column to the right at a time by default by each row.
6. Construct a multiplication table
7. Construct a multiplication table in rotation
8. Construct a multiplication table with inversion
9. Construct a multiplication table with inversion in rotation
10. Compute the prime set from a given set
11. Print the table of pitch class sets
12. Find all permutations of a given set
13. Find all subsets of a given set
