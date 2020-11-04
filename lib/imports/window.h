#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include <string>
#include "common.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Integer;
using v8::Value;

HWND topMostWindow;

class Window {
    public: 
        static std::string GetTitle(HWND window) {
            char wnd_title[256];
            GetWindowText(window, wnd_title, sizeof(wnd_title));

            return Common::charToString(wnd_title, GetWindowTextLength(window) + 1);
        }

        static void FocusTopmost(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            EnumWindows(EnumWindowsProc, NULL);

            HWND hWnd = topMostWindow;
            topMostWindow = NULL;

            if (!isForeground(hWnd)) {
                // From: https://github.com/sentialx/node-window-manager/blob/master/lib/windows.cc#L319
                // License: https://github.com/sentialx/node-window-manager/blob/master/LICENSE
                SetForegroundWindow(hWnd);
                
                HWND hCurWnd = GetForegroundWindow();
                DWORD dwMyID = GetCurrentThreadId();
                DWORD dwCurID = GetWindowThreadProcessId (hCurWnd, NULL);
                AttachThreadInput (dwCurID, dwMyID, TRUE);
                BringWindowToTop(hWnd);
                SetForegroundWindow (hWnd);
                AttachThreadInput (dwCurID, dwMyID, FALSE);
                SetFocus (hWnd);
                SetActiveWindow (hWnd);

                args.GetReturnValue().Set(
                    String::NewFromUtf8(
                        isolate,
                        ("Changed window from: " + GetTitle(hCurWnd) + " to: " + GetTitle(hWnd)).c_str()
                    ).ToLocalChecked()
                );
            } else {
                args.GetReturnValue().Set(
                    String::NewFromUtf8(
                        isolate,
                        GetTitle(hWnd).c_str()
                    ).ToLocalChecked()
                );
            }
        };

        static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
            int windowLength = GetWindowTextLength(hWnd);
            if (windowLength == 0 || !IsWindowVisible(hWnd) || topMostWindow != NULL)return TRUE;
            topMostWindow = hWnd;
            return TRUE;
        }
        static bool isForeground(HWND wind) {
            return wind == GetForegroundWindow();
        }
};

#endif