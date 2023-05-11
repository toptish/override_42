```asm
Dump of assembler code for function main:
   0x0804885a <+0>:	push   %ebp
   0x0804885b <+1>:	mov    %esp,%ebp
   0x0804885d <+3>:	and    $0xfffffff0,%esp                         // stack alignment
   0x08048860 <+6>:	sub    $0x20,%esp                               // 32 bytes for local varibles
   0x08048863 <+9>:	push   %eax                                     // push eax value to stack
   0x08048864 <+10>:	xor    %eax,%eax                            // eax = 0
   0x08048866 <+12>:	je     0x804886b <main+17>                  // jump if equal *main+17
   0x08048868 <+14>:	add    $0x4,%esp                            // add 4 to esp
   0x0804886b <+17>:	pop    %eax
   0x0804886c <+18>:	movl   $0x0,(%esp)                          // put 0 to adress saved in esp
   0x08048873 <+25>:	call   0x80484b0 <time@plt>                 // time()
   0x08048878 <+30>:	mov    %eax,(%esp)                          // save result in a stack (at adress at esp)
   0x0804887b <+33>:	call   0x8048500 <srand@plt>                // srand(time())
   0x08048880 <+38>:	movl   $0x8048a48,(%esp)                    // "***********************************"
   0x08048887 <+45>:	call   0x80484d0 <puts@plt>                 // puts("***********************************")
   0x0804888c <+50>:	movl   $0x8048a6c,(%esp)                    // "*\t\tlevel03\t\t**"
   0x08048893 <+57>:	call   0x80484d0 <puts@plt>                 // puts("*\t\tlevel03\t\t**")
   0x08048898 <+62>:	movl   $0x8048a48,(%esp)                    // "***********************************"
   0x0804889f <+69>:	call   0x80484d0 <puts@plt>                 // puts("***********************************")
   0x080488a4 <+74>:	mov    $0x8048a7b,%eax                      // "Password:"
   0x080488a9 <+79>:	mov    %eax,(%esp)                          // arg1 - "Password:"
   0x080488ac <+82>:	call   0x8048480 <printf@plt>               // printf("Password:")
   0x080488b1 <+87>:	mov    $0x8048a85,%eax                      // "%d"
   0x080488b6 <+92>:	lea    0x1c(%esp),%edx                      // load esp+0x1c to edx
   0x080488ba <+96>:	mov    %edx,0x4(%esp)                       // arg2 - esp+0x1c - var input
   0x080488be <+100>:	mov    %eax,(%esp)                          // arg1 - "%d"
   0x080488c1 <+103>:	call   0x8048530 <__isoc99_scanf@plt>       // scanf("%d", &input)
   0x080488c6 <+108>:	mov    0x1c(%esp),%eax                      // input to eax
   0x080488ca <+112>:	movl   $0x1337d00d,0x4(%esp)                // arg2 - 322424845 (0x1337d00d)
   0x080488d2 <+120>:	mov    %eax,(%esp)                          // arg1 - input
   0x080488d5 <+123>:	call   0x8048747 <test>                     // test(input, 322424845)
   0x080488da <+128>:	mov    $0x0,%eax                            // 0 to eax
   0x080488df <+133>:	leave  
   0x080488e0 <+134>:	ret                                         // return 0
End of assembler dump.

```


