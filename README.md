# BIG-INT
In this code, I've developed functionality to handle arithmetic operations on numbers exceeding the typical integer size, specifically using a custom structure called bigint. This structure includes attributes for length, sign, and a pointer to an array of integers to store digits.

To achieve this, the input numbers are initially taken as strings to accommodate their large size. Subsequently, memory allocation (malloc) is employed to store the sign bit, length, and digits of the number within the bigint structure. This setup enables arithmetic operations such as addition, subtraction, and multiplication to be performed seamlessly on numbers .
