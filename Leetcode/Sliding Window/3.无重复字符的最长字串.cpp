class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;
        int ans = 0, l = 0, n = s.size();
        for(int r = 0; r < n; r ++){
            mp[s[r]]++;
            while(mp[s[r]] > 1){
                mp[s[l]]--;
                l += 1;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
