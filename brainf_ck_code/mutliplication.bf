ABI {
    Stack is growing to the right by plus operation
    pointer start at stack top
    stack top is empty value
    input is ordered stackwise left to right starting at top minus one position
    input values are totally removed after the operation
    output value is put one below stack top
    at the end pointing at value to benchmark

    input
        number1
        number2
    output
        number1 X number2
}

<< go to the first arg and copy it at the top of the stack
[->>+<<]
> go the second arg
[
 - substract one from the second arg
 > go to the copy of the first arg
 copy it and add value to result
 [->+<<<+>>]
 move the first arg to current cell
 >[-<+>]
 << return to the second arg
]
>[-] go back to copy and clear cell
< go back to the stack top
< for benchmarking go back to returned value
