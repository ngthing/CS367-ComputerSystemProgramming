#  Thi Nguyen 10/10/2016
# multiply the given value by 20 and return it
        .text
.global mul_20
        .type   mul_20,@function
mul_20:

        # YOUR CODE HERE        # Recall x*20 = x*(16+4)=x<<4 + x<<2
        movq %rdi,%rbx          # Save x on %rbx to use later
        movq %rdi,%rax          # Save x on %rax
        salq $4, %rbx           # x<<4
        salq $2, %rax           # x<<2
        addq %rbx, %rax         # return x<<2 + x<<4
        ret
        # END YOUR CODE

        .size   mul_20, .-mul_20