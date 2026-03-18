#pragma once
#include "Singleton.h"
#include <map>
#include <vector>
#include <memory>
#include <tuple>

namespace dae
{
    enum class ControllerButton {
        DpadUp = 0x0001,
        DpadDown = 0x0002,
        DpadLeft = 0x0004,
        DpadRight = 0x0008,
        Start = 0x0010,
        Back = 0x0020,
        LeftThumb = 0x0040,
        RightThumb = 0x0080,
        LeftShoulder = 0x0100,
        RightShoulder = 0x0200,
        ButtonA = 0x1000,
        ButtonB = 0x2000,
        ButtonX = 0x4000,
        ButtonY = 0x8000,
        None
    };

    enum class KeyState { Down, Up, Pressed };

    struct CommandKey {
        unsigned int id;
        ControllerButton button;
        KeyState state;
        bool isController;

        bool operator<(const CommandKey& other) const {
            return std::forward_as_tuple(id, (int)button, state, isController) <
                std::forward_as_tuple(other.id, (int)other.button, other.state, other.isController);
        }
    };

    class Command;          
    class XInputController; 

    class InputManager final : public Singleton<InputManager>
    {
    public:
        InputManager();
        ~InputManager();

        void BindCommand(CommandKey key, std::unique_ptr<Command> command);
        bool ProcessInput();

    private:
        std::map<CommandKey, std::unique_ptr<Command>> m_Commands;
        std::vector<std::unique_ptr<XInputController>> m_Controllers;
    };
}