```asm
Dump of assembler code for function test:
   0x08048747 <+0>:	push   %ebp                                     // push ebp value to the stack
   0x08048748 <+1>:	mov    %esp,%ebp                                // store esp address with previous ebp in ebp
   0x0804874a <+3>:	sub    $0x28,%esp                               // 40 bytes for local variables
   0x0804874d <+6>:	mov    0x8(%ebp),%eax                           // arg1 to eax (input var)
   0x08048750 <+9>:	mov    0xc(%ebp),%edx                           // arg2 to edx
   0x08048753 <+12>:	mov    %edx,%ecx                            // save arg2 to ecx
   0x08048755 <+14>:	sub    %eax,%ecx                            // subtract arg1 from arg2 and save to ecx
   0x08048757 <+16>:	mov    %ecx,%eax                            // save ecx to eax
   0x08048759 <+18>:	mov    %eax,-0xc(%ebp)                      // arg2-arg1 to ebp-0xc
   0x0804875c <+21>:	cmpl   $0x15,-0xc(%ebp)                     // compare 21 to arg2-arg1
   0x08048760 <+25>:	ja     0x804884a <test+259>                 // if greater - jump test+259
   0x08048766 <+31>:	mov    -0xc(%ebp),%eax                      // arg2-arg1 to eax
   0x08048769 <+34>:	shl    $0x2,%eax                            // shift left eax на 2 (ex: 101 -> 10100)
   0x0804876c <+37>:	add    $0x80489f0,%eax                      // add 0x80489f0 to eax
   0x08048771 <+42>:	mov    (%eax),%eax                          // save value at address in eax to eax
   0x08048773 <+44>:	jmp    *%eax                                // jump to address saved in eax
   0x08048775 <+46>:	mov    -0xc(%ebp),%eax
   0x08048778 <+49>:	mov    %eax,(%esp)                          // arg1 - arg2-arg1
   0x0804877b <+52>:	call   0x8048660 <decrypt>                  // decrypt(arg2-arg1)
   0x08048780 <+57>:	jmp    0x8048858 <test+273>
   0x08048785 <+62>:	mov    -0xc(%ebp),%eax
   0x08048788 <+65>:	mov    %eax,(%esp)
   0x0804878b <+68>:	call   0x8048660 <decrypt>
   0x08048790 <+73>:	jmp    0x8048858 <test+273>
   0x08048795 <+78>:	mov    -0xc(%ebp),%eax
   0x08048798 <+81>:	mov    %eax,(%esp)
   0x0804879b <+84>:	call   0x8048660 <decrypt>
   0x080487a0 <+89>:	jmp    0x8048858 <test+273>
   0x080487a5 <+94>:	mov    -0xc(%ebp),%eax
   0x080487a8 <+97>:	mov    %eax,(%esp)
   0x080487ab <+100>:	call   0x8048660 <decrypt>
   0x080487b0 <+105>:	jmp    0x8048858 <test+273>
   0x080487b5 <+110>:	mov    -0xc(%ebp),%eax
   0x080487b8 <+113>:	mov    %eax,(%esp)
   0x080487bb <+116>:	call   0x8048660 <decrypt>
   0x080487c0 <+121>:	jmp    0x8048858 <test+273>
   0x080487c5 <+126>:	mov    -0xc(%ebp),%eax
   0x080487c8 <+129>:	mov    %eax,(%esp)
   0x080487cb <+132>:	call   0x8048660 <decrypt>
   0x080487d0 <+137>:	jmp    0x8048858 <test+273>
   0x080487d5 <+142>:	mov    -0xc(%ebp),%eax
   0x080487d8 <+145>:	mov    %eax,(%esp)
   0x080487db <+148>:	call   0x8048660 <decrypt>
   0x080487e0 <+153>:	jmp    0x8048858 <test+273>
   0x080487e2 <+155>:	mov    -0xc(%ebp),%eax
   0x080487e5 <+158>:	mov    %eax,(%esp)
   0x080487e8 <+161>:	call   0x8048660 <decrypt>
   0x080487ed <+166>:	jmp    0x8048858 <test+273>
   0x080487ef <+168>:	mov    -0xc(%ebp),%eax
   0x080487f2 <+171>:	mov    %eax,(%esp)
   0x080487f5 <+174>:	call   0x8048660 <decrypt>
   0x080487fa <+179>:	jmp    0x8048858 <test+273>
   0x080487fc <+181>:	mov    -0xc(%ebp),%eax
   0x080487ff <+184>:	mov    %eax,(%esp)
   0x08048802 <+187>:	call   0x8048660 <decrypt>
   0x08048807 <+192>:	jmp    0x8048858 <test+273>
   0x08048809 <+194>:	mov    -0xc(%ebp),%eax
   0x0804880c <+197>:	mov    %eax,(%esp)
   0x0804880f <+200>:	call   0x8048660 <decrypt>
   0x08048814 <+205>:	jmp    0x8048858 <test+273>
   0x08048816 <+207>:	mov    -0xc(%ebp),%eax
   0x08048819 <+210>:	mov    %eax,(%esp)
   0x0804881c <+213>:	call   0x8048660 <decrypt>
   0x08048821 <+218>:	jmp    0x8048858 <test+273>
   0x08048823 <+220>:	mov    -0xc(%ebp),%eax
   0x08048826 <+223>:	mov    %eax,(%esp)
   0x08048829 <+226>:	call   0x8048660 <decrypt>
   0x0804882e <+231>:	jmp    0x8048858 <test+273>
   0x08048830 <+233>:	mov    -0xc(%ebp),%eax
   0x08048833 <+236>:	mov    %eax,(%esp)
   0x08048836 <+239>:	call   0x8048660 <decrypt>
   0x0804883b <+244>:	jmp    0x8048858 <test+273>
   0x0804883d <+246>:	mov    -0xc(%ebp),%eax
   0x08048840 <+249>:	mov    %eax,(%esp)
   0x08048843 <+252>:	call   0x8048660 <decrypt>
   0x08048848 <+257>:	jmp    0x8048858 <test+273>
   0x0804884a <+259>:	call   0x8048520 <rand@plt>
   0x0804884f <+264>:	mov    %eax,(%esp)
   0x08048852 <+267>:	call   0x8048660 <decrypt>
   0x08048857 <+272>:	nop
   0x08048858 <+273>:	leave  
   0x08048859 <+274>:	ret    
End of assembler dump.

```

