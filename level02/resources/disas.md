```asm
(gdb) disas main
Dump of assembler code for function main:
   0x0000000000400814 <+0>:	push   %rbp
   0x0000000000400815 <+1>:	mov    %rsp,%rbp
   
   0x0000000000400818 <+4>:	sub    $0x120,%rsp                      // 288 bytes for local vars
   0x000000000040081f <+11>:	mov    %edi,-0x114(%rbp)            // argc
   0x0000000000400825 <+17>:	mov    %rsi,-0x120(%rbp)            // argv
   0x000000000040082c <+24>:	lea    -0x70(%rbp),%rdx             // char username rbp-0x70 - rbp-0xc= 100
   0x0000000000400830 <+28>:	mov    $0x0,%eax
   0x0000000000400835 <+33>:	mov    $0xc,%ecx                    // 12 steps for 8 bytes
   0x000000000040083a <+38>:	mov    %rdx,%rdi
   0x000000000040083d <+41>:	rep stos %rax,%es:(%rdi)            // char username[100] = {}
   0x0000000000400840 <+44>:	mov    %rdi,%rdx
   0x0000000000400843 <+47>:	mov    %eax,(%rdx)
   0x0000000000400845 <+49>:	add    $0x4,%rdx
   0x0000000000400849 <+53>:	lea    -0xa0(%rbp),%rdx             // char pass[48] ?; 0xa0-0x70=48 char pass[40] ?
   0x0000000000400850 <+60>:	mov    $0x0,%eax
   0x0000000000400855 <+65>:	mov    $0x5,%ecx
   0x000000000040085a <+70>:	mov    %rdx,%rdi
   0x000000000040085d <+73>:	rep stos %rax,%es:(%rdi)            // char pass[41] = {}
   0x0000000000400860 <+76>:	mov    %rdi,%rdx
   0x0000000000400863 <+79>:	mov    %al,(%rdx)
   0x0000000000400865 <+81>:	add    $0x1,%rdx
   0x0000000000400869 <+85>:	lea    -0x110(%rbp),%rdx            // char user_pass = 0x110 - 0xa0 = 112
   0x0000000000400870 <+92>:	mov    $0x0,%eax
   0x0000000000400875 <+97>:	mov    $0xc,%ecx                    // 12 steps of 8 bytes
   0x000000000040087a <+102>:	mov    %rdx,%rdi
   0x000000000040087d <+105>:	rep stos %rax,%es:(%rdi)            // char user_pass[100] = {}
   0x0000000000400880 <+108>:	mov    %rdi,%rdx
   0x0000000000400883 <+111>:	mov    %eax,(%rdx)
   0x0000000000400885 <+113>:	add    $0x4,%rdx
   0x0000000000400889 <+117>:	movq   $0x0,-0x8(%rbp)              // 8 byte FILE *file 
   0x0000000000400891 <+125>:	movl   $0x0,-0xc(%rbp)              // 4 byte int pass_len
   
   
   0x0000000000400898 <+132>:	mov    $0x400bb0,%edx               // "r"
   0x000000000040089d <+137>:	mov    $0x400bb2,%eax               // "/home/users/level03/.pass"
   0x00000000004008a2 <+142>:	mov    %rdx,%rsi                    // arg2 - "r"
   0x00000000004008a5 <+145>:	mov    %rax,%rdi                    // arg1 -  "/home/users/level03/.pass"
   0x00000000004008a8 <+148>:	callq  0x400700 <fopen@plt>         // fopen("/home/users/level03/.pass", "r")
   0x00000000004008ad <+153>:	mov    %rax,-0x8(%rbp)              // store return in rbp-0x8
   0x00000000004008b1 <+157>:	cmpq   $0x0,-0x8(%rbp)              // compare return with 0
   0x00000000004008b6 <+162>:	jne    0x4008e6 <main+210>          // jump if not eqaul to main+210
   
   
   0x00000000004008b8 <+164>:	mov    0x200991(%rip),%rax          # 0x601250 <stderr@@GLIBC_2.2.5>
   0x00000000004008bf <+171>:	mov    %rax,%rdx                    // stderr
   0x00000000004008c2 <+174>:	mov    $0x400bd0,%eax               // "ERROR: failed to open password file\n"
   0x00000000004008c7 <+179>:	mov    %rdx,%rcx                    // arg4 - stderr
   0x00000000004008ca <+182>:	mov    $0x24,%edx                   // arg3 - 36
   0x00000000004008cf <+187>:	mov    $0x1,%esi                    // arg2 - 1
   0x00000000004008d4 <+192>:	mov    %rax,%rdi                    // arg1 - "ERROR: failed to open password file\n"
   0x00000000004008d7 <+195>:	callq  0x400720 <fwrite@plt>        // fwrite( "ERROR: failed to open password file\n", 1, 36, stderr)
   
   0x00000000004008dc <+200>:	mov    $0x1,%edi                    // 1
   0x00000000004008e1 <+205>:	callq  0x400710 <exit@plt>          // exit(1)
   
   0x00000000004008e6 <+210>:	lea    -0xa0(%rbp),%rax             // &pass
   0x00000000004008ed <+217>:	mov    -0x8(%rbp),%rdx              // file
   0x00000000004008f1 <+221>:	mov    %rdx,%rcx                    // arg4 - file
   0x00000000004008f4 <+224>:	mov    $0x29,%edx                   // arg3 - 41
   0x00000000004008f9 <+229>:	mov    $0x1,%esi                    // arg2 - 1
   0x00000000004008fe <+234>:	mov    %rax,%rdi                    // arg1 - &pass
   0x0000000000400901 <+237>:	callq  0x400690 <fread@plt>         // fread(pass, 1, 41, file)
   0x0000000000400906 <+242>:	mov    %eax,-0xc(%rbp)              // store length of pass 
     
   0x0000000000400909 <+245>:	lea    -0xa0(%rbp),%rax             // pass
   0x0000000000400910 <+252>:	mov    $0x400bf5,%esi               // arg2 - "\n"
   0x0000000000400915 <+257>:	mov    %rax,%rdi                    // arg1 - pass
   0x0000000000400918 <+260>:	callq  0x4006d0 <strcspn@plt>       // strcspn(pass, "\n")
   0x000000000040091d <+265>:	movb   $0x0,-0xa0(%rbp,%rax,1)      // change "\n" to "\0"
   0x0000000000400925 <+273>:	cmpl   $0x29,-0xc(%rbp)             // compare that pass len equals 41
   0x0000000000400929 <+277>:	je     0x40097d <main+361>          // if equal jump *main+361
   
   
   0x000000000040092b <+279>:	mov    0x20091e(%rip),%rax          # 0x601250 <stderr@@GLIBC_2.2.5>
   0x0000000000400932 <+286>:	mov    %rax,%rdx                    // stderr
   0x0000000000400935 <+289>:	mov    $0x400bf8,%eax               // "ERROR: failed to read password file\n"
   0x000000000040093a <+294>:	mov    %rdx,%rcx                    // arg4 - stderr
   0x000000000040093d <+297>:	mov    $0x24,%edx                   // arg3 - 36
   0x0000000000400942 <+302>:	mov    $0x1,%esi                    // arg2 - 1
   0x0000000000400947 <+307>:	mov    %rax,%rdi                    // arg1 - "ERROR: failed to read password file\n"
   0x000000000040094a <+310>:	callq  0x400720 <fwrite@plt>        // fwrite("ERROR: failed to read password file\n", 1, 36, stderr)
   
   
   0x000000000040094f <+315>:	mov    0x2008fa(%rip),%rax           # 0x601250 <stderr@@GLIBC_2.2.5>
   0x0000000000400956 <+322>:	mov    %rax,%rdx                    // stderr
   0x0000000000400959 <+325>:	mov    $0x400bf8,%eax               // "ERROR: failed to read password file\n"
   0x000000000040095e <+330>:	mov    %rdx,%rcx                    // arg4 - stderr
   0x0000000000400961 <+333>:	mov    $0x24,%edx                   // arg3 - 36
   0x0000000000400966 <+338>:	mov    $0x1,%esi                    // arg2 - 1
   0x000000000040096b <+343>:	mov    %rax,%rdi                    // arg1 - "ERROR: failed to read password file\n"
   0x000000000040096e <+346>:	callq  0x400720 <fwrite@plt>        // fwrite("ERROR: failed to read password file\n", 1, 36, stderr)
   
   0x0000000000400973 <+351>:	mov    $0x1,%edi             
   0x0000000000400978 <+356>:	callq  0x400710 <exit@plt>          // exit(1)
   
   0x000000000040097d <+361>:	mov    -0x8(%rbp),%rax              // *file
   0x0000000000400981 <+365>:	mov    %rax,%rdi
   0x0000000000400984 <+368>:	callq  0x4006a0 <fclose@plt>        // fclose(file)
   
   0x0000000000400989 <+373>:	mov    $0x400c20,%edi               // "===== [ Secure Access System v1.0 ] ====="
   0x000000000040098e <+378>:	callq  0x400680 <puts@plt>          // puts("===== [ Secure Access System v1.0 ] =====")
   0x0000000000400993 <+383>:	mov    $0x400c50,%edi               // "/***************************************\\"
   0x0000000000400998 <+388>:	callq  0x400680 <puts@plt>          // puts("/***************************************\\")
   0x000000000040099d <+393>:	mov    $0x400c80,%edi               // "| You must login to access this system. |"
   0x00000000004009a2 <+398>:	callq  0x400680 <puts@plt>          // puts("| You must login to access this system. |")
   0x00000000004009a7 <+403>:	mov    $0x400cb0,%edi               // "\\**************************************/"
   0x00000000004009ac <+408>:	callq  0x400680 <puts@plt>          // puts("\\**************************************/")
   0x00000000004009b1 <+413>:	mov    $0x400cd9,%eax               // "--[ Username: "
   0x00000000004009b6 <+418>:	mov    %rax,%rdi                    
   0x00000000004009b9 <+421>:	mov    $0x0,%eax
   0x00000000004009be <+426>:	callq  0x4006c0 <printf@plt>        // printf("--[ Username: ")
   
   0x00000000004009c3 <+431>:	mov    0x20087e(%rip),%rax           # 0x601248 <stdin@@GLIBC_2.2.5>
   0x00000000004009ca <+438>:	mov    %rax,%rdx                    // arg3 - stdin
   0x00000000004009cd <+441>:	lea    -0x70(%rbp),%rax             // username
   0x00000000004009d1 <+445>:	mov    $0x64,%esi                   // arg2 - 100
   0x00000000004009d6 <+450>:	mov    %rax,%rdi                    // arg1 - username
   0x00000000004009d9 <+453>:	callq  0x4006f0 <fgets@plt>         // fgets(username, 100, stdin)
   
   
   0x00000000004009de <+458>:	lea    -0x70(%rbp),%rax             // &username
   0x00000000004009e2 <+462>:	mov    $0x400bf5,%esi               // arg2 - "\n"
   0x00000000004009e7 <+467>:	mov    %rax,%rdi                    // arg1 - &username
   0x00000000004009ea <+470>:	callq  0x4006d0 <strcspn@plt>       // strcspn(&username, "\n")
   0x00000000004009ef <+475>:	movb   $0x0,-0x70(%rbp,%rax,1)      // change \n to \0
   
   0x00000000004009f4 <+480>:	mov    $0x400ce8,%eax               // "--[ Password: "
   0x00000000004009f9 <+485>:	mov    %rax,%rdi
   0x00000000004009fc <+488>:	mov    $0x0,%eax
   0x0000000000400a01 <+493>:	callq  0x4006c0 <printf@plt>        // printf("--[ Password: ")
   
   0x0000000000400a06 <+498>:	mov    0x20083b(%rip),%rax          # 0x601248 <stdin@@GLIBC_2.2.5>
   0x0000000000400a0d <+505>:	mov    %rax,%rdx                    // arg3 - stdin
   0x0000000000400a10 <+508>:	lea    -0x110(%rbp),%rax            // user_pass
   0x0000000000400a17 <+515>:	mov    $0x64,%esi                   // arg2 - 100
   0x0000000000400a1c <+520>:	mov    %rax,%rdi                    // arg1 - &user_pass
   0x0000000000400a1f <+523>:	callq  0x4006f0 <fgets@plt>         // fgets(user_pass, 100, stdin)
   
   0x0000000000400a24 <+528>:	lea    -0x110(%rbp),%rax            // user_pass
   0x0000000000400a2b <+535>:	mov    $0x400bf5,%esi               // arg2 - "\n"
   0x0000000000400a30 <+540>:	mov    %rax,%rdi                    // arg1 - user_pass
   0x0000000000400a33 <+543>:	callq  0x4006d0 <strcspn@plt>       // strcspn(user_pass, "\n")
   0x0000000000400a38 <+548>:	movb   $0x0,-0x110(%rbp,%rax,1)     // change "\n" to "\0" 
   
   
   0x0000000000400a40 <+556>:	mov    $0x400cf8,%edi               // "************************************************"
   0x0000000000400a45 <+561>:	callq  0x400680 <puts@plt>          // puts("************************************************")
   
   0x0000000000400a4a <+566>:	lea    -0x110(%rbp),%rcx            // user_pass
   0x0000000000400a51 <+573>:	lea    -0xa0(%rbp),%rax             // &pass
   0x0000000000400a58 <+580>:	mov    $0x29,%edx                   // arg3 - 41
   0x0000000000400a5d <+585>:	mov    %rcx,%rsi                    // arg2 - user_pass
   0x0000000000400a60 <+588>:	mov    %rax,%rdi                    // arg1 - &pass
   0x0000000000400a63 <+591>:	callq  0x400670 <strncmp@plt>       // strncmp(pass, user_pass, 41)
   
   0x0000000000400a68 <+596>:	test   %eax,%eax                    // if eax==0 continue
   0x0000000000400a6a <+598>:	jne    0x400a96 <main+642>          // if not equal - jump *main+642
   
   0x0000000000400a6c <+600>:	mov    $0x400d22,%eax               // "Greetings, %s!\n"
   0x0000000000400a71 <+605>:	lea    -0x70(%rbp),%rdx             // username
   0x0000000000400a75 <+609>:	mov    %rdx,%rsi                    // arg2 - username
   0x0000000000400a78 <+612>:	mov    %rax,%rdi                    // arg1 - "Greetings, %s!\n"
   0x0000000000400a7b <+615>:	mov    $0x0,%eax                    
   0x0000000000400a80 <+620>:	callq  0x4006c0 <printf@plt>        // printf("Greetings, %s!\n", username)
   
   
   0x0000000000400a85 <+625>:	mov    $0x400d32,%edi               // "/bin/sh"
   0x0000000000400a8a <+630>:	callq  0x4006b0 <system@plt>        // system("/bin/sh")
   
   0x0000000000400a8f <+635>:	mov    $0x0,%eax
   0x0000000000400a94 <+640>:	leaveq 
   0x0000000000400a95 <+641>:	retq   
   0x0000000000400a96 <+642>:	lea    -0x70(%rbp),%rax             // username
   0x0000000000400a9a <+646>:	mov    %rax,%rdi                    // arg1 - username
   0x0000000000400a9d <+649>:	mov    $0x0,%eax
   0x0000000000400aa2 <+654>:	callq  0x4006c0 <printf@plt>        // printf(username)
   0x0000000000400aa7 <+659>:	mov    $0x400d3a,%edi               // " does not have access!"
   0x0000000000400aac <+664>:	callq  0x400680 <puts@plt>          // puts(" does not have access!")
   0x0000000000400ab1 <+669>:	mov    $0x1,%edi
   0x0000000000400ab6 <+674>:	callq  0x400710 <exit@plt>          // exit(1)
End of assembler dump.

```