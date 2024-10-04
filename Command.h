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
    Command() {
        while (1) {
            cout << "Enter Command: ";
            char temp[20];
            cin.getline(temp, 19);
            command = temp[0];

            if (command == 'm') {
                if (temp[2] == 'w') {
                    source[0] = temp[2];
                    source[1] = '\0';
                    if (temp[4] == 'c') {
                        destination[0] = temp[4];
                        if ((temp[5] - '0') >= 1 && (temp[5] - '0') <= 7) destination[1] = temp[5];
                        else {
                            cout << "Error in Command. ";
                            continue;
                        }
                        destination[2] = '\0';
                    }
                    else {
                        cout << "Error in Command. ";
                        continue;
                    }
                    if (temp[7] == ' ') {
                        cout << "Error in Command. ";
                        continue;
                    }
                    num = extractNumber(temp, 7);
                    Move();
                }
                else if (temp[2] == 'c') {
                    source[0] = temp[2];
                    if((temp[3]-'0') >= 1 && (temp[3] - '0') <= 7) source[1] = temp[3];
                    else {
                        cout << "Error in Command. ";
                        continue;
                    }
                    if (temp[6] == ' ') {
                        cout << "Error in Command. ";
                        continue;
                    }
                    source[2] = '\0';
                    if (temp[5] == 'c') {
                        destination[0] = temp[5];
                        if ((temp[6] - '0') >= 1 && (temp[6] - '0') <= 7) destination[1] = temp[6];
                        else {
                            cout << "Error in Command. ";
                            continue;
                        }
                        if (temp[6] == ' ') {
                            cout << "Error in Command. ";
                            continue;
                        }
                        destination[2] = '\0';
                    }
                    else {
                        cout << "Error in Command. ";
                        continue;
                    }
                    num = extractNumber(temp, 8);
                    Move();
                }
                else {
                    cout << "Error in Command. ";
                    continue;
                }
            }
            else if (command == 's') {
                Draw();
            }
            else if (command == 'z') {
                Undo();
            }
            else {
                cout << "Error in Command. ";
                continue;
            }
        }
    }
    void Undo() {
        cout << "Doing Undo" << endl;
    }
    void Move() {
        cout << "moving from " << source << " to " << destination << " " << num << " cards" << endl;
    }
    void Draw() {
        cout << "Doing Draw" << endl;
    }
};