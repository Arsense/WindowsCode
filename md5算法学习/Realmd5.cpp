// Realmd5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "md5.h"
#include <string>
#include <iostream>
#include <cstdio> 
using namespace std;



//为MD5Transform常规常量。
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// F，G，H，I是基本的MD5函数。
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) { return x&y | ~x&z; } 
inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) { return x&z | y&~z; } 
inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) { return x^y^z; } 
inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }

//  将x的数字左位移循环n位
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) {
	return (x << n) | (x >> (32-n));
}
// FF，GG，HH，和II转换为轮1，2，3和4。
//旋转是除了分开，避免重新计算。
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + F(b,c,d) + x + ac, s) + b;
}

inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
}

inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
}

inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
}

// default ctor, just initailize
MD5::MD5()
{
	init();
}

MD5::MD5(const std::string &text)
{
	init();            //初始化四个链表变量
	update(text.c_str(), text.length());
	finalize();
}

void MD5::init()
{
	finalized=false;

	count[0] = 0;
	count[1] = 0;
	// //加载Magic初始化常量。
	// load magic initialization constants.
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

//解码输入（无符号字符）到输出（uint4）。假定len为4的倍数。
void MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint4)input[j]) | (((uint4)input[j+1]) << 8) |
		(((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);
}
//取出值
//编码输入（uint4）到输出（无符号字符）。假定len为4的倍数。
void MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
	//length 8   32位  4个字节存一位
	for (size_type i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = input[i] & 0xff;
		output[j+1] = (input[i] >> 8) & 0xff;
		output[j+2] = (input[i] >> 16) & 0xff;
		output[j+3] = (input[i] >> 24) & 0xff;
	}
}

//块上应用的MD5算法中
void MD5::transform(const uint1 block[blocksize])
{
	uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	decode (x, block, blocksize);
	/* Round 1 *///FF里面套了两个函数
	FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

	/* Round 2 */
	GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

	/* Round 3 */
	HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

	/* Round 4 */
	II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	//清0敏感信息
	memset(x, 0, sizeof x);
}

// MD5块更新操作。持续的MD5信息摘要
//操作，处理另一个消息块
void MD5::update(const unsigned char input[], size_type length)
{
	// compute number of bytes mod 64
	//
	size_type index = count[0] / 8 % blocksize;    //512分组的那个

		//位的更新数   
	if ((count[0] += (length << 3)) < (length << 3))
		count[1]++;
	count[1] += (length >> 29);

	// 我们需要填充的空间长度
	size_type firstpart = 64 - index;

	size_type i;


	//变换多次越好。
	if (length >= firstpart)
	{
		//首先填写缓冲区，转换
		memcpy(&buffer[index], input, firstpart);
		transform(buffer);

		//变换块大小的块（64字节）  分组处理
		for (i = firstpart; i + blocksize <= length; i += blocksize)
			transform(&input[i]);

		index = 0;
	}
	else
		i = 0;
	//输入的Input拷到Buffer后操作
	memcpy(&buffer[index], &input[i], length-i);
}
//为方便起见，转成无符号
// for convenience provide a verson with signed char
void MD5::update(const char input[], size_type length)
{
	update((const unsigned char*)input, length);
}
// MD5定稿。完一个MD5信息摘要操作，书写
//消息摘要和zeroizing上下文。
MD5& MD5::finalize()
{
	//padding 就有填充的意思  0x80 =  8x16x4 = 512位
	static unsigned char padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	if (!finalized) {
	//位保存号码
		unsigned char bits[8];
		encode(bits, count, 8);

		// pad out to 56 mod 64.
		// 56*8 = 448 
		size_type index = count[0] / 8 % 64;
		size_type padLen = (index < 56) ? (56 - index) : (120 - index);
		update(padding, padLen);
		//处理字符串长度和分组
		//附加长度（填充前）
  		update(bits, 8);


		//在消化存储状态
		encode(digest, state, 16);
		// 归零敏感信息。
		memset(buffer, 0, sizeof buffer);
		memset(count, 0, sizeof count);

		finalized=true;
	}

	return *this;
}

//返回消化的十六进制表示的字符串
std::string MD5::hexdigest() const
{
	if (!finalized) return "";

	char buf[33];
	for (int i=0; i<16; i++)
		sprintf(buf+i*2, "%02x", digest[i]);
	buf[32]=0;

	return std::string(buf);
}

std::ostream& operator<<(std::ostream& out, MD5 md5)
{
	return out << md5.hexdigest();
} 

std::string md5(const std::string str)
{
	MD5 md5 = MD5(str); 
	return md5.hexdigest();
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "MD5("") = " << md5("")  << endl;
	//cout << "MD5(\"admin\") = " << md5("admin") << endl;
	//cout << "MD5(\"1234567890\") = " << md5("1234567890") << endl;
	//cout << "MD5(\"汉子长字符串测试你能抗的住吗？你能体会宝宝现在的心情吗？爸爸的阿杜阿什顿我）="   << md5("汉子长字符串测试你能抗的住吗？你能体会宝宝现在的心情吗？爸爸的阿杜阿什顿我") << endl;
    return 0;
	/* 函数输出为：
	MD5("") = d41d8cd98f00b204e9800998ecf8427e
	MD5("admin") = 21232f297a57a5a743894a0e4a801fc3
	MD5("123456") = e10adc3949ba59abbe56e057f20f883e */
	
}
