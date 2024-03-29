++++++ >
++ >
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