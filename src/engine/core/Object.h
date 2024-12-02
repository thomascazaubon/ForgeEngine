#pragma once

#include "engine/core/NonCopyable.h"

namespace ForgeEngine
{
	typedef unsigned long long int ObjectID;

	class Object : public NonCopyable
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		private:
			ObjectID m_ID{};

			static ObjectID s_LastGivenID;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			Object();
			virtual ~Object() {}

#ifdef FORGE_DEBUG_ENABLED
            virtual const char* GetDebugName() const = 0;
#endif //FORGE_DEBUG_ENABLED

			ObjectID GetID() const { return m_ID; }
	};
}