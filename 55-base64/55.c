#include<stdio.h>

char chr(int x) {
    if(x < 26) return 'A' + x;
    if(x < 52) return 'a' + x - 26;
    if(x < 62) return '0' + x - 52;
    return x == 62 ? '+' : '/';
}

int id_hex(char c) {
    return c <= '9' ? c - '0' : 10 + c - 'A';
}

int main() {
    int n;
    scanf("%d", &n);
    char s[4];
    int carry[24];
    for(int i = 0; i < n; i += 3) {
        int cnt = (i + 3 <= n ? i + 3 : n) - i;
        int at = 0;
        for(int j = 0; j < cnt; j++) {
            scanf("%s", s);
            for(int p = 0; p < 2; p++) {
                int to = at + 3;
                int val = id_hex(s[p]);
                for(int k = 0; k < 4; k++) {
                    carry[to--] = val % 2;
                    val /= 2;
                }   
                at += 4;
            }
        }
        while(at % 6) carry[at++] = 0;
        int pos = 0;
        int chars = at / 6;
        for(int j = 0; j < chars; j++) {
            int val = 0;
            for(int k = 0; k < 6; k++) {
                val *= 2;
                val += carry[pos++];
            }
            putchar(chr(val));
        }
        while(chars < 4) {
            putchar('=');
            chars++;
        }
    }
    puts("");
    return 0;
}