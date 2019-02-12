# 机器学习的数学基础(一)

机器学习对于数学要求比较高，但是学习过程中也不能淹没在数学细节中。机器学习的重要的数学基础之一是`线性代数`和`多变量微积分`（`Linear Algebra` and `Multivariable Calculus`）。对于这门学科要掌握到什么程度?请弄懂以下三道试题即可。

## 问题一 {Gradients and Hessians}

### 题目

Recall that a matrix $A \in {R}^{n \times n}$ is symmetric if $A^T=A$, that is, ${A}_{ij}={A}_{ji}$ for all $i, j$. Also recall the gradient $\triangledown f(x)$ of a function $f:{R}^{n} \rightarrow n$ which is the n-vector of partial derivatives $\triangledown f(x) = \begin{bmatrix} \frac { \partial  }{ \partial { x }_{ 1 } }f(x) \\ \vdots \\ \frac { \partial  }{ \partial { x }_{ n }}f(x) \end{bmatrix}$ where $x =  \begin{bmatrix} {x}_{1} \\ \vdots \\ {x}_{n} \end{bmatrix}$. The hessian ${\triangledown}^{2}f(x)$ of a function $f:{R}^{n} \rightarrow R$ is the $ n \times n$ symmetric matrix of twice partial derivatives, $\begin{bmatrix} \frac{{\partial}^{2}}{\partial {x}_{1}^{2}}f(x) & \frac{{\partial}^{2}}{\partial {x}_{1} {x}_{2}}f(x) & \cdots & \frac{{\partial}^{2}}{\partial {x}_{1} \partial {x}_{n}}f(x) \\ \frac{{\partial}^{2}}{\partial {x}_{2}{x}_{1}}f(x) & \frac{{\partial}^{2}}{\partial {x}_{2}^{2}}f(x) & \cdots & \frac{{\partial}^{2}}{\partial {x}_{2} \partial {x}_{n}}f(x) \\ \vdots & \vdots & \ddots & \vdots \\ \frac{{\partial}^{2}}{\partial {x}_{n}{x}_{1}}f(x) & \frac{{\partial}^{2}}{\partial {x}_{n}{x}_{2}}f(x) & \cdots & \frac{{\partial}^{2}}{\partial {x}_{n}^{2}}f(x) \end{bmatrix}​$. 

### 第一问

Let $f(x)=\frac{1}{2}{x}^{T}Ax + {b}^{T}x$ where A is a symmetric matrix and $b \in {R}^{n}$ is a vector. What is $\triangledown f(x)$ ?

### 解：

A可以写成：$A = \begin{bmatrix} {R}_{1} \\ {R}_{2} \\ \cdots \\ {R}_{n} \end{bmatrix}$ 其中 $ {R}_{i} = \begin{bmatrix} {A}_{i1} & {A}_{i2} & \cdots & {A}_{in} \end{bmatrix} $,

设:$ {f}_{1}(x) = {x}^{T}Ax = {x}^{T}(Ax)={x}^{T}(\begin{bmatrix} {R}_{1} \\ {R}_{2} \\ \cdots \\ {R}_{n} \end{bmatrix}x) = {x}^{T}\begin{bmatrix} {R}_{1}x \\ {R}_{2}x \\ \cdots \\ {R}_{n}x \end{bmatrix} = {x}^{T}\begin{bmatrix} {R}_{1}x \\ {R}_{2}x \\ \cdots \\ {R}_{n}x \end{bmatrix} $ (其中：${R}_{i}$为行向量；$x​$为列向量) 

$= \begin{bmatrix} {x}_{1} & {x}_{2} &  \cdots  & {x}_{n}  \end{bmatrix} \begin{bmatrix} {R}_{1}x \\ {R}_{2}x \\ \vdots \\ {R}_{n}x  \end{bmatrix}  =\sum_{i=1}^{n}{{x}_{i}{R}_{i}x} =\sum_{i=1}^{n}{({R}_{i}x){x}_{i}} = \sum_{i=1}^{n}{\sum_{j=1}^{n}{{A}_{ij}{x}_{j}}{x}_{i}} = \sum_{i=1}^{n}{\sum_{j=1}^{n}{{A}_{ij}{x}_{i}}{x}_{j}} $

所以：$\triangledown {f}_{1}(x)=\begin{bmatrix} \frac{\partial}{\partial {x}_{1}}({f}_{1}(x)) \\ \frac{\partial}{\partial {x}_{2}}({f}_{1}(x)) \\ \vdots \\ \frac{\partial}{\partial {x}_{k}}({f}_{1}(x)) \\ \vdots \\ \frac{\partial}{\partial {x}_{n}}({f}_{1}(x)) \\ \end{bmatrix} $ 

