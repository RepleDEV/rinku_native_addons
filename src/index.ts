let addon: NodeAddon;

interface NodeAddon {
    // Window functions
    windowFocusTopMost(): string;

    // Keyboard functions
    keyboardKeyPress(keyCode: number): void;
    keyboardKeyDown(keyCode: number): void;
    keyboardKeyUp(keyCode: number): void;

    // Mouse functions
    mouseMove(x: number, y: number): void;
}

interface WindowObject {
    focusOnTopMost(): string;
}

interface KeyboardObject {
    keyPress(keyCode: number): void;
    keyDown(keyCode: number): void;
    keyUp(keyCode: number): void;
}

interface MouseObject {
    move(x: number, y: number): void;
}

let windowObject: WindowObject;
let keyboardObject: KeyboardObject;
let mouseObject: MouseObject;

try {
    const { platform } = process;
    addon = require(`../build/Release/rinku_native_addons_${platform}.node`);
    windowObject = {
        focusOnTopMost(): string {
            return addon.windowFocusTopMost();
        },
    };
    keyboardObject = {
        keyPress(keyCode: number): void {
            if (keyCode > 255) throw new Error("Invalid argument");

            addon.keyboardKeyPress(keyCode);
        },
        keyDown(keyCode: number): void {
            if (keyCode > 255) throw new Error("Invalid argument");

            addon.keyboardKeyDown(keyCode);
        },
        keyUp(keyCode: number): void {
            if (keyCode > 255) throw new Error("Invalid argument");

            addon.keyboardKeyUp(keyCode);
        }
    };
    mouseObject = {
        move(x: number, y: number): void {
            addon.mouseMove(x, y);
        }
    };
} catch (err) {
    console.error(
        "[rinku_node_addon] Unsupported platform! All primary functions are disabled!"
    );
}

export {
    windowObject as window,
    keyboardObject as keyboard,
    mouseObject as mouse
};
