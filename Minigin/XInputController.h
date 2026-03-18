#pragma once
#include <memory> 

namespace dae {
    class XInputController final {
        class XInputControllerImpl; 
        std::unique_ptr<XInputControllerImpl> pImpl;

    public:
        explicit XInputController(unsigned int controllerIndex);
        ~XInputController();

        void Update();
        bool IsDown(unsigned int button) const;
        bool IsUp(unsigned int button) const;
        bool IsPressed(unsigned int button) const;
    };
}