#pragma once

#include "Shader.h"
#include <string>
#include <vector>

namespace Teal
{
	namespace Buffers
	{
		class LayoutElem
		{
		public:
			LayoutElem(const Shader::Types& type, const std::string& name, bool normalised = false)
				: _Type(type), _Name(name), _Size(Shader::TypeSize(type)), _Normalized(normalised) {}

			const Shader::Types& GetType() { return _Type; }
			const std::string& GetName() { return _Name; }
			const unsigned int& GetSize() { return _Size; }
			const unsigned int& GetOffset() { return _Offset; }

			void SetOffset(const unsigned int& offset) { _Offset = offset; }
		private:
			Shader::Types _Type;
			std::string _Name;
			unsigned int _Offset = 0;
			bool _Normalized;
			unsigned int _Size;
		};

		class Layout
		{
		public:
			Layout(const std::initializer_list<LayoutElem>& elems) : _Elems(elems)
			{
				DoOffsetStride();
			}
		private:
			void DoOffsetStride()
			{
				_Stride = 0;
				for (auto& elem : _Elems)
				{
					elem.SetOffset(_Stride);
					_Stride += elem.GetSize();
				}
			}

			std::vector<LayoutElem> _Elems;
			unsigned int _Stride = 0;
		};

		class Vertex
		{
		public:
			virtual ~Vertex() = default;

			virtual void Bind() = 0;
		};

		class Index
		{
		public:
			virtual ~Index() = default;

			virtual void Bind() = 0;
			virtual unsigned int GetCount() = 0;
		};

	}
}
