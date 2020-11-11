#include <node.h>
#include <napi.h>
#include <windows.h>

#include "imports/window.h"
#include "imports/keyboard.h"
#include "imports/mouse.h"

using Napi::Object;
using Napi::String;
using Napi::Function;
using Napi::Env;

Object init(Env env, Object exports) {
    // Window functions
    exports.Set(
        String::New(
            env,
            "windowFocusTopMost"
        ),
        Function::New(
            env,
            Window::FocusTopmost
        )
    );

    exports.Set(
        String::New(
            env,
            "windowGetAllTitles"
        ),
        Function::New(
            env,
            Window::GetAllWindowTitles
        )
    );

    exports.Set(
        String::New(
            env,
            "windowFocusOnNthWindow"
        ),
        Function::New(
            env,
            Window::FocusOnNthWindow
        )
    );

    // Keyboard functions
    exports.Set(
        String::New(
            env,
            "keyboardKeyPress"
        ),
        Function::New(
            env,
            Keyboard::keyPress
        )
    );
    exports.Set(
        String::New(
            env,
            "keyboardKeyDown"
        ),
        Function::New(
            env,
            Keyboard::keyDown
        )
    );
    exports.Set(
        String::New(
            env,
            "keyboardKeyUp"
        ),
        Function::New(
            env,
            Keyboard::keyUp
        )
    );

    // Mouse functions
    exports.Set(
        String::New(
            env,
            "mouseMove"
        ),
        Function::New(
            env,
            Mouse::move
        )
    );
    exports.Set(
        String::New(
            env,
            "mouseDown"
        ),
        Function::New(
            env,
            Mouse::down
        )
    );
    exports.Set(
        String::New(
            env,
            "mouseUp"
        ),
        Function::New(
            env,
            Mouse::up
        )
    );
    exports.Set(
        String::New(
            env,
            "mouseClick"
        ),
        Function::New(
            env,
            Mouse::click
        )
    );

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, init);