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
    string command = "start chrome.exe " + url;
    system(command.c_str());

}

void openWM(string url) {
    string command3 = "start /min chrome.exe " + url;
    system(command3.c_str());
}

void startVid() {
    this_thread::sleep_for(std::chrono::seconds(2));
    INPUT input[2];
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_SPACE;
    input[0].ki.dwFlags = 0;
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_SPACE;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
}

void closeW() { // pass command to prompt to kill chrome
    system("taskkill /F /IM chrome.exe");
}

int main() {

    string url, ipPath;
    int min, max, loop;
    char startV, shortW;
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
    cout << "Do you need to send a input to automatically start the video? " << endl << endl << "Note that this will send the keyStroke (SPACE BAR) to the window to start the video" << endl << "    y/n ";
    cin >> startV;
    cout << "Do you wish to minimize the window after it opens?" << endl << endl << "Note that this may only work if the window is not minimized." << endl << "    y/n ";
    cin >> shortW;
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
        if (startV == 'y') { //     your internet settings, if you have to manually reset use commands in line 92 to do so
            startVid();
        }
        if (shortW == 'y') {
            openWM(url);
            int random = rand() % (max - min + 1) + min;
            std::this_thread::sleep_for(std::chrono::seconds(random));
            closeW();
        }
        if(shortW == 'n') {
            openW(url);
            int random = rand() % (max - min + 1) + min;
            std::this_thread::sleep_for(std::chrono::seconds(random));
            closeW();
        }

    }
                  // resets your original settings              place original interface                 original IP,      Mask       Gateway
    string command2 = "netsh interface ipv4 set address name=\"Interface Area Connection\" source=static 'Original IP' 255.255.255.0 192.168.1.1";
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