```asm
(gdb) disas decrypt
Dump of assembler code for function decrypt:
# Prologue
   0x08048660 <+0>:	push   %ebp                                     // push ebp to stack
   0x08048661 <+1>:	mov    %esp,%ebp                                // save adress with previous ebp to ebp
   0x08048663 <+3>:	push   %edi                                     // push edi to stack
   0x08048664 <+4>:	push   %esi                                     // push esi to stack                                  
# Local vars
   0x08048665 <+5>:	sub    $0x40,%esp                               // 64 bytes for local vars
   0x08048668 <+8>:	mov    %gs:0x14,%eax                            // segment register. canary value?
   0x0804866e <+14>:	mov    %eax,-0xc(%ebp)                      // local var at esp-0xc
   0x08048671 <+17>:	xor    %eax,%eax                            // eax=0
   0x08048673 <+19>:	movl   $0x757c7d51,-0x1d(%ebp)              // u|}Q  --  Q}|u   Q}|u`sfg~sf{}|a3
   0x0804867a <+26>:	movl   $0x67667360,-0x19(%ebp)              // gfs`  --  `sfg
   0x08048681 <+33>:	movl   $0x7b66737e,-0x15(%ebp)              // {fs~  --  ~sf{
   0x08048688 <+40>:	movl   $0x33617c7d,-0x11(%ebp)              // 3a|}  --  }|a3
   0x0804868f <+47>:	movb   $0x0,-0xd(%ebp)                      // \0    --  terminate -> \0
   0x08048693 <+51>:	push   %eax                                 // push eax=0 to stack                        
   0x08048694 <+52>:	xor    %eax,%eax                            // eax=0
   0x08048696 <+54>:	je     0x804869b <decrypt+59>               // 
   0x08048698 <+56>:	add    $0x4,%esp                            // add 4 bytes to esp - alignment?
   0x0804869b <+59>:	pop    %eax                                 // remove eax from stack
   0x0804869c <+60>:	lea    -0x1d(%ebp),%eax                     // load crypt "Q}|u`sfg~sf{}|a3" to eax
   0x0804869f <+63>:	movl   $0xffffffff,-0x2c(%ebp)              // counter? -1 (-2, -3, ...)
   0x080486a6 <+70>:	mov    %eax,%edx                            // load crypt "Q}|u`sfg~sf{}|a3" to edx
   0x080486a8 <+72>:	mov    $0x0,%eax                            // counter = 0
   0x080486ad <+77>:	mov    -0x2c(%ebp),%ecx                     // 0xffffffff to ecx
   0x080486b0 <+80>:	mov    %edx,%edi                            // load crypt "Q}|u`sfg~sf{}|a3" to edi
   0x080486b2 <+82>:	repnz scas %es:(%edi),%al                   // strlen of crypt
   0x080486b4 <+84>:	mov    %ecx,%eax                            // counter to eax
   0x080486b6 <+86>:	not    %eax                                 // not counter (from 0xffffffee to 0x11, from -18 to 17)
   0x080486b8 <+88>:	sub    $0x1,%eax                            // strlen = counter - 1            
   0x080486bb <+91>:	mov    %eax,-0x24(%ebp)                     // strlen to ebp-0x24  size_t crypt_len = strlen(crypt)
   0x080486be <+94>:	movl   $0x0,-0x28(%ebp)                     // 0 to ebp-0x28        int i = 0
   0x080486c5 <+101>:	jmp    0x80486e5 <decrypt+133>
   0x080486c7 <+103>:	lea    -0x1d(%ebp),%eax                     // crypt address "Q}|u`sfg~sf{}|a3"
   0x080486ca <+106>:	add    -0x28(%ebp),%eax                     // add 0 to crypt address crypt[i]
   0x080486cd <+109>:	movzbl (%eax),%eax                          // replace eax with lower byte at eax adress (Q at 1st step)
   0x080486d0 <+112>:	mov    %eax,%edx                            // move crypt[i] to eax
   0x080486d2 <+114>:	mov    0x8(%ebp),%eax                       // load decrypt arg to eax
   0x080486d5 <+117>:	xor    %edx,%eax                            // xor arg1 crypt[0] (01010001 ^ 00000101 = 01010100 = 54)
   0x080486d7 <+119>:	mov    %eax,%edx                            // store xor result at edx
   0x080486d9 <+121>:	lea    -0x1d(%ebp),%eax                     // load crypt to eax
   0x080486dc <+124>:	add    -0x28(%ebp),%eax                     // crypt[0+i]
   0x080486df <+127>:	mov    %dl,(%eax)                           // replace crypt[i] with xor result
   0x080486e1 <+129>:	addl   $0x1,-0x28(%ebp)                     // i += 1
   0x080486e5 <+133>:	mov    -0x28(%ebp),%eax                     // ebp-0x28 to eax
   0x080486e8 <+136>:	cmp    -0x24(%ebp),%eax                     // compare strlen and ebp-0x28
   0x080486eb <+139>:	jb     0x80486c7 <decrypt+103>              // if below jump to *decrypt+103; while i < crypt_len
   0x080486ed <+141>:	lea    -0x1d(%ebp),%eax                     // load crypt address to eax
   0x080486f0 <+144>:	mov    %eax,%edx                            // load crypt address to edx
   0x080486f2 <+146>:	mov    $0x80489c3,%eax                      // "Congratulations"
   0x080486f7 <+151>:	mov    $0x11,%ecx                           // 0x11 - 17
   0x080486fc <+156>:	mov    %edx,%esi                            // crypt address to esi
   0x080486fe <+158>:	mov    %eax,%edi                            // "Congratulations" - to edi
   0x08048700 <+160>:	repz cmpsb %es:(%edi),%ds:(%esi)            // strncmp(crypt, "Congratulations, 17)
   0x08048702 <+162>:	seta   %dl
   0x08048705 <+165>:	setb   %al
   0x08048708 <+168>:	mov    %edx,%ecx
   0x0804870a <+170>:	sub    %al,%cl
   0x0804870c <+172>:	mov    %ecx,%eax
   0x0804870e <+174>:	movsbl %al,%eax
   0x08048711 <+177>:	test   %eax,%eax                            // if (strncmp(crypt, "Congratulations, 17) == 0)
   0x08048713 <+179>:	jne    0x8048723 <decrypt+195>              // if not equal - jump decrypt+195
   0x08048715 <+181>:	movl   $0x80489d4,(%esp)                    // "/bin/sh"
   0x0804871c <+188>:	call   0x80484e0 <system@plt>               // system("/bin/sh")
   0x08048721 <+193>:	jmp    0x804872f <decrypt+207>              // jumpt to decrypt+207
   0x08048723 <+195>:	movl   $0x80489dc,(%esp)                    // "\nInvalid Password"
   0x0804872a <+202>:	call   0x80484d0 <puts@plt>                 // puts("\nInvalid Password")
   0x0804872f <+207>:	mov    -0xc(%ebp),%esi                      // load canary value
   0x08048732 <+210>:	xor    %gs:0x14,%esi
   0x08048739 <+217>:	je     0x8048740 <decrypt+224>
   0x0804873b <+219>:	call   0x80484c0 <__stack_chk_fail@plt>     // check_canary_value
   0x08048740 <+224>:	add    $0x40,%esp
   0x08048743 <+227>:	pop    %esi
   0x08048744 <+228>:	pop    %edi
   0x08048745 <+229>:	pop    %ebp
   0x08048746 <+230>:	ret                                         // return 0
