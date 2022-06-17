def solve(str1, str2, m, n): 
    # dp table to store results of subproblems 
    dp = [[0 for x in range(n + 1)] for x in range(m + 1)] 
  
    for i in range(m + 1): 
        for j in range(n + 1): 
  
            # first string is empty => insert all characters of second string 
            if i == 0: 
                dp[i][j] = j
  
            # second string is empty => remove all characters of second string 
            elif j == 0: 
                dp[i][j] = i
  
            # last characters are same => ignore last character and recurce for remaining
            elif str1[i-1] == str2[j-1]: 
                dp[i][j] = dp[i-1][j-1] 
  
            # last characters are different => check all options to find minimum 
            else: 
                dp[i][j] = 1 + min(dp[i][j-1],       
                                   dp[i-1][j],       
                                   dp[i-1][j-1])   
  
    return dp[m][n] 


def main():
    str1 = "ggact"
    str2 = "gctga"
  
    print(solve(str1, str2, len(str1), len(str2))) 
    

if __name__ == "__main__":
    main()
