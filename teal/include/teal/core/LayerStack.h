#pragma once

#include "teal/core/Common.h"
#include "teal/core/Layer.h"

namespace Teal
{
	class TL_API LayerStack
	{
	public:
		using StackObj = std::shared_ptr<Layer>;
		using Stack = std::vector<StackObj>;

		LayerStack() : _LayerInsert(_Layers.begin()) {}
		~LayerStack();

		void PushLayer(StackObj layer);
		void PushOverlay(StackObj layer);
		void PopLayer(StackObj layer);
		void PopOverlay(StackObj layer);

		Stack::iterator begin() { return _Layers.begin(); }
		Stack::iterator end() { return _Layers.end(); }
	private:
		Stack _Layers;
		Stack::iterator _LayerInsert;
	};
}
