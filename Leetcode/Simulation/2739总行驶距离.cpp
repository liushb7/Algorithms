class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int dis = 0;
        while(mainTank >= 5 && additionalTank > 0){
            mainTank -= 5;
            additionalTank -= 1;
            mainTank += 1;
            dis += 50;
        }
        if(mainTank > 0){
            dis += mainTank * 10;
        }
        return dis;
    }
};
