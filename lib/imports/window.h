#ifndef WINDOW_H_
#define WINDOW_H_

#include <napi.h>
#include <windows.h>
#include <string>
#include <vector>

#include "common.h"

using Napi::String;
using Napi::CallbackInfo;
using Napi::Env;
using Napi::Array;
using Napi::TypeError;
using Napi::Number;

std::vector<HWND> windowArray;
int nthWindow;

class Window {
    public: 
        static std::string GetTitle(HWND window) {
            char wnd_title[256];
            GetWindowText(window, wnd_title, sizeof(wnd_title));

            return Common::charToString(wnd_title, GetWindowTextLength(window) + 1);
        }

        static String FocusTopmost(const CallbackInfo& info) {
            Env env = info.Env();

            windowArray = {};

            EnumWindows(EnumWindowsProcGetAllWindows, NULL);

            HWND hWnd = windowArray[0];

            windowArray = {};

            if (isForeground(hWnd)) {
                return String::New(
                    env,
                    GetTitle(hWnd)
                );
            }

            HWND previousWindow = focusOnWindow(hWnd);

            return String::New(
                env,
                ("Changed window from: " + GetTitle(previousWindow) + " to: " + GetTitle(hWnd))
            );
        }

        static String FocusOnNthWindow(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT LENGTH"
                ).ThrowAsJavaScriptException();

                return String::New(env, "");
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT TYPE"
                ).ThrowAsJavaScriptException();

                return String::New(env, "");
            }

            int n = ((int) info[0].As<Number>().DoubleValue()) - 1;

            if (n < 0)n = 0;

            windowArray = {};

            EnumWindows(EnumWindowsProcGetAllWindows, NULL);

            HWND hWnd = windowArray[n];

            windowArray = {};

            if (isForeground(hWnd)) {
                return String::New(
                    env,
                    GetTitle(hWnd)
                );
            }

            HWND previousWindow = focusOnWindow(hWnd);

            return String::New(
                env,
                ("Changed window from: " + GetTitle(previousWindow) + " to: " + GetTitle(hWnd))
            );
        }

        static Array GetAllWindowTitles(const CallbackInfo& info) {
            Env env = info.Env();

            windowArray = {};

            EnumWindows(EnumWindowsProcGetAllWindows, NULL);

            Array res = Array::New(env);

            for (int i = 0;i < windowArray.size();++i) {
                res.Set(i, GetTitle(windowArray[i]));
            }

            windowArray = {};

            return res;
        }

        static BOOL CALLBACK EnumWindowsProcGetAllWindows(HWND hWnd, LPARAM lParam) {
            int windowLength = GetWindowTextLength(hWnd);
            if (windowLength == 0 || !IsWindowVisible(hWnd))return TRUE;
            windowArray.push_back(hWnd);
            return TRUE;
        }

        static bool isForeground(HWND wind) {
            return wind == GetForegroundWindow();
        }

        static HWND focusOnWindow(HWND hWnd) {
            if (!isForeground(hWnd)) {
                // From: https://github.com/sentialx/node-window-manager/blob/master/lib/windows.cc#L319
                // License: https://github.com/sentialx/node-window-manager/blob/master/LICENSE
                SetForegroundWindow(hWnd);
                
                HWND hCurWnd = GetForegroundWindow();
                DWORD dwMyID = GetCurrentThreadId();
                DWORD dwCurID = GetWindowThreadProcessId(hCurWnd, NULL);
                AttachThreadInput(dwCurID, dwMyID, TRUE);
                BringWindowToTop(hWnd);
                SetForegroundWindow(hWnd);
                AttachThreadInput(dwCurID, dwMyID, FALSE);
                SetFocus(hWnd);
                SetActiveWindow(hWnd);

                return hCurWnd;
            } else {
                return hWnd;
            }
        }
};

#endif