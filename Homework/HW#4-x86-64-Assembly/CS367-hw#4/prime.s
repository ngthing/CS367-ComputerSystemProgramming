# Thi Nguyen 10/10/2016
# Given a positive long argument n, determine if it is prime. 
# Return 0x0 when it is composite, and 0x1 when it is prime.
        .text
.global prime
        .type   prime,@function
prime:
        # This method will return Ox1 if n is a prime number, 0x0 if n is composite
        # YOUR CODE HERE
        movq    %rdi, %rsi      # Set x = n, x @ %rsi
        movq    $2, %rcx        # Set i = 2, i @ %rcx 
        shrq    $1, %rsi        # Set x = x/2 = x>>1 Logical shift right
        cmpq    $2 ,%rdi        # Compare n : 2
        jg      .L1             # If n > 2, jump to L1 to check for prime 
        jl      .L2             # If n < 2. i.e. n = 0,1. return OxO
        movq    $1, %rax        # n = 2 is prime
        ret
.L1:
        movq    %rdi, %rax      # Move n to lower 8 bytes of dividend
        cqto
        idivq   %rcx            # Divide by i
        cmpq    $0, %rdx        # Compare remainder : 0
        je      .L2             # If remainder = 0, n is not a prime number, jump to L2
        incq    %rcx            # Otherwise i++
        cmpq    %rsi, %rcx      # Compare i : x
        jl      .L1             # If i < x , continue loop L1
        movq    $1, %rax        # Otherwise, n is prime, return 0x1
        ret
.L2:
        movq    $0, %rax        # n is not prime return 0x0
        ret
        # END YOUR CODE

        .size   prime, .-prime