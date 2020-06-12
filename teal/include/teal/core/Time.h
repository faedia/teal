#pragma once

namespace Teal
{
	class DeltaTime
	{
	public:
		virtual void CalculateDelta() = 0;
		operator double() const { return GetSeconds(); }
		inline double GetSeconds() const { return _DeltaTime; }
		inline double GetMilliSeconds() const { return _DeltaTime * 1000; }
	protected:
		double _PrevTime;
		double _DeltaTime;
	};
}