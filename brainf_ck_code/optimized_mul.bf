TODO {
    it does not work if second argument is zero
}

+++++ >
+++ >
<< go to the first arg and copy it at the top of the stack
[->>+<<]
>- go the second arg and subtract one
[
    - substract one from the second arg
    > go to the copy of the first arg
    [->+<<<+>>] copy it and add value to result
TODO {
    this process can be removed at last iteration
    but right now I don't have psycha to do that
}
    move the first arg to current cell
    >[-<+>] 
    << return to the second arg
]
>[-<<+>>] add the rest to the result
< go to stack top