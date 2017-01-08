# Thi Nguyen 10/10/2016
# Given a positive long int argument n, calculate the length of the collatz sequence starting with n.
# all sequences end with the value 1.
# when a value is even, the next value is half of this value.
# when a value is odd, the next value is triple this value plus 1.
        .text
.global collatz
        .type   collatz,@function
collatz:
        # This method will return the length of the collatz sequence starting at n.
        # YOUR CODE HERE
        movl    $0 , %eax               # Set length = 0
.L1:
        movq    %rdi , %rsi             # Set a variable x = the current n
        incq    %rax                    # length++ 
        cmpq    $1, %rdi                # Compare current n : 1
        je      .L4                     # If n = 1, jump to L4 to return length
        andq    $0x1, %rsi              # If n!=1, compute x = x & 0x1 
        je      .L2                     # If x=0, current n is event, jump to L2
        jmp     .L3                     # Otherwise, current n is odd, jump to L3       
.L2:
        shrq    $1,%rdi                 # If n is even, Logical Right Shift n=n>>1
        jmp     .L1
.L3:
        leaq    1(%rdi, %rdi, 2),%rdi   # If n is odd, n=n*2 + n +1 
        jmp     .L1
.L4:
        ret

        # END YOUR CODE

        .size   collatz, .-collatz