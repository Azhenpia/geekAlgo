class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int hold = 1;
        for(int i = digits.size() - 1; i >= 0; --i){
            digits[i] = digits[i] + hold;
            hold = digits[i] / 10;
            digits[i] %= 10;
            if(!hold) break;
        }
        if(hold) digits.insert(digits.begin(), 1);
        return digits;
    }
};