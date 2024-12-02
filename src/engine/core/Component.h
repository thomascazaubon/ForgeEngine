#pragma once

#include "engine/core/ManagedObject.h"

namespace ForgeEngine
{
    class Entity;

	class Component : public ManagedObject
	{
		using Mother = ManagedObject;

		friend class Entity;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		protected:
			Entity* m_Owner{};

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Entity* GetOwner() const { return m_Owner; }

		protected:
			void SetOwner(Entity* owner) { m_Owner = owner; }
	};
}