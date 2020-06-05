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

			const inline Shader::Types& GetType() const { return _Type; }
			const inline std::string& GetName() const { return _Name; }
			const inline unsigned int& GetSize() const { return _Size; }
			const inline unsigned int& GetOffset() const { return _Offset; }
			const inline bool& GetNormalized() const { return _Normalized; }

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
			inline std::vector<LayoutElem>::iterator begin() { return _Elems.begin(); }
			inline std::vector<LayoutElem>::iterator end() { return _Elems.end(); }
			inline std::vector<LayoutElem>::const_iterator begin() const { return _Elems.begin(); }
			inline std::vector<LayoutElem>::const_iterator end() const { return _Elems.end(); }

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

			const inline Buffers::Layout& GetLayout() { return p_Layout; }

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
