/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
	  /* brief description of how your implementation works */
	  int var1 = Expr1;
	  ...
	  int varM = ExprM;

	  varJ = ExprJ;
	  ...
	  varN = ExprN;
	  return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
	  not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
	 cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
	 than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
	 /* exploit ability of shifts to compute powers of 2 */
	 return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
	 /* exploit ability of shifts to compute powers of 2 */
	 int result = (1 << x);
	 result += 4;
	 return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
	 cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
	 check the legality of your solutions.
  2. Each function has a maximumoutputber of operators (! ~ & ^ | + << >>)
	 that you are allowed to use for your implementation of the function.
	 The max operator count is checked by dlc. Note that '=' is not
	 counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximumoutputber of ops for each function is given in the
	 header comment for each function. If there are any inconsistencies
	 between the maximum ops in the writeup and in this file, consider
	 this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */

#endif
//1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y){
	//利用数字逻辑知识，A异或B=A'B+AB'。
	int a = ~(~(~x & y) & ~(x & ~y));
	return a;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void){
	//最小的二进制补码第一位为1，后面全为0。
	return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complementoutputber,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x){
	//观察tmax的特性。
	//如果x为二进制补码的最大值，他加上一之后应该会溢出为补码的最小值，取反后除第一位以外都为1。再和x本身异或运算就可以得到0。
	//然而，-1也具有此特性，所以需要用!(~x)来排除这种情况。
	return !(~(x + 1) ^ x | (!(~x)));
}
/*
 * allOddBits - return 1 if all oddoutputbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x){
	//曲线生成一个题目不允许的常量0xAAAAAAAA来判断。
	int a = 0xAA;
	int b = (a << 8) + a;
	int c = (b << 8) + a;
	int d = (c << 8) + a;
	return !((x & d) ^ d);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x){
	//负数等于反码加一。
	return ~x + 1;
}
//3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x){
	//利用x-0x30>=0且x-0x39<=0求解。-0x30=~0x30+1。
	return (!((x + (~0x30 + 1)) >> 31)) & (!((0x39 + (~x + 1)) >> 31));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z){
	//利用当x等于0的时候返回z，x等于1的时候返回y。这两个数的特性在于将x转换为0或1后，他们的负数会变成全0位或全1位，再进行&运算即可。
	int t = !x;
	return ((~!t + 1) & y) | (~(~!t + 1) & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y){
	//为了防止直接使用x+~y导致数据溢出，需要判断两者的符号。同号时直接运算，异号时判断是否为x负，y正。
	int negX = ~x + 1;				//-x
	int addX = negX + y;			//y-x
	int checkSign = addX >> 31 & 1; //y-x的符号
	int leftBit = 1 << 31;			//最大位为1的32位有符号数
	int xLeft = x & leftBit;		//x的符号
	int yLeft = y & leftBit;		//y的符号
	int bitXor = xLeft ^ yLeft;		//x和y符号相同标志位，相同为0不同为1
	bitXor = (bitXor >> 31) & 1;	//符号相同标志位格式化为0或1
	return ((!bitXor) & (!checkSign)) | (bitXor & (xLeft >> 31));
}
//4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x){
	//利用当x=0时-x=x，且最高位为0，其他所有情况都不满足。
	int negx = ~x + 1;
	return ~(x | negx) >> 31 & 1;
}
/* howManyBits - return the minimumoutputber of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x){
	//用二分查找法确定位数，即如果x在某个位数上有值，那么就会给最终的结果加上对应的数字，并且将x右移对应的位数，进行进一步判断。
	//最后的总位数加上1用来表示符号位。
	int sign, bit0, bit1, bit2, bit4, bit8, bit16;
	sign = x >> 31;
	x = (sign & ~x) | (~sign & x); //如果是负数便翻转x的值运算。
	bit16 = !!(x >> 16) << 4;
	x = x >> bit16;
	bit8 = !!(x >> 8) << 3;
	x = x >> bit8;
	bit4 = !!(x >> 4) << 2;
	x = x >> bit4;
	bit2 = !!(x >> 2) << 1;
	x = x >> bit2;
	bit1 = !!(x >> 1);
	x = x >> bit1;
	bit0 = x;
	return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}
//float
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf){
	//需要判断规格化的值，非规格化的值和特殊值的情况，分开计算。
	unsigned exp = uf & 0x7F800000;
	unsigned sign = uf & 0x80000000;
	if (exp != 0)
	{
		if (exp != 0x7F800000)
		{
			uf = uf + 0x00800000;
			if (exp == 0x7F000000)
				uf = (uf & 0xFF800000);
		}
	}
	else
		uf = (uf << 1) | sign;
	return uf;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x){
	//浮点数使用的是第一位来表示正负数，所以对于输入为负的整数，需要转换成正数再操作；
	//如果为0则直接返回0；
	//判断出阶码为2多多少次方指数，再运算出尾数对应的小数值；
	int sign, exp, frac, bitc, tailb;
	if (x == 0)
		return 0;
	else if (x == 0x80000000)
		return 0xCF000000;
	sign = (x >> 31) & 1;
	if (sign)
		x = -x;
	bitc = 1;
	while ((x >> bitc) != 0)
		bitc++;
	bitc--;
	exp = bitc + 127;
	x = x << (31 - bitc);
	frac = (x >> 8) & 0x7FFFFF;
	if (bitc > 23){
		tailb = x & 0xFF; 
		if ((tailb > 128) || ((tailb == 128) && (frac & 1))){
			frac += 1;
			if (frac >> 23){
				exp += 1;
				frac = 0;
			}
		}
	}
	return (sign << 31) | (exp << 23) | frac;
}
/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf){
	//将浮点数的各个部分提取出来，并分情况求解。
	//当exp<0的时候浮点数小于0，所以为0；
	//当其大于2^32次方时，数字过大，返回inf。
	//其他情况下，将小数部分加1之后位移相应位数。
	
	//多次尝试后仍然没有通过。
	unsigned sig = uf >> 31;
	unsigned exp = uf & 0x7F800000;
	unsigned frac = uf & 0x007FFFFF;
	unsigned bias = 0x7F;
	int output;
	if (exp >= 0 && exp < 0 + bias){
		output = 0;
	}
	else if (exp >= 31 + bias){
		output = 0x80000000;
	}
	else{
		unsigned E = exp - bias;
		unsigned M = frac | 0x800000;
		if (E > 23){
			output = M << (E - 23);
		}
		else{
			output = M >> (23 - E);
		}
	}
	return sig ? output : -output;
}
