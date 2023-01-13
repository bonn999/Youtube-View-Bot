#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <string>
using namespace std;

void openChrome(string url) {
    // Start a new background instance of Chrome
    string command = "start /B chrome.exe " + url;
    system(command.c_str());
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Simulate key press to play the video
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_SPACE; // VK_SPACE is the virtual key code for the spacebar
    input.ki.dwFlags = 0; // 0 for key press, KEYEVENTF_KEYUP for key release
    SendInput(1, &input, sizeof(INPUT));

    // Minimize the chrome window
    keybd_event(VK_LWIN, 0x5B, 0, 0);
    keybd_event(VK_DOWN, 0x28, 0, 0);
    keybd_event(VK_LWIN, 0x5B, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_DOWN, 0x28, KEYEVENTF_KEYUP, 0);

}

void closeChrome() {
    system("taskkill /F /IM chrome.exe");
}

int main() {
    string url;
    int min_seconds, max_seconds, loop;
    cout << "Enter the URL you want to open: " << endl << endl;
    cin >> url;
    cout << "Please enter the min time to watch video in seconds and then enter the max time" << endl << endl;
    cin >> min_seconds;
    cin >> max_seconds;
    cout << "From " << min_seconds << " to " << max_seconds << "selected." << endl << endl;
    cout << "Enter the number of loops/views: " << endl << endl;
    cin >> loop;
    string filepath;
    cout << "Enter path of the file containing the IP addresses: " << endl << endl;
    cin >> filepath;
    cout << endl << endl;
    vector<string> IPs;

    // Open the file and read the IP addresses into the vector
    ifstream file(filepath);
    if (file.is_open()) {
        string ip;
        while (getline(file, ip)) {
            IPs.push_back(ip);
        }
        file.close();
    }
    else {
        cout << "Unable to open the file at the specified path." << endl;
        return 0;
    }

    for (int i = 0; i < loop; i++) {
        if (IPs.empty()) {
            cout << "No more IPs" << endl;
            break;
        }
        string newIP = IPs.back();
        IPs.pop_back();
        string command = "netsh interface ipv4 set address \"Local Area Connection\" static " + newIP + " 255.255.255.0 192.168.1.1";
        system(command.c_str());
        openChrome(url);
        int random_seconds = rand() % (max_seconds - min_seconds + 1) + min_seconds;
        std::this_thread::sleep_for(std::chrono::seconds(random_seconds));
        closeChrome();
    }
    // This will restore your ip back to original     this can be changed if you wish     right here <--- set your original ip to reset it back to normal whe the program has finished
    string command2 = "netsh interface ipv4 set address \"Local Area Connection\" static 'Place Ip here' 255.255.255.0 192.168.1.1";
    system(command2.c_str());
    return main();
}