section .text
global df2
df2:
    push ebp
    mov ebp, esp
    fld qword[ebp+8]
    fld qword[ebp+8]
    fmulp
    mov dword[ebp+8], 3
    fimul dword[ebp+8]
    mov esp, ebp
    pop ebp
    ret