End of assembler dump.

```


```asm
Dump of assembler code for function frame_dummy:
   0x080485d0 <+0>:	push   %ebp
   0x080485d1 <+1>:	mov    %esp,%ebp
   0x080485d3 <+3>:	sub    $0x18,%esp
   0x080485d6 <+6>:	mov    0x8049f24,%eax
   0x080485db <+11>:	test   %eax,%eax
   0x080485dd <+13>:	je     0x80485f1 <frame_dummy+33>
   0x080485df <+15>:	mov    $0x0,%eax
   0x080485e4 <+20>:	test   %eax,%eax
   0x080485e6 <+22>:	je     0x80485f1 <frame_dummy+33>
   0x080485e8 <+24>:	movl   $0x8049f24,(%esp)
   0x080485ef <+31>:	call   *%eax
   0x080485f1 <+33>:	leave  
   0x080485f2 <+34>:	ret    
   0x080485f3 <+35>:	nop
End of assembler dump.
```

```asm
Dump of assembler code for function get_unum:
   0x08048617 <+0>:	push   %ebp
   0x08048618 <+1>:	mov    %esp,%ebp
   0x0804861a <+3>:	sub    $0x28,%esp
   0x0804861d <+6>:	movl   $0x0,-0xc(%ebp)
   0x08048624 <+13>:	mov    0x804a040,%eax
   0x08048629 <+18>:	mov    %eax,(%esp)
   0x0804862c <+21>:	call   0x8048490 <fflush@plt>
   0x08048631 <+26>:	mov    $0x80489c0,%eax
   0x08048636 <+31>:	lea    -0xc(%ebp),%edx
   0x08048639 <+34>:	mov    %edx,0x4(%esp)
   0x0804863d <+38>:	mov    %eax,(%esp)
   0x08048640 <+41>:	call   0x8048530 <__isoc99_scanf@plt>
   0x08048645 <+46>:	call   0x80485f4 <clear_stdin>
   0x0804864a <+51>:	mov    -0xc(%ebp),%eax
   0x0804864d <+54>:	leave  
   0x0804864e <+55>:	ret    
End of assembler dump.
```

```asm
Dump of assembler code for function prog_timeout:
   0x0804864f <+0>:	push   %ebp
   0x08048650 <+1>:	mov    %esp,%ebp
   0x08048652 <+3>:	mov    $0x1,%eax
   0x08048657 <+8>:	mov    $0x1,%ebx
   0x0804865c <+13>:	int    $0x80
   0x0804865e <+15>:	pop    %ebp
   0x0804865f <+16>:	ret    
End of assembler dump.

```