​    通项：$\frac{\partial}{\partial {x}_{k}}({f}_{1}(x))=\frac{\partial}{\partial {x}_{k}}(\sum_{i=1}^{n}{\sum_{j=1}^{n}{{A}_{ij}{x}_{i}}{x}_{j}}) = part1 + part2 + part3 + part4$ ,

​     其中:

​    $i = k, j = k$时为part1;

​    $i \neq k, j \neq k$ 时为 part2; 

​    $i = k, j \neq k​$时为 part3; 

​    $i \neq k, j = k$时 为 part4;

可得:

  $part1 = \frac{\partial {A}_{kk}{x}_{k}^{2}}{\partial {x}_{k}} = 2{A}_{kk}{x}_{k}$;

  $part2 = 0$; 

 $part3 = \frac{\partial \sum_{j \neq k}^{n} {A}_{kj} {x}_{k}{x}_{j}}{{x}_{k}} = \sum_{j \neq k}^{n}{A}_{kj}{x}_{j}$; 

  $part4 = \frac{\partial \sum_{i \neq k}^{n} {A}_{ik} {x}_{i}{x}_{k}}{{x}_{k}} = \sum_{i \neq k}^{n}{A}_{ik}{x}_{i} = \sum_{j \neq k}^{n}{A}_{jk}{x}_{j} = \sum_{j \neq k}^{n}{A}_{kj}{x}_{j}​$

  $\because​$ matrix A is symmetric , $\therefore {A}_{jk} = {A}_{kj}​$.

   可得: $part4=part3$ ,

​    $\therefore \frac{\partial}{\partial {x}_{k}}({f}_{1}(x)) = part1 + 2part3 = 2{A}_{kk}{x}_{k} + 2\sum_{j \neq k}^{n}{A}_{kj}{x}_{j} = 2\sum_{j = 1}^{n}{A}_{kj}{x}_{j} = 2\begin{bmatrix} {R}_{1}{x}_{1} \\ {R}_{2}{x}_{2} \\ \vdots  \\ {R}_{n}{x}_{n}  \end{bmatrix} = 2\begin{bmatrix} {R}_{1} \\ {R}_{2} \\ \vdots \\ {R}_{n} \end{bmatrix}x  = 2Ax$ ,

  综上：$\frac{\partial}{\partial {x}_{k}}({f}_{1}(x)) = 2Ax$ , 设：${f}_{2}(x) = {b}^Tx = \sum_{i=1}^{n}{{b}_{i}{x}_{i}}$ ,

   则：$\triangledown{f}_{2}(x) = \frac{\partial}{\partial x} {f}_{2}(x) = \begin{bmatrix} \frac{\partial \sum_{i=1}^{n}{{b}_{i}{x}_{i}} }{\partial {x}_{1}} \\ \frac{\partial \sum_{i=1}^{n}{{b}_{i}{x}_{i}} }{\partial {x}_{2}} \\ \vdots \\ \frac{\partial \sum_{i=1}^{n}{{b}_{i}{x}_{i}} }{\partial {x}_{n}} \\ \end{bmatrix} = \begin{bmatrix} {b}_{1} \\ {b}_{2} \\ \vdots \\ {b}_{n} \\ \end{bmatrix} = b$

​    结论:$\triangledown f(x) = \triangledown {f}_{1}(x) + \triangledown {f}_{2}(x) = 2Ax + b$ ,

    ### 小结

这是个很形式化的结论，如果A,x,b是标量，我们可轻易得到结论：$\\triangledown (A{x}^{2}+bx) = 2Ax + b$.

由本题推算过程可知：这个结论当x为向量时，依然成立，只是 $A{x}^{2}​$需表述成：${x}^{T}Ax​$,且$A​$必须为对称矩阵;$bx​$需表述成${b}^{T}x​$。

### 第二问

Let $f(x) = g(h(x))​$,where $g:R \rightarrow R​$ is differentiable and $h:{R}^{n} \rightarrow R​$ is differentiable. What is $\triangledown f(x)​$?

### 解:

设 $y = h(x)$ $y \in R$ 则:$f(x) = g(y)$ 

