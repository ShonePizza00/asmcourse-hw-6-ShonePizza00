section .text
global f2
f2:
    push ebp
    mov ebp, esp
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fld qword[ebp+8]
    fmulp
    mov esp, ebp
    pop ebp
    ret