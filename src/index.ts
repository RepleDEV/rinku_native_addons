let addon: NodeAddon;

interface NodeAddon {
    windowFocusTopMost(): string;
    keyboardKeyPress(keyCode: number): void;
    keyboardKeyDown(keyCode: number): void;
    keyboardKeyUp(keyCode: number): void;
}

interface WindowObject {
    focusOnTopMost(): string;
}

interface KeyboardObject {
    keyPress(keyCode: number): void;
    keyDown(keyCode: number): void;
    keyUp(keyCode: number): void;
}

let windowObject: WindowObject;
let keyboardObject: KeyboardObject;

(function main() {
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
        }
    } catch (err) {
        console.error(
            "[rinku_node_addon] Unsupported platform! All primary functions are disabled!"
        );
    }
})();

export { windowObject as window, keyboardObject as keyboard };
