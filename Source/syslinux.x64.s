.att_syntax

.globl mount
.globl mkdir
.globl write
.globl exit
.globl fork
.globl execve
.globl chmod
.globl reboot
.globl waitid

.section .text

mount:
  movq $0xa5, %rax
  movq %rcx , %r10
  syscall
  ret

mkdir:
  movq $0x53, %rax
  syscall
  ret

write:
  movq $0x01, %rax
  syscall
  ret

exit:
  movq $0x3c, %rax
  syscall
  ret

fork:
  movq $0x39, %rax
  syscall
  ret

execve:
  movq $0x03b, %rax
  syscall
  ret

chmod:
  movq $0xfa, %rax
  syscall
  ret

reboot:
  movq $0xa9, %rax
  syscall
  ret

waitid:
  movq $0xF7, %rax
  movq %rcx, %r10
  syscall
  ret
