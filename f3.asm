section .text
global f3
f3:
    push ebp
    mov ebp, esp
    fld qword[ebp+8]
    fstcw word[ebp-8]
    mov ax, word[ebp-8]
    mov dx, ax
    mov ah, 0b1111
    mov word[ebp-8], ax
    fldcw word[ebp-8]
    frndint
    mov word[ebp-8], dx
    fldcw word[ebp-8]
    fstp qword[ebp-8]
    fld qword[ebp+8]
    fld qword[ebp-8]
    fsubp
    f2xm1
    fld1
    faddp
    fstp qword[ebp+8]
    fld qword[ebp-8]
    fld1
    fscale
    fstp
    fld qword[ebp+8]
    fmulp
    fld1
    fdivrp
    mov esp, ebp
    pop ebp
    ret