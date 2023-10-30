char * longestPalindrome(char * s) {
    int len = strlen(s);
    if (len <= 1) {
        return s;
    }

    int start = 0;
    int maxLen = 1;
    int dp[len][len];

    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < len; i++) {
        dp[i][i] = 1;
    }

    for (int i = 0; i < len - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = 1;
            start = i;
            maxLen = 2;
        }
    }

    for (int k = 3; k <= len; k++) {
        for (int i = 0; i < len - k + 1; i++) {
            int j = i + k - 1;

            if (dp[i + 1][j - 1] && s[i] == s[j]) {
                dp[i][j] = 1;

                if (k > maxLen) {
                    start = i;
                    maxLen = k;
                }
            }
        }
    }

    char *result = (char *)malloc(maxLen + 1);
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0';

    return result;
}
