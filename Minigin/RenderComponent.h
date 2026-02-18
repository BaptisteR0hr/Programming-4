#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>

namespace dae {
    class Texture2D;
    class RenderComponent final : public BaseComponent {
    public:
        RenderComponent(GameObject* pOwner, const std::string& filename);
        void Update(float) override {}
        void Render() const override;
    private:
        std::shared_ptr<Texture2D> m_texture;
    };
}