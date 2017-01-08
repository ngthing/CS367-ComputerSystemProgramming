# Thi Nguyen 10/10/2016
# Accept a long n (the length of an array), and long[] xs (the array). 
# Add up all the prime numbers in the array. Return this sum.
        .text
.global sum_primes
        .type   sum_primes,@function

sum_primes:
        # long sum_primes (long n, long a[]) 
        # n in %rdi, a pointer to a[] in %rsi
        # YOUR CODE HERE
        movq    %rdi, %rbx      # Move n to %rbx so that %rdi can be used when call prime
        movq    $0, %rdi        # Reset %rdi = 0
        movq    $0, %rdx        # Set i = 0, i @ %rdx
        movq    $0, %rcx        # Set sum = 0, sum @ %rcx
        jmp     .L1
.L1: #loop
        movl    (%rsi, %rdx, 4),%edi    # Set %rdi = a[i]
        call    prime
        je      .L2             # If a[i] is not Prime
        addq    %rdi, %rcx      # If a[i] is Prime: sum += a[i]
        incq    %rdx            # i++
        cmpq    %rbx, %rdx      # Compare i : n
        jl      .L1             # i < n, goto loop
        jmp     .L3             # i>=n goto L3 to return
.L2: #if not prime
        incq    %rdx            # i++
        cmpq    %rbx, %rdx      # Compare i : n
        jl      .L1             # If i < n goto loop
        jmp     .L3             # If i >= n goto L3 to return sum

.L3:
        movq    %rcx, %rax      # Set %rax = sum and return
        ret
        # END YOUR CODE

        .size   sum_primes, .-sum_primes