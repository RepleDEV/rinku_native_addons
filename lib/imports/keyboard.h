#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <napi.h>
#include <windows.h>
#include <string>
#include <cmath>

using Napi::String;
using Napi::CallbackInfo;
using Napi::Env;
using Napi::Number;
using Napi::TypeError;
using Napi::Value;

class Keyboard {
    public:
        static Value keyDown(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT AMOUNT"
                ).ThrowAsJavaScriptException();

                return env.Null();
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPES"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int keyCode = (int) info[0].As<Number>().DoubleValue();

            INPUT input;
            WORD vkey = floor(keyCode);
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.wVk = vkey;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));

            return env.Undefined();
        }
        static Value keyUp(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT AMOUNT"
                ).ThrowAsJavaScriptException();

                return env.Null();
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPES"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int keyCode = (int) info[0].As<Number>().DoubleValue();

            INPUT input;
            WORD vkey = floor(keyCode);
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.wVk = vkey;
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

            return env.Undefined();
        }
        static Value keyPress(const CallbackInfo& info) {
            Env env = info.Env();

            if (info.Length() < 1) {
                TypeError::New(
                    env,
                    "INVALID ARGUMENT AMOUNT"
                ).ThrowAsJavaScriptException();

                return env.Null();
            } else if (!info[0].IsNumber()) {
                TypeError::New(
                    env,
                    "INVALID ARUMENT TYPES"
                ).ThrowAsJavaScriptException();

                return env.Undefined();
            }

            int keyCode = (int) info[0].As<Number>().DoubleValue();

            INPUT input;
            WORD vkey = floor(keyCode);
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.wVk = vkey;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

            return env.Undefined();
        }
};

#endif;