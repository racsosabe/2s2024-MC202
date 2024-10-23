#include<stdio.h>
#include<string.h>
#define N 300001
#define M 1001

char char_abs(char c) {
	return c <= 'Z' ? c + 'a' - 'A' : c; 
}

int isvowel(char c) {
	return isalpha(c) && (char_abs(c) == 'a' || char_abs(c) == 'e' || char_abs(c) == 'i' || char_abs(c) == 'o' || char_abs(c) == 'u');
}

int isconsonant(char c) {
	return isalpha(c) && !isvowel(c);
}

int main() {
	int i;
	char s[N];
	while(fgets(s, N, stdin) != NULL) {
		int sum = 0;
		int cur = 0;
		int at = 0;
		int len = strlen(s);
		for(i = 0; i < len; i++) {
			if(isdigit(s[i])) {
				cur = 10 * cur + s[i] - '0';
				continue;
			}
			sum += cur;
			cur = 0;
			if(s[i] != ' ' && !isalpha(s[i])) continue;
			if(s[i] == ' ') {
				if(at > 0 && s[at - 1] != ' ') s[at++] = s[i];
			}
			else s[at++] = s[i];
		}
		sum += cur;
		len = at;
		while(len > 0 && s[len - 1] == ' ') len--;
		printf("%d %s %s:", sum, (sum == 1 ? "goat" : "goats"), (sum == 1 ? "says" : "say"));
		int last = -1;
		if(len > 0) s[len++] = ' ';
		for(i = 0; i < len; i++) {
			if(s[i] == ' ') {
				putchar(' ');
				int l = last + 1, r = i - 1;
				int pos = 0, j;
				if(isvowel(s[l])) {
					for(j = l; j <= r; j++) putchar(s[j]);
				}
				else {
					for(j = l + 1; j <= r; j++) putchar(s[j]);
					putchar(s[l]);
				}
				printf("ma");
				for(j = l; j <= r; j++) putchar('a');
				last = i;
			}
		}
		puts("");
	}
	return 0;
}
