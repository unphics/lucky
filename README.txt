5 + 1 - 3 * 4 / 2
根据BNF生成这棵树
          [-]
       ↙     ↘
    [+]       [/]
  ↙   ↘     ↙  ↘
[5]   [1] [*]  [2]
        ↙   ↘
      [3]   [4]



mov   $2,   %rax
push  %rax
mov   $4,   %rax  
push  %rax
mov   $3,   %rax
pop   %rdi
mul   %rdi, %rax
pop   %rdi
cqo
idiv  %rdi
push  %rax
mov   $1,   %rax
push  %rax
mov   $5,   %rax
pop   %rdi
add   %rdi, %rax
pop   %rdi
sub   %rdi, %rax


1 是常量， a 是变量
a+1 是表达式
if(a) a+=1; 是语句
表达式都有「值」，语句都能「执行」
它们可以互相引用，像 if(表达式)语句; ，即嵌套树结构。
最深项先执行，把树变为值称「解释」，
保留中间数据，即区间推断/地址安排称「编译」