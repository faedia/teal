#include "teal/core/LayerStack.h"

namespace Teal
{
	LayerStack::~LayerStack()
	{
		for (StackObj layer : _Layers)
		{
			layer->OnDetach();
			layer.reset();
		}
	}

	void LayerStack::PushLayer(const StackObj& layer)
	{
		_LayerInsert = _Layers.emplace(_LayerInsert, layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(const StackObj& layer)
	{
		_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(const StackObj& layer)
	{
		auto it = std::find(_Layers.begin(), _Layers.end(), layer);
		if (it != _Layers.end())
		{
			_Layers.erase(it);
			_LayerInsert--;
		}
		layer->OnDetach();
	}

	void LayerStack::PopOverlay(const StackObj& layer)
	{
		auto it = std::find(_LayerInsert, _Layers.end(), layer);
		if (it != _Layers.end())
			_Layers.erase(it);
		layer->OnDetach();
	}
}