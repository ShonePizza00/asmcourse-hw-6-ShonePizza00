section .text
global df1
df1:
    push ebp
    mov ebp, esp
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    fld1
    faddp
    fstp qword[ebp-8]
    fld qword[ebp-8]
    fld qword[ebp-8]
    fmulp
    fld qword[ebp+8]
    mov dword[ebp+8], 8
    fimul dword[ebp+8]
    fdivrp
    fchs
    mov esp, ebp
    pop ebp
    ret