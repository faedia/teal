#pragma once

#include "teal/core/Common.h"
#include "teal/Event.h"

namespace Teal
{
	class TL_API Layer : public EventListener
	{
	public:
		Layer(const std::string& name) : p_Name(name) {};
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		inline const std::string& GetName() const { return p_Name; }
	protected:
		std::string p_Name;
	};
}