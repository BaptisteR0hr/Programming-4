#define WIN32_LEAN_AND_MEAN 
#include <windows.h>       
#include <Xinput.h>        
#include "XInputController.h"

#pragma comment(lib, "xinput.lib") 

namespace dae {
    class XInputController::XInputControllerImpl {
        unsigned int m_Index;
        XINPUT_STATE m_PreviousState{};
        XINPUT_STATE m_CurrentState{};
        unsigned int m_ButtonsPressedThisFrame{};
        unsigned int m_ButtonsReleasedThisFrame{};

    public:
        XInputControllerImpl(unsigned int index) : m_Index(index) {}

        void Update() {
            m_PreviousState = m_CurrentState;
            ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
            XInputGetState(m_Index, &m_CurrentState);

            auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
            m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
            m_ButtonsReleasedThisFrame = buttonChanges & m_PreviousState.Gamepad.wButtons;
        }

        bool IsDown(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }
        bool IsPressed(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
        bool IsUp(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
    };

    XInputController::XInputController(unsigned int index) : pImpl(std::make_unique<XInputControllerImpl>(index)) {}
    XInputController::~XInputController() = default;
    void XInputController::Update() { pImpl->Update(); }
    bool XInputController::IsDown(unsigned int button) const { return pImpl->IsDown(button); }
    bool XInputController::IsPressed(unsigned int button) const { return pImpl->IsPressed(button); }
    bool XInputController::IsUp(unsigned int button) const { return pImpl->IsUp(button); }
}