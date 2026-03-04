#pragma once
#include "BaseComponent.h"
#include <vector>

namespace dae {
    struct Transform3D {
        float matrix[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
    };

    struct GameObject3D {
        Transform3D transform;
        int ID;
    };

    struct GameObject3DAlt {
        int ID;
    };

    class TrashTheCacheComponent final : public BaseComponent {
    public:
        explicit TrashTheCacheComponent(GameObject* pOwner) : BaseComponent(pOwner) {}
        void Update(float) override {}
        void Render() const override {}
        void RenderImGui() override;

    private:
        void RunIntBenchmark(int samples);
        void RunGameObjectBenchmark(int samples);
        void RunGameObjectAltBenchmark(int samples);

        std::vector<float> m_IntResults;
        std::vector<float> m_GameObjectResults;
        std::vector<float> m_GameObjectAltResults;

        int m_IntSamples = 10;
        int m_GameObjectSamples = 10;
    };
}