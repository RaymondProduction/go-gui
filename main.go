package main

/*
#cgo LDFLAGS: -L. -lwxinterface
#include <stdlib.h>
#include <stdint.h>

// Declare callback function type
typedef void (*CallbackFunc)(int);

// External C functions
extern int CreateWindow(const char* title, int width, int height);
extern void AddButton(int windowId, const char* label, int x, int y, int width, int height, CallbackFunc callback, int id);
extern void WxShowWindow(int windowId);
extern void RunEventLoop();
extern void Cleanup();

// Wrapper function for callback
void CCallback(int id);
*/
import "C"
import (
	"fmt"
	"sync"
	"unsafe"
)

// Global callback registry
var (
	callbackRegistry = make(map[int]func())
	callbackMutex    sync.Mutex
	nextCallbackID   = 1
)

//export CCallback
func CCallback(id C.int) {
	fmt.Println("RUN CALLBACK ", id)
	callbackMutex.Lock()
	defer callbackMutex.Unlock()
	if callback, exists := callbackRegistry[int(id)]; exists {
		callback()
	}
}

func registerCallback(callback func()) int {
	callbackMutex.Lock()
	defer callbackMutex.Unlock()
	id := nextCallbackID
	nextCallbackID++
	callbackRegistry[id] = callback
	return id
}

func main() {
	// Create the window
	title := C.CString("Test Window")
	defer C.free(unsafe.Pointer(title))
	windowID := C.CreateWindow(title, 400, 400)

	// Add a button with a Go callback
	buttonLabel := C.CString("Click Me")
	defer C.free(unsafe.Pointer(buttonLabel))

	// Register the Go callback and get its ID
	callbackID := registerCallback(func() {
		fmt.Println("Go callback executed from button!")
	})

	fmt.Println("====> ", callbackID)

	// Pass the callback ID and function pointer to C
	C.AddButton(windowID, buttonLabel, 150, 100, 100, 50, C.CallbackFunc(C.CCallback), C.int(callbackID))

	// Show the window and run the event loop
	C.WxShowWindow(windowID)
	C.RunEventLoop()

	// Cleanup
	C.Cleanup()
}
