#pragma once
#include<iostream>
#include<cstring>
class Command {
private:
    char command;
    char source[3];
    char destination[3];
    int num;

    int extractNumber(char* str, int startPos) {
        int result = 0;
        int i = startPos;
        while (str[i] >= '0' && str[i] <= '9') {
            result = (result * 10) + (str[i] - '0');
            i++;
        }
        return result;
    }

public:
    void getInput() {
        while (1) {
            cout << "Enter Command: ";
            char temp[20] = "\0";
            cin.getline(temp, 19);
            command = temp[0];
            if (command == 's') {
                if (temp[1] == '\0')
                return;
            }
            else if (command == 'o') {
                if (temp[1] == '\0')
                    return;
            }
            else if (command == 'u') {
                if (temp[1] == '\0')
                    return;
            }
            else if (command == 'e') {
                if (temp[1] == '\0')
                    return;
            }
            else if (command == 'z') {
                if(temp[1] == '\0')
                return;
            }
            if (command == 'm') {
                if (temp[2] == 'w') {
                    source[0] = temp[2];
                    source[1] = '\0';
                    if (temp[4] == 'c' || temp[4] == 'f') {
                        destination[0] = temp[4];
                        if (temp[4] == 'c') {
                            if ((temp[5] - '0') >= 1 && (temp[5] - '0') <= 7) destination[1] = temp[5];
                            else {
                                cout << "Error in Command. ";
                                continue;
                            }
                        }
                        else if (temp[4] == 'f') {
                            if ((temp[5] - '0') >= 1 && (temp[5] - '0') <= 4) destination[1] = temp[5];
                            else {
                                cout << "Error in Command. ";
                                continue;
                            }
                        }
                        destination[2] = '\0';
                    }
                    else {
                        cout << "Error in Command. ";
                        continue;
                    }
                    if (!(temp[7] >= '0' && temp[7] <= '9')) {
                        cout << "Error in Command. ";
                        continue;
                    }
                    num = extractNumber(temp, 7);
                    return;
                }
                else if (temp[2] == 'c') {
                    source[0] = temp[2];
                    if ((temp[3] - '0') >= 1 && (temp[3] - '0') <= 7) source[1] = temp[3];
                    else {
                        cout << "Error in Command. ";
                        continue;
                    }
                    if (temp[5] == ' ') {
                        cout << "Error in Command. ";
                        continue;
                    }
                    source[2] = '\0';
                    if (temp[5] == 'c' || temp[5] == 'f') {
                        destination[0] = temp[5];
                        if (temp[5] == 'c') {
                            if ((temp[6] - '0') >= 1 && (temp[6] - '0') <= 7) destination[1] = temp[6];
                            else {
                                cout << "Error in Command. ";
                                continue;
                            }
                            if (temp[6] == ' ') {
                                cout << "Error in Command. ";
                                continue;
                            }
                        }
                        else if (temp[5] == 'f') {
                            if ((temp[6] - '0') >= 1 && (temp[6] - '0') <= 4) destination[1] = temp[6];
                            else {
                                cout << "Error in Command. ";
                                continue;
                            }
                            if (temp[6] == ' ') {
                                cout << "Error in Command. ";
                                continue;
                            }
                        }
                        destination[2] = '\0';
                    }
                    else {
                        cout << "Error in Command. ";
                        continue;
                    }
                    if (!(temp[8] >= '0' && temp[8] <= '9')) {
                        cout << "Error in Command. ";
                        continue;
                    }
                    num = extractNumber(temp, 8);
                    return;
                }
                else {
                    cout << "Error in Command. ";
                    continue;
                }
            }
            else {
                cout << "Error in Command. ";
                continue;
            }
        }
    }
    char getCommand() { return command; }
    char* getSource() { return source; }
    char* getDest() { return destination; }
    int getNum() { return num; }
};