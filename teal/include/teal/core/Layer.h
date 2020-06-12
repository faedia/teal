#pragma once

#include "teal/core/Common.h"
#include "teal/Event.h"
#include "teal/render/Renderer.h"
#include "Time.h"

namespace Teal
{
	class TL_API Layer : public EventListener
	{
	public:
		Layer(const std::string& name) : p_Name(name) {};
		virtual ~Layer() = default;

		virtual void OnAttach(Renderer& renderer) {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const DeltaTime& dt, Renderer& renderer) {}

		inline const std::string& GetName() const { return p_Name; }
	protected:
		std::string p_Name;
	};
}