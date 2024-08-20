int lengthOfLongestSubstring(char * s){
    if (s[0] == '\0') return 0;

    char map[200] = {0};

    int start = 0, result = 1, tlen;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (map[s[i]] > 0) {
            start = start > map[s[i]] ? start : map[s[i]];
        }

        map[s[i]] = i + 1;
        tlen = map[s[i]] - start;
        result = (tlen > result) ? tlen : result;
    }

    return result;
}
