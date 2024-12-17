#pragma once

namespace ForgeEngine
{
    class NonCopyable
    {
        /************************************/
        /************ATTRIBUTES**************/
        /************************************/

        /************************************/
        /**************METHODS***************/
        /************************************/

        public:
            NonCopyable() {}
            virtual ~NonCopyable() {}
            NonCopyable(const NonCopyable& other) = delete;
            NonCopyable& operator=(const NonCopyable& other) = delete;
            NonCopyable(NonCopyable&&) = delete;
            NonCopyable& operator=(NonCopyable&&) = delete;
    };
}