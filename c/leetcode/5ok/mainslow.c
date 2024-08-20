int checkPalindrome(char * s) {
    int i1 = 0;
    int i2 = strlen(s) - 1;
    while (i2 > i1) {
        if (s[i1] != s[i2]) {
            return 0;
        }
        ++i1;
        --i2;
    }
    return 1;
}

char * longestPalindrome(char * s){
    int len = strlen(s);
    int ind1 = 0, maxsize = 0, ind2 = 0;

    for (int i = 0; s[i] != '\0'; ++i) {
        for(int j = len - 1; j > i; --j) {
            if (j - i + 1 > maxsize) {
                char *a = malloc((j - i + 2) * sizeof(char));
                strncpy(a, s + i, j - i + 1);
                a[j - i + 1] = '\0';

                if (checkPalindrome(a) == 1) {
                    maxsize = j - i + 1;
                    ind1 = i;
                    ind2 = j;
                }
                free(a);
            }
        }
    }

    char * returned = malloc(ind2 - ind1 + 2);
    strncpy(returned, s + ind1, ind2 - ind1 + 1);
    returned[ind2 - ind1 + 1] = '\0';
    return returned;
}
