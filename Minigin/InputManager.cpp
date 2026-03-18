#include <SDL3/SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#include "Command.h"        
#include "XInputController.h"

dae::InputManager::InputManager() {
    m_Controllers.push_back(std::make_unique<XInputController>(0));
}

dae::InputManager::~InputManager() = default; 

void dae::InputManager::BindCommand(CommandKey key, std::unique_ptr<Command> command) {
    m_Commands[key] = std::move(command);
}

bool dae::InputManager::ProcessInput() {
    for (auto& controller : m_Controllers) controller->Update();

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) return false;
        ImGui_ImplSDL3_ProcessEvent(&e);
    }

    const bool* kbState = SDL_GetKeyboardState(NULL);

    for (auto& [key, command] : m_Commands){
        bool execute = false;
        if (!key.isController) {
            if (kbState[key.id]) execute = true;
        }
        else {
            auto& controller = m_Controllers[0];
            unsigned int buttonBit = static_cast<unsigned int>(key.button);
            switch (key.state) {
            case KeyState::Down:    execute = controller->IsPressed(buttonBit); break;
            case KeyState::Up:      execute = controller->IsUp(buttonBit); break;
            case KeyState::Pressed: execute = controller->IsDown(buttonBit); break;
            }
        }
        if (execute) command->Execute();
    }
    return true;
}