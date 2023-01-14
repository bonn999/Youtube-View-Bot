#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <string>
using namespace std;

void openW(string url) { // import string url then pass command in prompt window to start chrome
    string command = "start /B chrome.exe " + url;
    system(command.c_str());
}

void start() { // sleep for 2 seconds and press the space bar to start the video
    std::this_thread::sleep_for(std::chrono::seconds(2));
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_SPACE;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
}

void MinW() { // pass keyboard events to window to minimize window
    keybd_event(VK_LWIN, 0x5B, 0, 0);
    keybd_event(VK_DOWN, 0x28, 0, 0);
    keybd_event(VK_LWIN, 0x5B, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_DOWN, 0x28, KEYEVENTF_KEYUP, 0);
}

void closeW() { // pass command to prompt to kill chrome
    system("taskkill /F /IM chrome.exe");
}

int main() {
    string url, ipPath;
    int min, max, loop, sPlay, winM;
    cout << "Enter the url " << endl;
    cin >> url;
    cout << "Enter the minimum time " << endl;
    cin >> min;
    cout << "Enter the maximum time " << endl;
    cin >> max;
    cout << "From " << min << " to " << max << " selected." << endl;
    cout << "Enter path to the ip list to use " << endl;
    cin >> ipPath;
    cout << "Enter the amout of loops/views " << endl;
    cin >> loop;
    cout << "Do you need to send a input to automatically start the video? " << endl << endl << "Yes = 1 No = 0 ";
    cin >> sPlay;
    cout << "Do you wish to minimize the window after it opens?" << endl << endl << "Yes = 1 No = 0 ";
    cin >> winM;
    cout << endl << endl;
    vector<string> IPs;
    ifstream file(ipPath);
    if (file.is_open()) {
        string ip;
        while (getline(file, ip)) {
            IPs.push_back(ip);
        }
        file.close();
    }
    else {
        cout << "Unable to open file at specified path." << endl;
        return 0;
    }
    for (int i = 0; i < loop; i++) {
        if (IPs.empty()) {
            cout << "No more IPs" << endl;
            break;
        }
        string newIP = IPs.back();
        IPs.pop_back(); // this will change the internet settings   interface used                          ip from list     mask        gateway   ---- You can chage whatever you want here
        string command = "netsh interface ipv4 set address name=\"Interface Area Connection\" source=static " + newIP + " 255.255.255.0 192.168.1.1";
        system(command.c_str()); // just remember line 92 is to reset your settings back to original, be sure to run program all the way through or you will have to manually reset
        openW(url); //              your internet settings, if you have to manually reset use commands in line 92 to do so
        if (sPlay > 0) {
            start();
        }
        if (winM > 0) {
            MinW();
        }
        int random = rand() % (max - min + 1) + min;
        std::this_thread::sleep_for(std::chrono::seconds(random));
        closeW();
    }
                  // resets your original settings              place original interface                 original IP,      Mask       Gateway
    string command2 = "netsh interface ipv4 set address name=\"Interface Area Connection\" source=static 'Original Ip' 255.255.255.0 192.168.1.1";
    system(command2.c_str()); // if you were using DHCP and want that back on use command "netsh interface ipv4 set address name=\"Local Area Connection\" source=dhcp"
    return main();
}
/*
use command prompt with command
    
    -- netsh interface ipv4 show address
    
"With whatever interface you are useing you will place the interface in"
    
    -- /"INTERFACE-HERE/"

if DHCP is on and program is showing an error trying to use the command make sure this program is being ran in administrator mode
if it still didnt work manually config your network settings to make it take a static ip
*/
