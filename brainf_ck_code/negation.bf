
>
move the number one above top of the stack
< [>>+<<-] >
being at the top of the stack add one to zero caused by moving the 
value over the top
+ [-<+>]
if the copy is nonzero then this will flip one to zero
go one above the copy
> [<<->>>]
if previous cell is copy go one left
< [<]
clear copy if exists
> [-] <