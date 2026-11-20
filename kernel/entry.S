.section .multiboot2_header,"a"
.balign 8
header_start:
    .long 0xe85250d6
    .long 0
    .long header_end - header_start
    .long -(0xe85250d6 + (header_end - header_start))

    /* Pede framebuffer gráfico 800x600x32 ao GRUB. */
    .short 5
    .short 0
    .long 20
    .long 800
    .long 600
    .long 32

    /* Mantém os serviços UEFI disponíveis durante o primeiro bring-up. */
    .short 7
    .short 0
    .long 8

    /* Entrada x86_64 para GRUB EFI amd64. */
    .short 9
    .short 0
    .long 16
    .quad _start

    .short 0
    .short 0
    .long 8
header_end:

.section .text,"ax"
.global _start
.type _start,@function
_start:
    cli
    cld
    leaq kernel_stack_top(%rip), %rsp
    andq $-16, %rsp
    movq %rax, %rdi
    movq %rbx, %rsi
    call kernel_main
1:
    hlt
    jmp 1b

.section .bss,"aw",@nobits
.balign 16
kernel_stack_bottom:
    .skip 16384
kernel_stack_top:

.section .note.GNU-stack,"",@progbits
