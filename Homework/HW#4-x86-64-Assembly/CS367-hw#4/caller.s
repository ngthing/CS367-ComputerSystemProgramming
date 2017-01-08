# Thi Nguyen 10/10/2016
# Caller manually calls another function. 
# Accept two arguments x and y. Add them together, feed the result to collatz, 
# add one to that answer, and return that result.
        .text
.global caller
        .type   caller,@function
caller:
        # caller (long x, long y) 
        # YOUR CODE HERE
        leaq    (%rdi, %rsi),%rdi               # z= x + 7
        call    collatz
        incq    %rax                            # return collatz result + 1
        ret
        # END YOUR CODE

        .size   caller, .-caller