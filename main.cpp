class Solution {
public:
    bool validUtf8(vector<int>& data) {
        for (auto const &x : data) {
            if (!StateMachine(x))
                return false;
        }
        if(expected_bytes > 0)
            return false;
        return true;
    }
private:
    int ReadBit(int data, int index)
    {
        return (data >> index) & 1;
    }
    
    int expected_bytes = 0;
    bool StateMachine(int data)
    {
        if(expected_bytes > 0) {
            if ((data >> 6) != 0b10)
                return false;
            expected_bytes--;
        } else { //expected bytes == 0
            
            if (ReadBit(data, 7) == 1) { //we expect start of byte
                if ((data >> 5) == 0b110)
                    expected_bytes = 1;
                else if ((data >> 4) == 0b1110)
                    expected_bytes = 2;
                  else if ((data >> 3) == 0b11110)
                    expected_bytes = 3;
                else 
                    return false;
            }  // in else branch we got 1 byte char so just moving to next state
        }
        return true;
    }
};
