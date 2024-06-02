#pragma once
#include <string>

namespace ascii_io
{
	void print(const std::string& output);
	int getchar();
	void clear();
	void reset();
	std::string getline();
	void get_terminal_size(int& x, int& y);
	
	const int space = 32;
	const int exclamation = 33;
	const int double_quoatation = 34;
	const int pound = 35;
	const int dollar = 36;
	const int percent = 37;
	const int ampersand = 38;
	const int single_quotation = 39;
	const int begin_parentheses = 40;
	const int end_parentheses = 41;
	const int asterisk = 42;
	const int plus = 43;
	const int comma = 44;
	const int minus = 45;
	const int period = 46;
	const int forward_slash = 47;
	const int zero = 48;
	const int one = 49;
	const int two = 50;
	const int three = 51;
	const int four = 52;
	const int five = 53;
	const int six = 54;
	const int seven = 55;
	const int eight = 56;
	const int nine = 57;
	const int colon = 58;
	const int semi_colon = 59;
	const int less_than = 60;
	const int equal = 61;
	const int greater_than = 62;
	const int question = 63;
	const int at_sign = 64;
	const int A = 65;
	const int B = 66;
	const int C = 67;
	const int D = 68;
	const int E = 69;
	const int F = 70;
	const int G = 71;
	const int H = 72;
	const int I = 73;
	const int J = 74;
	const int K = 75;
	const int L = 76;
	const int M = 77;
	const int N = 78;
	const int O = 79;
	const int P = 80;
	const int Q = 81;
	const int R = 82;
	const int S = 83;
	const int T = 84;
	const int U = 85;
	const int V = 86;
	const int W = 87;
	const int X = 88;
	const int Y = 89;
	const int Z = 90;
	const int begin_bracket = 91;
	const int backslash = 92;
	const int end_bracket = 93;
	const int caret = 94;
	const int underscore = 95;
	const int back_quote = 96;
	const int a = 97;
	const int b = 98;
	const int c = 99;
	const int d = 100;
	const int e = 101;
	const int f = 102;
	const int g = 103;
	const int h = 104;
	const int i = 105;
	const int j = 106;
	const int k = 107;
	const int l = 108;
	const int m = 109;
	const int n = 110;
	const int o = 111;
	const int p = 112;
	const int q = 113;
	const int r = 114;
	const int s = 115;
	const int t = 116;
	const int u = 117;
	const int v = 118;
	const int w = 119;
	const int x = 120;
	const int y = 121;
	const int z = 122;
	const int begin_curly_bracket = 123;
	const int pipe = 124;
	const int end_curly_bracket = 125;
	const int tilde = 126;
	const int DEL = 127;
}