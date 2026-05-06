#pragma once
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace dae {
    class Scene;
}

namespace pengo {
    struct GridPos {
        int col;
        int row;

        bool operator==(const GridPos& other) const {
            return col == other.col && row == other.row;
        }
    };
    enum class TileType { Empty, Ice, Diamond, Wall };

    class GridManager final {
    public:
        GridManager(dae::Scene& scene);

        void LoadLevel(const std::string& levelPath);

        bool IsTileWalkable(int row, int col) const;
        TileType GetTileAt(int row, int col) const;

        GridPos GetGridPosFromXY(float x, float y) const;
        glm::vec2 GetWorldPosFromGrid(GridPos pos) const;

    private:
        dae::Scene& m_Scene; 
        int m_Rows{ 15 };
        int m_Cols{ 13 };
        float m_TileSize{ 32.0f };

        std::vector<TileType> m_Grid;
    };
}