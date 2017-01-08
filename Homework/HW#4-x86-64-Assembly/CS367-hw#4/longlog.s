# Thi Nguyen 10/10/2016
# Given a long argument n, calculate longlog(n), the whole number log2 value.
        .text
.global longlog
        .type   longlog,@function
longlog:

        # YOUR CODE HERE        # return the log base 2 of long n
        movl $0 , %eax          # set result = 0
        cmpq $1 , %rdi          # compare n : 1
        jg   .L2                # if n > 1, jump to L2
        ret                     # if n <= 1, return 0 
.L2:
        shrq $1, %rdi           # n=n>>1 logical shift 1
        jne  .L3                # if n!=0 jump to L3
        ret                     # if n=0 return 
.L3:
        incq %rax               # result++
        jmp  .L2

        # END YOUR CODE

        .size   longlog, .-longlog