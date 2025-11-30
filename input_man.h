#ifndef INPUT_MAN_H
#define INPUT_MAN_H

class InputManager {
public:
    static int askInteger(const char* message, int minVal, int maxVal);
};

#endif 