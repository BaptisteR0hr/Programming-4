#include "../Minigin/BaseComponent.h"
#include <vector>
#include "GridManager.h"

namespace pengo {
	enum class PengoState {
		Idle,
		Moving,
		Pushing,
		Dying,
		Dead
	};

	class Pengo : public dae::BaseComponent {
	public:
		explicit Pengo(dae::GameObject* pOwner) : BaseComponent(pOwner) {}
		virtual ~Pengo() = default;

		void Update(float /*deltaTime*/) override {}
		void Render() const override {}
	private:
		int m_Lives{ 4 };
		int m_score{ 0 };
		GridPos m_CurrentPos;
		GridManager* m_pGrid;
	};
}