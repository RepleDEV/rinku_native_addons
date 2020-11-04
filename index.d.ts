/// <reference types="node" />

declare interface WindowObject {
    focusOnTopMost(): string;
}

/**
 * Window functions.
 */
declare const windowObject: WindowObject = {
    /**
     * Set window focus to window with highest z-order.
     */
    focusOnTopMost(): string;,
};

export { windowObject as window };