$ \therefore \triangledown f(x) = \frac{d}{dy}g(y)\frac{\partial y}{\partial x} = \frac{d}{dh}g(h)\frac{\partial h}{\partial x} = \frac{d}{dh}g(h) \begin{bmatrix} \frac{\partial}{\partial {x}_{1}}h \\ \frac{\partial}{\partial {x}_{2}}h \\ \vdots \\ \frac{\partial}{\partial {x}_{n}}h \\ \end{bmatrix} = \begin{bmatrix} \frac{d}{dh}g(h)\frac{\partial}{\partial {x}_{1}}h \\ \frac{d}{dh}g(h)\frac{\partial}{\partial {x}_{2}}h \\ \vdots \\ \frac{d}{dh}g(h)\frac{\partial}{\partial {x}_{n}}h \\ \end{bmatrix} $

### 第三问

Let $f(x)= {x}^{T}Ax+{b}^{T}x$,where A is symmetric and $b \in {R}^{n}$ is a vector. What is ${\triangledown}^{2}f(x)$?

### 解：

由Hessians矩阵可知：${\triangledown}^{2}f(x) = \begin{bmatrix}
  {b}_{11} & {b}_{12} & \cdots & {b}_{1n} \\
  {b}_{21} & {b}_{22} & \cdots & {b}_{2n}  \\
  \vdots & \vdots & \ddots &\vdots \\
  {b}_{n1} & {b}_{n2} & \cdots & {b}_{nn}  \\
 \end{bmatrix}​$ 
结合第一问的结论，可知，
通项${b}_{ij} =  \frac{{\partial}^{2}}{\partial {x}_{i} \partial {x}_{j}}f(x)= \frac{{\partial}^{2}}{\partial {x}_{i} \partial {x}_{j}}\sum_{i=1}^{n}\sum_{j=1}^{n}{A}_{ij}{x}_{i}{x}_{j} + \frac{{\partial}^{2}}{\partial {x}_{i} \partial {x}_{j}}\sum_{i=1}^{n}{b}_{i}{x}_{i}={A}_{ij} + 0 = {A}_{ij}​$ 
可得：${\triangledown}^{2}f(x)=A​$

### 小结

如同第一问，这同样是一个很形式化的结论，如果A,x,b是标量，我们可轻易得到结论：${\triangledown}^{2} (A{x}^{2}+bx) = A。$ 
由本题推算过程可知：这个结论当x为向量时，依然成立，只是 $A{x}^{2}$需表述成：${x}^{T}Ax$,且A必须对称矩阵;bx需表述成${b}^{T}x$。

### 第四问

Let $f(x)=g({a}^{T}x)$, where $g:R \rightarrow R$ is continuously differentiable and $a \in {R}^{n}$ is a vector. What are $\triangledown f(x)$ and $\triangledown^{2}f(x)$? (Hint: your expression for $\triangledown^{2}f(x)$ may have as few as 11 symbols, including $^{,}$ and parentheses.)

### 解：

令 $y={a}^{T}x$,则
$\triangledown g(x) = \frac{dg}{dy}\begin{bmatrix}
\frac{\partial}{\partial {x}_{1}}({a}^{T}x) \\
\frac{\partial}{\partial {x}_{2}}({a}^{T}x) \\
\vdots \\
\frac{\partial}{\partial {x}_{n}}({a}^{T}x) \\
\end{bmatrix}
= {g}^{,}({a}^{T}x)\begin{bmatrix}
{a}_{1}\\ {a}_{2}\\ \vdots\\ {a}_{n} 
\end{bmatrix}
= {g}^{,}({a}^{T}x)\cdot a$ 
$
\triangledown^{2}g(x)
= \begin{bmatrix}
{C}_{11} & C_{12} & \cdots & C_{1n} \\
{C}_{21} & C_{22} & \cdots & C_{2n} \\
\vdots   & \vdots & \ddots & \vdots \\
{C}_{n1} & C_{n2} & \cdots & C_{nn}
\end{bmatrix}\\
$
其中：${C}_{ij}
= \frac{\partial}{\partial {x}_{i}} \frac{\partial}{\partial {x}_{j}} g({a}^{T}x)
= \frac{\partial}{\partial {x}_{i}} (g'({a}^{T}x) \cdot {a}_{j})
= {a}_{j}\frac{\partial}{\partial {x}_{i}} g'({a}^{T}x)
= {a}_{j} {g}^{}({a}^{T}x)\cdot {a}_{i} 
=  {a}_{i}{a}_{j}{g}^{''}({a}^{T}x)
$
可知：$\triangledown^{2}g(x) 
= a\cdot {a}^{T}{g}^{''}({a}^{T}x)​$