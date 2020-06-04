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
			LayoutElem(const Shader::Types& type, const std::string& name, const bool& normalised = false)
				: _Type(type), _Name(name), _Size(Shader::TypeSize(type)), _Normalized(normalised) {}

			const Shader::Types& GetType() const { return _Type; }
			const std::string& GetName() const { return _Name; }
			const unsigned int& GetSize() const { return _Size; }
			const unsigned int& GetOffset() const { return _Offset; }
			const bool& GetNormalized() const { return _Normalized; }

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
			std::vector<LayoutElem>::iterator begin() { return _Elems.begin(); }
			std::vector<LayoutElem>::iterator end() { return _Elems.end(); }
			std::vector<LayoutElem>::const_iterator begin() const { return _Elems.begin(); }
			std::vector<LayoutElem>::const_iterator end() const { return _Elems.end(); }

			const unsigned int& GetStride() const { return _Stride; }

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
			Vertex(const Buffers::Layout& layout) : p_Layout(layout) {}
			virtual ~Vertex() = default;

			const Buffers::Layout& GetLayout() { return p_Layout; }

			virtual void Bind() = 0;
		protected:
			Buffers::Layout p_Layout;
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
