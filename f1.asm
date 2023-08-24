section .text
global f1
f1:
    push ebp
    mov ebp, esp
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fld1
    faddp
    mov dword[esp-8], 4
    fidivr dword[esp-8]
    fld1
    faddp
    mov esp, ebp
    pop ebp
    ret