let addon: NodeAddon;

interface NodeAddon {
    windowFocusTopMost(): string;
}

interface WindowObject {
    focusOnTopMost(): string;
}

let windowObject: WindowObject;

(function main() {
    try {
        const { platform } = process;
        addon = require(`../build/Release/rinku_native_addons_${platform}.node`);
        windowObject = {
            focusOnTopMost(): string {
                return addon.windowFocusTopMost();
            }
        }
    } catch (err) {
        console.error("[rinku_node_addon] Unsupported platform! All primary functions are disabled!");
    }
})()

export { windowObject as window };