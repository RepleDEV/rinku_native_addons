#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <windows.h>
#include <string>
#include <cmath>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Integer;
using v8::Value;
using v8::Exception;
using v8::Number;

class Keyboard {
    public:
        static void keyDown(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 1 || !args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

            int keyCode = (int) args[0].As<Number>()->Value();

            INPUT input;
            WORD vkey = floor(keyCode);
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.wVk = vkey;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));
        }
        static void keyUp(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 1 || !args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

            int keyCode = (int) args[0].As<Number>()->Value();

            INPUT input;
            WORD vkey = floor(keyCode);
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.wVk = vkey;
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }
        static void keyPress(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            if (args.Length() < 1 || !args[0]->IsNumber()) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

            int keyCode = (int) args[0].As<Number>()->Value();

            if (keyCode > 255) {
                isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(
                        isolate,
                        "INVALID ARGS"
                    ).ToLocalChecked()
                ));

                return;
            }

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
        }
};

#endif;