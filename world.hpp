#pragma once

#include "block.hpp"

#include<vector>

class World final
{
public:
	World() : M_blocks{}
	{
		for (std::size_t i = 0UL; i < 10UL; i++)
		{
			for (std::size_t j = 0UL; j < 10UL; j++)
			{
				M_blocks.emplace_back(GREEN, Vector3{ (float)i + 0.5f, 0.5f, (float)j + 0.5f });
			}
		}
	}

	World(World &&) = delete;
	World(const World &&) = delete;
	World& operator=(World &&) = delete;
	World& operator=(const World &) = delete;

	~World() = default;

	[[nodiscard]]
	const auto &GetBlocks() const
	{
		return M_blocks;
	}

private:
	std::vector<Block> M_blocks;
};