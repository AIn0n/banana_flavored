generated with generate_multiplication py
Stores argument at top of the stack
return argument one above the stack
first step: generate 3 copies of dynamic first arg
[
  -
  >+
  >+
  >+

  <<<
]
sum all the copied values
move to the 2 copy
>>
move pointer to the left as long as the number is not zero
[
  >
  move current cell value into the left neighbor
  [-<+>]
  <<
]
